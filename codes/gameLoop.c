#include "raylib.h"
#include <string.h>
#include "mapToArray.c"
#include "movements.h"
#include "shoot.c"
#include "constants.h"
#include "keyboardFunctions.h"
#include "visualInterface.h"
//include "mazeSolver2.h"
#include "mazeSolverDijkstra.h"
#include "stopwatch.h"
#include <time.h>       // for time()
#include <unistd.h>     // for sleep()


struct Bullet bullets[MAX_BULLLETS];
struct Isaac isaac;
struct Enemy enemies[15];
struct Enemy enemy1;
//struct Stopwatch stopwatch;

typedef enum { GAME, MENU } GameState;



int gameLoop(int map_counter,struct Stopwatch *stopwatch, struct InformationBarStrings *informationBarStrings)
{

	for(int i = 0; i < MAX_BULLLETS; i++){
		bullets[i].IsAlive = false;
	}

	int i,j,missionComplete=0;
	int nEnemies;
	readMap(&isaac,map_counter,enemies,&nEnemies);

	//Characters Variables
	isaac.id='J';
	isaac.missionComplete=0;
	enemy1.id='I';
	isaac.nLifes=300;
	isaac.nBombs=0;
	for(int i=0;i<MAX_ENEMIES;i++)
	{
		enemies[i].id='I';
	}

	static int graph[V][V];
	static int dist[V][V];
	static int Next[V][V];
	static int path[V];
	int nVertices=V;
	static int maze[MAP_SIZE_Y][MAP_SIZE_X];
	mapToMaze(maze);
	mazeToGraph(maze,graph);


    int** adjacencyMatrix = (int**)malloc(nVertices * sizeof(int*));
    for (int i = 0; i < nVertices; i++) {
        adjacencyMatrix[i] = (int*)malloc(nVertices * sizeof(int));
    }

    for (int i = 0; i < nVertices; i++) {
        for (int j = 0; j < nVertices; j++) {
            adjacencyMatrix[i][j]=graph[i][j];
        }
    }
    int dxdy[2];

	GameState gameState = GAME;
	//set default state

	EnemiesAlive = nEnemies;
	//La¸co principal do jogo
	//int enemiesSleepCount=0; //counter to slows dows enemy. it moves each enemyMovesPeriod
	//int isaacSleepCount=0; //counter to slows dows Isaac. it moves each isaacMovesPeriod
	//int enemyMovesPeriod=20;
	//int isaacMovesPeriod=500;
	SetExitKey(0);// the function WindowShouldClose will close when ESC is press, this will Set the configuration flag to ignore the ESC key press
	while (!WindowShouldClose()&&isaac.missionComplete==0) // Detect window close button or ESC key
	{
		// Trata entrada do usu´ario e atualiza estado do jogo
		//----------------------------------------------------------------------------------

		

		 if (IsKeyPressed(KEY_ESCAPE)) {
            // Toggle the game state between GAME and MENU
            if (gameState == GAME) {
                gameState = MENU;
            } else if (gameState == MENU) {
				restart_chronometer(stopwatch);
                gameState = GAME;
            }
        }


		if (gameState == GAME) {
			AtualizarTiros(bullets, map, enemies, nEnemies);

			readKeyboard(&isaac,bullets);

			for(int i=0;i<nEnemies;i++)
			{
				// if enemy.isAlive is false and his id is 'I', it is the first time he has passed through this loop.
				// The function moveAndVerifyEnemy will declare his id as ' '
				if(enemies[i].IsAlive || enemies[i].id == 'I')
				{
					dijkstra(adjacencyMatrix, enemies[i].vertex, V, isaac.vertex, dxdy);

					enemies[i].dx=dxdy[0];
					enemies[i].dy=dxdy[1];

					moveAndVerifyEnemy(&enemies[i],&isaac);
					isaac.vertex=indexToVertex(isaac.posY,isaac.posX);
					enemies[i].vertex=indexToVertex(enemies[i].posY,enemies[i].posX);
				}
			}

			if(map[isaac.posY][isaac.posX]=='P' && EnemiesAlive <= 0)
			{
				isaac.missionComplete=1;
				return 0;
				//CloseWindow();
			}
			get_elapsed_time(stopwatch);
			drawWindow(stopwatch->str_time,isaac, *stopwatch, map_counter,informationBarStrings,EnemiesAlive);
			//printf("%d",enemiesSleepCount);

        } else if (gameState == MENU) {

			Menu();
        }
	}
    for(int i = 0; i < nVertices; i++)
		free(adjacencyMatrix[i]);
	free(adjacencyMatrix);
	return 1;
}

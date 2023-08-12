#include "raylib.h"
#include <string.h>
#include "mapToArray.c"
#include "movements.h"
#include "shoot.c"
#include "constants.h"
#include "keyboardFunctions.h"
#include "visualInterface.h"
#include "stopwatch.h"
#include <time.h>       // for time()
#include <unistd.h>     // for sleep()
#include "mazeSolverFloydWarshall.h"
#include "constants.h"

struct Bullet bullets[MAX_BULLLETS];

struct Isaac isaac;
struct Enemy enemies[MAX_ENEMIES];
struct Enemy enemy1;
//struct Stopwatch stopwatch;

typedef enum { GAME, MENU } GameState;

int gameLoop(int *map_counter,struct Stopwatch *stopwatch, struct InformationBarStrings *informationBarStrings)
{
	struct MapElement mapElements[N_MAP_ELEMENTS];
	int i,j,missionComplete=0;
	int nEnemies;


	static int graph[V][V];
	static int dist[V][V];
	static int Next[V][V];
	static int path[V];
	int nVertices=V;
	static int maze[MAP_SIZE_Y][MAP_SIZE_X];
	mapToMaze(maze);
	mazeToGraph(maze,graph);
	static char nextMoveMatrix[V][V];
	

	int dxdy[2];

	GameState gameState = GAME;
	//set default state

	EnemiesAlive = nEnemies;
	int fframe=0;
	int enemyMovesPeriod=2;
	
	
	////////////
	// INITIALIZATIONS
	///////////
	readMap(&isaac,*map_counter,enemies,&nEnemies);
	initializeMapElement(mapElements);
	for(int i = 0; i < MAX_BULLLETS; i++) {
		bullets[i].IsAlive = false;
	}


	readMap(&isaac,*map_counter,enemies,&nEnemies);

	//Characters Variables
	isaac.id='J';
	isaac.missionComplete=0;
	enemy1.id='I';
	isaac.nLifes=300;
	isaac.nBombs=0;
	for(int i=0; i<MAX_ENEMIES; i++)
	{
		enemies[i].id='I';
	}
	EnemiesAlive = nEnemies;
	if(orderToLoadGame==1)
	{
		loadGame(map,enemies,&isaac,stopwatch,&EnemiesAlive,bullets,map_counter,&nEnemies);
		restart_chronometer(stopwatch);
		//calculateEnemyMovesIfNeeded(*map_counter,graph,dist,Next,nextMoveMatrix);
		orderToLoadGame=0;
	}

	calculateEnemyMovesIfNeeded(*map_counter,graph,dist,Next,nextMoveMatrix);


	SetExitKey(0);// the function WindowShouldClose will close when ESC is press, this will Set the configuration flag to ignore the ESC key press
	while (!WindowShouldClose()&&isaac.missionComplete==0) // Detect window close button or ESC key
	{
		// Trata entrada do usu´ario e atualiza estado do jogo
		//----------------------------------------------------------------------------------
		if(orderToSaveGame==1)
		{
			saveGame(map,enemies,isaac,stopwatch,EnemiesAlive,bullets,*map_counter,nEnemies);
			orderToSaveGame=0;
		}
		if(orderToLoadGame==1)
		{
			
			//loadGame(map,enemies,&isaac,stopwatch,&EnemiesAlive,bullets,map_counter);
			//restart_chronometer(stopwatch);
			//calculateEnemyMovesIfNeeded(*map_counter,graph,dist,Next,nextMoveMatrix);
			*map_counter-=1;
			return 0;
			//calculateEnemyMovesIfNeeded(*map_counter,graph,dist,Next,nextMoveMatrix);
			//orderToLoadGame=0;
		}
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

			readKeyboard(&isaac,bullets,mapElements);

			if(fframe==0)
			{

				for(int i=0; i<nEnemies; i++)
				{
					// if enemy.isAlive is false and his id is 'I', it is the first time he has passed through this loop.
					// The function moveAndVerifyEnemy will declare his id as ' '
					if(enemies[i].IsAlive || enemies[i].id == 'I')
					{
						//dijkstra(adjacencyMatrix, enemies[i].vertex, V, isaac.vertex, dxdy);
						getDxdyFromNextMoveMatrix(dxdy,nextMoveMatrix[enemies[i].vertex][isaac.vertex]);
						enemies[i].dx=dxdy[0];
						enemies[i].dy=dxdy[1];

						moveAndVerifyEnemy(&enemies[i],&isaac,mapElements);
						isaac.vertex=indexToVertex(isaac.posY,isaac.posX);
						enemies[i].vertex=indexToVertex(enemies[i].posY,enemies[i].posX);
					}
				}
				fframe++;
			}
			else
			{
				fframe++;
				if(fframe>=enemyMovesPeriod)
				{
					fframe=0;
				}
			}

			if(EnemiesAlive<=0)
			{
				mapElements[MAP_ELEMENT_PORTAL_NUMBER].canIsaacMove=1;
			}

			if(map[isaac.posY][isaac.posX]=='P' && EnemiesAlive <= 0)
			{
				isaac.missionComplete=1;
				return 0;
				//CloseWindow();
			}
			get_elapsed_time(stopwatch);
			drawWindow(stopwatch->str_time,isaac, *stopwatch, *map_counter,informationBarStrings,EnemiesAlive,mapElements);
			//printf("%d",enemiesSleepCount);

		} else if (gameState == MENU) {

			Menu();
		}
	}

	return 1;
}

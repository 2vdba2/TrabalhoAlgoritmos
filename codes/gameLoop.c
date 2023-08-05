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
struct Enemy enemy1;
//struct Stopwatch stopwatch;

void gameLoop(int map_counter,struct Stopwatchh *stopwatchh, struct InformationBarStrings *informationBarStrings)
{
	int i,j,missionComplete=0;

	readMap(&isaac,&enemy1,map_counter);
	
	//Characters Variables
	isaac.id='J';
	enemy1.id='I';
	isaac.nLifes=300;
	
	//Time
	//stopwatch->start_time= time(NULL);
	//stopwatch->elapsed_time= time(NULL);
	//stopwatch->str_time={"00:00:00"};
	
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

	//La¸co principal do jogo
	int fframe=0;
	while (!WindowShouldClose()&&missionComplete==0) // Detect window close button or ESC key
	{
		// Trata entrada do usu´ario e atualiza estado do jogo
		//----------------------------------------------------------------------------------
		AtualizarTiros(bullets, map);

		readKeyboardMove(&isaac);
		readKeyboardShoot(isaac,bullets);
		enemy1.id='I';
		if(fframe==0)
		{
			dijkstra(adjacencyMatrix, enemy1.vertex, V, isaac.vertex, dxdy);

			enemy1.dx=dxdy[0];
			enemy1.dy=dxdy[1];
			
			moveAndVerifyEnemy(&enemy1,&isaac);
			isaac.vertex=indexToVertex(isaac.posY,isaac.posX);
			enemy1.vertex=indexToVertex(enemy1.posY,enemy1.posX);
			fframe++;
		}
		else
		{
			fframe++;
			if(fframe>=20)
			{
				fframe=0;
			}
		}
		if(map[isaac.posY][isaac.posX]=='P')
		{
			missionComplete=1;
			//CloseWindow();
		}
		get_elapsed_time(stopwatchh);
		drawWindow(stopwatchh->str_time,isaac, *stopwatchh, map_counter,informationBarStrings);
		printf("%d",fframe);

	}
    for(int i = 0; i < nVertices; i++)
		free(adjacencyMatrix[i]);
	free(adjacencyMatrix);
	
}

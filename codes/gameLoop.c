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


struct Bullet bullets[MAX_BULLLETS];

void gameLoop()
{
	int i,j,missionComplete=0;
	int xpx,ypx;
	struct Isaac isaac;
	struct Enemy enemy1;
	readMap(&isaac,&enemy1);
	
	//TESTING START
	
	isaac.id='J';
	
	enemy1.id='I';
	
	isaac.vertex=indexToVertex(isaac.posY,isaac.posX);
	enemy1.vertex=indexToVertex(enemy1.posY,enemy1.posX);
	
	printf("\nisaac vertex = %d",isaac.vertex);
	printf("\nenemy vertex = %d",enemy1.vertex);
	
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
    
    isaac.vertex=indexToVertex(isaac.posY, isaac.posX);
    enemy1.vertex=indexToVertex(enemy1.posY, enemy1.posX);
    
    dijkstra(adjacencyMatrix, enemy1.vertex, V, isaac.vertex, dxdy);
    //dijkstra(adjacencyMatrix, 153, V, 150, dxdy);
    printf("\nenemy x = %d, y = %d",enemy1.posX,enemy1.posY);
    //enemyMove(isaac,&enemy1);
    printf("\nenemy x = %d, y = %d",enemy1.posX,enemy1.posY);
	//printf("Go to %d!",dxdy[0]);
	
	
	//TESTING END

	//--------------------------------------------------------------------------------------
	//Inicializa¸c~oes
	InitWindow(MAP_SIZE_X_PX, MAP_SIZE_Y_PX+INFORMATION_BAR_Y_PX, "The Binding of Isaac remastered");//Inicializa janela, com certo tamanho e t´ıtulo
	SetTargetFPS(60);// Ajusta a execu¸c~ao do jogo para 60 frames por segundo
	//--------------------------------------------------------------------------------------
	//La¸co principal do jogo
	int fframe=0;
	while (!WindowShouldClose()) // Detect window close button or ESC key
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
			//enemy1.dx=1;
			//enemy1.dy=0;
			enemy1.dx=dxdy[0];
			enemy1.dy=dxdy[1];
			
			
			moveAndVerifyEnemy(&enemy1);
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
			CloseWindow();
		}
		drawWindow();
		printf("%d",fframe);

	}
	CloseWindow();// Fecha a janela e o contexto OpenGL
}

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
#include "mazeSolverFloydWarshall.h"
#include "constants.h"

struct Bullet bullets[MAX_BULLLETS];
struct Isaac isaac;
struct Enemy enemies[MAX_ENEMIES];


int gameLoop(int *map_counter,struct Stopwatch *stopwatch, struct InformationBarStrings *informationBarStrings,int nMaps)
{
	struct MapElement mapElements[N_MAP_ELEMENTS];
	int missionComplete=0;
	int nEnemies;
	static char nextMoveMatrix[V][V];
	int dxdy[2];//next enemy move
	int frame=0;
	int enemyMovesPeriod=2;
	int backUpIsaacNlifes;
	int scoreMessageDone=0;

	GameState gameState = GAME;

	initializeMapElement(mapElements);

	if(orderToLoadGame==1)
	{
		loadGame(map,enemies,&isaac,stopwatch,&EnemiesAlive,bullets,map_counter,&nEnemies, "QuickSave.bin");
		restart_chronometer(stopwatch);
		orderToLoadGame=0;
	}
	else
	{
		readMap(&isaac,*map_counter,enemies,&nEnemies);
		initializeIsaacEnemiesBullets(enemies,&isaac,bullets);
		EnemiesAlive = nEnemies;
	}
	calculateEnemyMovesIfNeeded(*map_counter,nextMoveMatrix);

	SetExitKey(0);// the function WindowShouldClose will close when ESC is press, this will Set the configuration flag to ignore the ESC key press
	while (closeGame==0&&isaac.missionComplete==0) // Detect window close button or ESC key
	{
		// Trata entrada do usu´ario e atualiza estado do jogo
		//----------------------------------------------------------------------------------
		if(orderToSaveGame==1)
		{
			saveGame(map,enemies,isaac,stopwatch,EnemiesAlive,bullets,*map_counter,nEnemies, "QuickSave.bin");
			orderToSaveGame=0;
		}
		if(orderToLoadGame==1)
		{
			*map_counter-=1;//because it leaves the loop and increments 1
			return 0;
		}

		readKeyboardSpecialKeys(mapElements,stopwatch,&gameState);
		if (gameState == GAME)
		{
			backUpIsaacNlifes=isaac.nLifes;
			AtualizarTiros(bullets, map, enemies, nEnemies);
			readKeyboard(&isaac,bullets,mapElements,stopwatch);//read isaac movements, shoots and special functions
			moveAndVerifyAllEnemies(enemies,&isaac,mapElements,&frame,nEnemies,nextMoveMatrix);

			//If kill all enemies dead, open portal
			if(EnemiesAlive<=0)
			{
				mapElements[MAP_ELEMENT_PORTAL_NUMBER].canIsaacMove=1;
			}
			//If isaac reached portal, go to next stage
			if(map[isaac.posY][isaac.posX]=='P' && EnemiesAlive <= 0)
			{
				//if isaac passed through all maps, come back to initial menu
				if(*map_counter==nMaps-1&&!scoreMessageDone)
				{
					while(!IsKeyPressed(KEY_ENTER))
					{
						drawScore(stopwatch->str_time,isaac, *stopwatch, *map_counter,informationBarStrings,EnemiesAlive,mapElements);
					}
					scoreMessageDone=1;
				}
				
				else
				{
					isaac.missionComplete=1;
					return 0;
				}
				
			}
			if(isaac.nLifes<backUpIsaacNlifes&&isaac.nLifes>0)
			{
				readMap(&isaac,*map_counter,enemies,&nEnemies);
				initializeIsaacEnemiesBullets(enemies,&isaac,bullets);
				EnemiesAlive = nEnemies;
				isaac.nLifes=backUpIsaacNlifes-1;
			}

			if(isaac.nLifes<=0)
			{
				*map_counter=nMaps;//force leave maps loop
				return 0;
			}

			get_elapsed_time(stopwatch);//update stopwatch
			drawWindow(stopwatch->str_time,isaac, *stopwatch, *map_counter,informationBarStrings,EnemiesAlive,mapElements); // draw visual interface
		}
		//check if gameState was changed from GAME to MENU by shortcut ESC
		else if (gameState == MENU)
		{
			InGameMenu(&gameState );
		} else if(gameState == WarningMenu) {
			if(AreYouSureMenu() == 1) {
				NewGame();
			} else if(AreYouSureMenu() == 0) {
				gameState = GAME;
			}
		}
		if(WindowShouldClose())
		{
			closeGame=1;
		}
	}

	return 1;
}

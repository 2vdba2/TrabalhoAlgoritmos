#include "raylib.h"
#include <string.h>
#include "mapToArray.c"
#include "mechanicsFunctions.h"
#include "shoot.c"
#include "constants.h"
#include "keyboardFunctions.h"
#include "visualInterface.h"

struct Bullet bullets[MAX_BULLLETS];

void gameLoop()
{
	int i,j,missionComplete=0;
	int xpx,ypx;
	struct Isaac isaac;

    readMap(&isaac);

    //--------------------------------------------------------------------------------------
    //Inicializa¸c~oes
    InitWindow(MAP_SIZE_X_PX, MAP_SIZE_Y_PX, "The Binding of Isaac remastered");//Inicializa janela, com certo tamanho e t´ıtulo
    SetTargetFPS(60);// Ajusta a execu¸c~ao do jogo para 60 frames por segundo
    //--------------------------------------------------------------------------------------
    //La¸co principal do jogo
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
    // Trata entrada do usu´ario e atualiza estado do jogo
    //----------------------------------------------------------------------------------
        AtualizarTiros(bullets, map);
		
		readKeyboardMove(&isaac);
		readKeyboardShoot(isaac,bullets);

        if(map[isaac.posY][isaac.posX]=='P')
        {
			missionComplete=1;
			CloseWindow();
		}
		drawWindow();
    }
    CloseWindow();// Fecha a janela e o contexto OpenGL
}

#include "raylib.h"
#include <string.h>
#include "mapToArray.c"
#include "shoot.c"

#define MAX_BULLLETS 100

struct Bullet bullets[MAX_BULLLETS];


void drawMap()
{
	int i,j,missionComplete=0;
	int MAP_SIZE_PX_L=MAP_SIZE_L*20;
	int MAP_SIZE_PX_C=MAP_SIZE_C*20;
    int x=MAP_SIZE_PX_C/2,y=MAP_SIZE_PX_L/2;

    // set initial position
    i=MAP_SIZE_L/2;
    j=MAP_SIZE_C/2;


    readMap();

    //--------------------------------------------------------------------------------------
    //Inicializa¸c~oes
    InitWindow(MAP_SIZE_PX_C, MAP_SIZE_PX_L, "The Binding of Isaac remastered");//Inicializa janela, com certo tamanho e t´ıtulo
    SetTargetFPS(60);// Ajusta a execu¸c~ao do jogo para 60 frames por segundo
    //--------------------------------------------------------------------------------------
    //La¸co principal do jogo
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
    // Trata entrada do usu´ario e atualiza estado do jogo
    //----------------------------------------------------------------------------------


        AtualizarTiros(bullets, map);

        if (IsKeyPressed(KEY_W))
        {
            if(map[i - 1][j] == ' ')
            {
                Atirar(bullets, j, i, 0 , -1);
            }
        }

        if (IsKeyPressed(KEY_S))
        {
            if(map[i + 1][j] == ' ')
            {
                Atirar(bullets, j, i, 0 , 1);
            }
        }


        if (IsKeyPressed(KEY_A))
        {
            if(map[i][j - 1] == ' ')
            {
                Atirar(bullets, j, i, -1 , 0);
            }
        }

        if (IsKeyPressed(KEY_D))
        {
            if(map[i][j + 1] == ' ')
            {
                Atirar(bullets, j, i, 1 , 0);
            }
        }


        if (IsKeyPressed(KEY_RIGHT))
        {
            j+=1;
            if(map[i][j]=='#')
            {
                j-=1;
            }
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            j-=1;
            if(map[i][j]=='#')
            {
                j+=1;
            }
        }
        if (IsKeyPressed(KEY_UP))
        {
            i-=1;
            if(map[i][j]=='#')
            {
                i+=1;
            }
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            i+=1;
            if(map[i][j]=='#')
            {
                i-=1;
            }
        }
        if(map[i][j]=='P')
        {
			missionComplete=1;
			CloseWindow();
		}
        //----------------------------------------------------------------------------------
        // Atualiza a representa¸c~ao visual a partir do estado do jogo
        //----------------------------------------------------------------------------------
        x=j*20;
        y=i*20;



        BeginDrawing();//Inicia o ambiente de desenho na tela
        ClearBackground(RAYWHITE);//Limpa a tela e define cor de fundo
        DrawRectangle(x,y,20,20,GREEN);
        //Draw matrixMap
        for(int i=0; i<MAP_SIZE_L; i++)
        {
            for(int j=0; j<MAP_SIZE_C; j++)
            {
				//walls
                if(map[i][j]=='#')
                {
                    DrawRectangle(j*20,i*20,20,20,RED);
                }
                //portal
                else if(map[i][j]=='P')
                {
					DrawRectangle(j*20,i*20,20,20,YELLOW);
				}
                else if(map[i][j]=='o')
                {
					DrawRectangle(j*20 + 5,i*20 + 5,10,10,BLACK);
				}
            }
        }
        EndDrawing();//Finaliza o ambiente de desenho na tela
    //----------------------------------------------------------------------------------
    }
    CloseWindow();// Fecha a janela e o contexto OpenGL
}

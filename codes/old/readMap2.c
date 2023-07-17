#include "raylib.h"
#define LARGURA 600
#include <string.h>
#define ALTURA 600
#include "../maps/mapToArray.c"

//extern int main2();
int main(void)
{

	int MAP_SIZE_PX_L=MAP_SIZE_L*20;
	int MAP_SIZE_PX_C=MAP_SIZE_C*20;
	//int LARGURA=MAP_SIZE_L*20;
    int x=MAP_SIZE_PX_C/2,y=MAP_SIZE_PX_L/2;

    int obstacles[MAP_SIZE_PX_L][MAP_SIZE_PX_C];
    //main2();
    //Frame
    for(int i=0; i<MAP_SIZE_PX_L; i++)
    {
        for(int j=0; j<MAP_SIZE_PX_C; j++)
        {
            if(i==0||i==MAP_SIZE_L-1||j==0||j==MAP_SIZE_C-1)
            {
                obstacles[i][j]=1;
            }
            else
            {
                obstacles[i][j]=0;
            }
        }
    }
    //Obstaculos
    
    for(int i=5; i<25; i=i+6)
    {
        for(int j=5; j<55; j=j+6)
        {
            obstacles[i][j]=1;
        }
    }
    
    //char texto[50] = "Pressione uma seta";//texto inicial
    //--------------------------------------------------------------------------------------
    //Inicializa¸c~oes
    InitWindow(MAP_SIZE_PX_C, MAP_SIZE_PX_L, "Quadrado");//Inicializa janela, com certo tamanho e t´ıtulo
    SetTargetFPS(60);// Ajusta a execu¸c~ao do jogo para 60 frames por segundo
    //--------------------------------------------------------------------------------------
    //La¸co principal do jogo
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
    // Trata entrada do usu´ario e atualiza estado do jogo
    //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_RIGHT))
        {
            x+=20;
            if(obstacles[y/20][x/20]==1)
            {
                x-=20;
            }
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            x-=20;
            if(obstacles[y/20][x/20]==1)
            {
                x+=20;
            }
        }
        if (IsKeyPressed(KEY_UP))
        {
            y-=20;
            if(obstacles[y/20][x/20]==1)
            {
                y+=20;
            }
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            y+=20;
            if(obstacles[y/20][x/20]==1)
            {
                y-=20;
            }
        }
        //----------------------------------------------------------------------------------
        // Atualiza a representa¸c~ao visual a partir do estado do jogo
        //----------------------------------------------------------------------------------
        BeginDrawing();//Inicia o ambiente de desenho na tela
        ClearBackground(RAYWHITE);//Limpa a tela e define cor de fundo
        DrawRectangle(x,y,20,20,GREEN);
        //Draw obstacles
        for(int i=0; i<MAP_SIZE_L; i++)
        {
            for(int j=0; j<MAP_SIZE_C; j++)
            {
                if(obstacles[i][j]==1)
                {
                    DrawRectangle(j*20,i*20,20,20,RED);
                }
            }
        }
        EndDrawing();//Finaliza o ambiente de desenho na tela
    //----------------------------------------------------------------------------------
    }
    CloseWindow();// Fecha a janela e o contexto OpenGL
    return 0;
}

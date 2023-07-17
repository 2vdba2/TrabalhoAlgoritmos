#include "raylib.h"
#define LARGURA 600
#include <string.h>
#define ALTURA 600
int main(void)
{
    int x=300,y=300;
    int obstacles[30][30];
    //Frame
    for(int i=0; i<30; i++)
    {
        for(int j=0; j<30; j++)
        {
            if(i==0||i==29||j==0||j==29)
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
        for(int j=5; j<25; j=j+6)
        {
            obstacles[i][j]=1;
        }
    }
    //char texto[50] = "Pressione uma seta";//texto inicial
    //--------------------------------------------------------------------------------------
    //Inicializa¸c~oes
    InitWindow(LARGURA, ALTURA, "Quadrado");//Inicializa janela, com certo tamanho e t´ıtulo
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
            if(obstacles[x/20][y/20]==1)
            {
                x-=20;
            }
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            x-=20;
            if(obstacles[x/20][y/20]==1)
            {
                x+=20;
            }
        }
        if (IsKeyPressed(KEY_UP))
        {
            y-=20;
            if(obstacles[x/20][y/20]==1)
            {
                y+=20;
            }
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            y+=20;
            if(obstacles[x/20][y/20]==1)
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
        for(int i=0; i<30; i++)
        {
            for(int j=0; j<30; j++)
            {
                if(obstacles[i][j]==1)
                {
                    DrawRectangle(i*20,j*20,20,20,RED);
                }
            }
        }
        EndDrawing();//Finaliza o ambiente de desenho na tela
    //----------------------------------------------------------------------------------
    }
    CloseWindow();// Fecha a janela e o contexto OpenGL
    return 0;
}

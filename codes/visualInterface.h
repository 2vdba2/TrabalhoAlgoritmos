#ifndef VISUALINTERFACE_H
#define VISUALINTERFACE_H

#include "constants.h"
#include "structs.h"
#include <string.h>

void drawMap()
{
	int xpx,ypx;
	DrawRectangle(0,0,MAP_SIZE_X_PX,MAP_SIZE_Y_PX,BEIGE);
	//Draw matrixMap
	for(int i=0; i<MAP_SIZE_Y; i++)
	{
		for(int j=0; j<MAP_SIZE_X; j++)
		{
			xpx=j*SQUARESIZE;
			ypx=i*SQUARESIZE;
			//walls
			if(map[i][j]=='#')
			{
				DrawRectangle(xpx,ypx,SQUARESIZE,SQUARESIZE,RED);
			}
			//portal
			else if(map[i][j]=='P')
			{
				DrawRectangle(xpx,ypx,SQUARESIZE,SQUARESIZE,YELLOW);
			}
			//bullet
			else if(map[i][j]=='o')
			{
				DrawRectangle(xpx + SQUARESIZE/4,ypx + SQUARESIZE/4,BULLETSIZE,BULLETSIZE,BLACK);
			}
			//bullet
			else if(map[i][j]=='J')
			{
				DrawRectangle(xpx,ypx,SQUARESIZE,SQUARESIZE,GREEN);
			}
			//Bomb
			else if(map[i][j]=='B')
			{
				DrawRectangle(xpx,ypx,SQUARESIZE,SQUARESIZE,BROWN);
			}
			//Fire
			else if(map[i][j]=='X')
			{
				DrawRectangle(xpx,ypx,SQUARESIZE,SQUARESIZE,ORANGE);
			}
			//Enemy
			else if(map[i][j]=='I')
			{
				DrawRectangle(xpx,ypx,SQUARESIZE,SQUARESIZE,PURPLE);
			}
		}
	}
}
void informationBar(struct Isaac isaac,struct InformationBarStrings informationBarStrings)
{
	//This function draws the informationBar at the botton of the window
	int xPxCol1  = INFORMATION_BAR_X_PX/30;
	int xPxCol2  = xPxCol1+INFORMATION_BAR_X_PX/1.25;
	int yPxLine1 = MAP_SIZE_Y_PX+INFORMATION_BAR_Y_PX/6;
	int yPxLine2 = yPxLine1 + INFORMATION_BAR_Y_PX/2;

	DrawRectangle(0,MAP_SIZE_Y_PX,INFORMATION_BAR_X_PX,INFORMATION_BAR_Y_PX,SKYBLUE); // draw background

	//draw information bar strings
	DrawText(informationBarStrings.timeText   , xPxCol1,yPxLine1,30, BLACK);
	DrawText(informationBarStrings.lifeText   , xPxCol1,yPxLine2,30, BLACK);
	DrawText(informationBarStrings.stageText  , xPxCol2,yPxLine1,30, BLACK);
	DrawText(informationBarStrings.enemiesText, xPxCol2,yPxLine2,30, BLACK);
}

void createInformationBarStrings(struct Stopwatchh stopwatchh, struct Isaac isaac, int map_counter, struct InformationBarStrings *informationBarStrings,int nEnemies)
{
	//This function creates the information bar strings
	sprintf(informationBarStrings->lifeText   , "Lifes: %d"     , isaac.nLifes);
	sprintf(informationBarStrings->timeText   , "Time alive: %s", stopwatchh.str_time);
	sprintf(informationBarStrings->stageText  , "Stage: %d"     , map_counter+1);
	sprintf(informationBarStrings->enemiesText, "Enemies: %d"   , nEnemies);
}

void drawWindow(char str_time[],struct Isaac isaac,struct Stopwatchh stopwatchh, int map_counter,  struct InformationBarStrings *informationBarStrings, int nEnemies)
{
	//This function draws the entire game window
	BeginDrawing();//Inicia o ambiente de desenho na tela
	ClearBackground(RAYWHITE);//Limpa a tela e define cor de fundo
	drawMap();
	createInformationBarStrings(stopwatchh,isaac, map_counter,informationBarStrings,nEnemies);
	informationBar(isaac,*informationBarStrings);
	EndDrawing();//Finaliza o ambiente de desenho na tela
}

typedef enum { 
    NOVO_JOGO,
    CARREGAR_JOGO,
    CONFIGURACOES,
    SAIR
 } MenuItem;

MenuItem currentMenuItem = NOVO_JOGO;

void DrawMenu() {
    ClearBackground(RAYWHITE);

    DrawText("The Binding of Isaac", MAP_SIZE_X_PX / 2 - MeasureText("The Binding of Isaac", 40) / 2, 80, 40, DARKGRAY);

    switch (currentMenuItem) {
        case NOVO_JOGO:
            DrawText("> Novo Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Novo Jogo", 30) / 2, 200, 30, GRAY);
            DrawText("Carregar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Carregar Jogo", 30) / 2, 250, 30, GRAY);
            DrawText("Configurações", MAP_SIZE_X_PX / 2 - MeasureText("Configurações", 30) / 2, 300, 30, GRAY);
            DrawText("Sair", MAP_SIZE_X_PX / 2 - MeasureText("Sair", 30) / 2, 350, 30, GRAY);
            break;
        case CARREGAR_JOGO:
            DrawText("Novo Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Novo Jogo", 30) / 2, 200, 30, GRAY);
            DrawText("> Carregar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Carregar Jogo", 30) / 2, 250, 30, GRAY);
            DrawText("Configurações", MAP_SIZE_X_PX / 2 - MeasureText("Configurações", 30) / 2, 300, 30, GRAY);
            DrawText("Sair", MAP_SIZE_X_PX / 2 - MeasureText("Sair", 30) / 2, 350, 30, GRAY);
            break;
        case CONFIGURACOES:
            DrawText("Novo Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Novo Jogo", 30) / 2, 200, 30, GRAY);
            DrawText("Carregar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Carregar Jogo", 30) / 2, 250, 30, GRAY);
            DrawText("> Configurações", MAP_SIZE_X_PX / 2 - MeasureText("Configurações", 30) / 2, 300, 30, GRAY);
            DrawText("Sair", MAP_SIZE_X_PX / 2 - MeasureText("Sair", 30) / 2, 350, 30, GRAY);
            break;
        case SAIR:
            DrawText("Novo Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Novo Jogo", 30) / 2, 200, 30, GRAY);
            DrawText("Carregar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Carregar Jogo", 30) / 2, 250, 30, GRAY);
            DrawText("Configurações", MAP_SIZE_X_PX / 2 - MeasureText("Configurações", 30) / 2, 300, 30, GRAY);
            DrawText("> Sair", MAP_SIZE_X_PX / 2 - MeasureText("Sair", 30) / 2, 350, 30, GRAY);
            break;
        default:
            break;
    }

    DrawText("Use as setas para navegar e pressione enter para selecionar", 50, MAP_SIZE_Y_PX - 50, 20, DARKGRAY);
}

#endif

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
void informationBar(char str_time[], struct Isaac isaac)
{
	int xPxCol1  = INFORMATION_BAR_X_PX/30;
	int xPxCol2  = xPxCol1+INFORMATION_BAR_X_PX/1.25;
	int yPxLine1 = MAP_SIZE_Y_PX+INFORMATION_BAR_Y_PX/6;
	int yPxLine2 = yPxLine1 + INFORMATION_BAR_Y_PX/2;
	
	char time_text[21] = {"Time alive: "};
	
	strcat(time_text,str_time);
	
	char life_text[10] = {"Lifes: "};
	char nLifes_char[10];
	sprintf(nLifes_char, "%d", isaac.nLifes);
	strcat(life_text,nLifes_char);
	
	
	DrawRectangle(0,MAP_SIZE_Y_PX,INFORMATION_BAR_X_PX,INFORMATION_BAR_Y_PX,SKYBLUE);
	//DrawText(strcat("Time alive: ",str_time), xPxCol1,yPxLine1,30, BLACK);
	
	DrawText(time_text,xPxCol1,yPxLine1,30, BLACK);
	DrawText(life_text, xPxCol1,yPxLine2,30, BLACK);
	DrawText("Stage: ", xPxCol2,yPxLine1,30, BLACK);
	DrawText("Enemies: ", xPxCol2,yPxLine2,30, BLACK);
}
void drawWindow(char str_time[],struct Isaac isaac)
{
	BeginDrawing();//Inicia o ambiente de desenho na tela
	ClearBackground(RAYWHITE);//Limpa a tela e define cor de fundo
	drawMap();
	informationBar(str_time,isaac);
	EndDrawing();//Finaliza o ambiente de desenho na tela
}
#endif

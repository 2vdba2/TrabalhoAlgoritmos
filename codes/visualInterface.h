#ifndef VISUALINTERFACE_H
#define VISUALINTERFACE_H

#include "constants.h"
#include "structs.h"

void drawMap()
{
	int xpx,ypx;

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
		}
	}
}
void drawWindow()
{
	BeginDrawing();//Inicia o ambiente de desenho na tela
	ClearBackground(RAYWHITE);//Limpa a tela e define cor de fundo
	drawMap();
	EndDrawing();//Finaliza o ambiente de desenho na tela
}
#endif

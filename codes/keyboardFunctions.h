#ifndef KEYBOARDFUNCTIONS_H
#define KEYBOARDFUNCTIONS_H

#include "constants.h"
#include "structs.h"
#include <stdbool.h>

void readKeyboardShoot(struct Isaac isaac,struct Bullet bullets[])
{
	int i,j;
	i=isaac.posY;
	j=isaac.posX;
	if (IsKeyDown(KEY_UP))
	{
		if(map[i - 1][j] == ' ')
		{
			Atirar(bullets, j, i, 0, -1);
		}
	}

	if (IsKeyDown(KEY_DOWN))
	{
		if(map[i + 1][j] == ' ')
		{
			Atirar(bullets, j, i, 0, 1);
		}
	}

	if (IsKeyDown(KEY_LEFT))
	{
		if(map[i][j - 1] == ' ')
		{
			Atirar(bullets, j, i, -1, 0);
		}
	}

	if (IsKeyDown(KEY_RIGHT))
	{
		if(map[i][j + 1] == ' ')
		{
			Atirar(bullets, j, i, 1, 0);
		}
	}
}
void readKeyboardMove(struct Isaac *isaac,struct MapElement mapElements[N_MAP_ELEMENTS])
{
	if (IsKeyDown(KEY_D))
	{
		isaac->dx=1;
		isaac->dy=0;
		moveAndVerifyIsaac(isaac,mapElements);
	}
	if (IsKeyDown(KEY_A))
	{
		isaac->dx=-1;
		isaac->dy=0;
		moveAndVerifyIsaac(isaac,mapElements);
	}
	if (IsKeyDown(KEY_W))
	{
		isaac->dx=0;
		isaac->dy=-1;
		moveAndVerifyIsaac(isaac,mapElements);
	}
	if (IsKeyDown(KEY_S))
	{
		isaac->dx=0;
		isaac->dy=1;
		moveAndVerifyIsaac(isaac,mapElements);
	}
}
void readKeyboardLeaveBomb(struct Isaac *isaac)
{
	int lastX,lastY;
	lastX=isaac->posX-isaac->dx;
	lastY=isaac->posY-isaac->dy;
	if (IsKeyDown(KEY_E)&&isaac->nBombs>0)
	{
		if(map[lastY][lastX]==' ')
		{
			map[lastY][lastX]='b';
			isaac->nBombs-=1;
		}
	}
}
void readKeyboard(struct Isaac *isaac, struct Bullet bullets[],struct MapElement mapElements[N_MAP_ELEMENTS])
{
	readKeyboardMove(isaac,mapElements);
	readKeyboardLeaveBomb(isaac);
	readKeyboardShoot(*isaac,bullets);
}
#endif

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
void readKeyboardMove(struct Isaac *isaac)
{
	if (IsKeyDown(KEY_D))
	{
		moveAndVerify(1, 0, isaac);
	}
	if (IsKeyDown(KEY_A))
	{
		moveAndVerify(-1, 0, isaac);
	}
	if (IsKeyDown(KEY_W))
	{
		moveAndVerify(0, -1, isaac);
	}
	if (IsKeyDown(KEY_S))
	{
		moveAndVerify(0, 1, isaac);
	}
}

#endif

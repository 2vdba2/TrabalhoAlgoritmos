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
}
void readKeyboardMove(struct Isaac *isaac)
{
	if (IsKeyPressed(KEY_RIGHT))
	{
		moveAndVerify(1, 0, isaac);
	}
	if (IsKeyPressed(KEY_LEFT))
	{
		moveAndVerify(-1, 0, isaac);
	}
	if (IsKeyPressed(KEY_UP))
	{
		moveAndVerify(0, -1, isaac);
	}
	if (IsKeyPressed(KEY_DOWN))
	{
		moveAndVerify(0, 1, isaac);
	}
}

#endif

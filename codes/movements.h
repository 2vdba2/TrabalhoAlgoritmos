#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include "constants.h"
#include "structs.h"
#include <stdbool.h>

void move(int dx, int dy, struct Isaac *isaac)
{
	if(map[(*isaac).posY][(*isaac).posX]=='J')
		map[(*isaac).posY][(*isaac).posX]=' ';//replace previous position by ' ' empty if it was fire
	(*isaac).posX  =(*isaac).posX   +dx;
	(*isaac).posY  =(*isaac).posY   +dy;
	(*isaac).posXpx=(*isaac).posX*SQUARESIZE;
	(*isaac).posYpx=(*isaac).posY*SQUARESIZE;
	
	//se proxima posicao esta vazia, coloca J
	if(map[(*isaac).posY][(*isaac).posX]==' ')
	{
		map[(*isaac).posY][(*isaac).posX]='J';//update position
	}
}
int verifyMove(int dx, int dy, struct Isaac *isaac)
{
	int result=0;
	int xNext, yNext;

	xNext=(*isaac).posX   +dx;
	yNext=(*isaac).posY   +dy;

	if(map[yNext][xNext]==' ')
	{
		result=1;
	}
	else if(map[yNext][xNext]=='X')//fogueira (X)
	{
		(*isaac).nLifes-=1;
		result=1;
	}
	else if(map[yNext][xNext]=='I')//inimigo(I)
	{
		(*isaac).nLifes-=1;
		result=0;
	}
	else if(map[yNext][xNext]=='#')// parede (#) ou bomba (B)
	{
		result=0;
	}
	else if(map[yNext][xNext]=='B')
	{
		(*isaac).nBombs+=1;
		result=0;
	}
	else if(map[yNext][xNext]=='P')//portal
	{
		result=1;
	}
	//printf("\n%d",result);
	return result;
}
void moveAndVerify(int dx, int dy, struct Isaac *isaac)
{
	if(verifyMove(dx, dy, isaac))
	{
		move(dx, dy, isaac);
	}
}


void moveEnemy(struct Enemy *enemy)
{
	
	
	if(map[(*enemy).posY][(*enemy).posX]==(*enemy).id)
		map[(*enemy).posY][(*enemy).posX]=' ';//replace previous position by ' ' empty if it was fire
	(*enemy).posX  =(*enemy).posX   +(*enemy).dx;
	(*enemy).posY  =(*enemy).posY   +(*enemy).dy;
	(*enemy).posXpx=(*enemy).posX*SQUARESIZE;
	(*enemy).posYpx=(*enemy).posY*SQUARESIZE;
	
	//se proxima posicao esta vazia, coloca J
	if(map[(*enemy).posY][(*enemy).posX]==' ')
	{
		map[(*enemy).posY][(*enemy).posX]=(*enemy).id;//update position
	}
}
int verifyMoveEnemy(struct Enemy *enemy)
{
	int result=0;
	int xNext, yNext;

	xNext=(*enemy).posX   +(*enemy).dx;
	yNext=(*enemy).posY   +(*enemy).dy;

	if(map[yNext][xNext]==' ')
	{
		result=1;
	}
	else if(map[yNext][xNext]=='X')//fogueira (X)
	{
		result=1;
	}
	else if(map[yNext][xNext]=='I')//inimigo(I)
	{
		result=0;
	}
	else if(map[yNext][xNext]=='#')// parede (#) ou bomba (B)
	{
		result=0;
	}
	else if(map[yNext][xNext]=='B')
	{
		(*enemy).nLifes-=1;
		result=1;
	}
	else if(map[yNext][xNext]=='P')//portal
	{
		result=0;
	}
	//printf("\n%d",result);
	return result;
}

void moveAndVerifyEnemy(struct Enemy *enemy)
{
	if(verifyMoveEnemy(enemy))
	{
		moveEnemy(enemy);
	}
}

#endif

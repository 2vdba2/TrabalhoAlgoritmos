#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include "constants.h"
#include "structs.h"
#include <stdbool.h>

void move(struct Isaac *isaac)
{
	if(map[(*isaac).posY][(*isaac).posX]=='J')
		map[(*isaac).posY][(*isaac).posX]=' ';//replace previous position by ' ' empty if it was fire
	(*isaac).posX  =(*isaac).posX   +isaac->dx;
	(*isaac).posY  =(*isaac).posY   +isaac->dy;
	(*isaac).posXpx=(*isaac).posX*SQUARESIZE;
	(*isaac).posYpx=(*isaac).posY*SQUARESIZE;
	
	//se proxima posicao esta vazia, coloca J
	if(map[(*isaac).posY][(*isaac).posX]==' '||map[(*isaac).posY][(*isaac).posX]=='B')
	{
		map[(*isaac).posY][(*isaac).posX]='J';//update position
	}
}


int verifyMove(struct Isaac *isaac)
{
	int result=0;
	int xNext, yNext;

	xNext=(*isaac).posX   +isaac->dx;
	yNext=(*isaac).posY   +isaac->dy;

	if(map[yNext][xNext]==' ')
	{
		result=1;
	}
	else if(map[yNext][xNext]=='X')//fogueira (X)
	{
		(*isaac).nLifes-=1;(isaac);
		if(map[yNext+isaac->dy][xNext+isaac->dx]==' ')
		{
			isaac->dy*=2;
			isaac->dx*=2;
			result=1;
		}
		else
		{
			for(int i=-1;i<2||result==1;i++)
			{
				for(int j=-1;j<2||result==1;j++)
				{
					if(i!=0&&j!=0)
					{
						if(map[yNext+i][xNext+j]==' ')
						{
							isaac->dy+=i;
							isaac->dx+=j;
							result=1;
						}
					}
				}
			}
		}
	}
	else if(map[yNext][xNext]=='I')//inimigo(I)
	{
		(*isaac).nLifes-=1;(isaac);
		result=0;
	}
	else if(map[yNext][xNext]=='#')// parede (#) ou bomba (B)
	{
		result=0;
	}
	else if(map[yNext][xNext]=='B')//Inactive bomb
	{
		(*isaac).nBombs+=1;
		result=1;
	}
	else if(map[yNext][xNext]=='b')//active bomb
	{
		result=0;
	}
	else if(map[yNext][xNext]=='P'&&EnemiesAlive==0)//portal
	{
		result=1;
	}
	//printf("\n%d",result);
	return result;
}
void moveAndVerify(struct Isaac *isaac)
{
	if(verifyMove(isaac))
	{
		move(isaac);
	}
}


void moveEnemy(struct Enemy *enemy)
{
	
	
	if((*enemy).IsAlive){
		if(map[(*enemy).posY][(*enemy).posX]==(*enemy).id)
			map[(*enemy).posY][(*enemy).posX]=' ';//replace previous position by ' ' empty if it was fire

		(*enemy).posX  =(*enemy).posX   +(*enemy).dx;
		(*enemy).posY  =(*enemy).posY   +(*enemy).dy;
		(*enemy).posXpx=(*enemy).posX*SQUARESIZE;
		(*enemy).posYpx=(*enemy).posY*SQUARESIZE;
		
		//se proxima posicao esta vazia, coloca I
		if(map[(*enemy).posY][(*enemy).posX]==' ')
		{
			map[(*enemy).posY][(*enemy).posX]=(*enemy).id;//update position
		}
	}
	else if(map[(*enemy).posY][(*enemy).posX] == (*enemy).id){
			map[(*enemy).posY][(*enemy).posX]= ' ';
			(*enemy).id = ' ';
			EnemiesAlive--;
	}
		
}
int verifyMoveEnemy(struct Enemy *enemy,struct Isaac *isaac)
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
	else if(map[yNext][xNext]=='#')// parede (#) 
	{
		result=0;
	}
	else if(map[yNext][xNext]=='B')// Inactive Bomb
	{
		result=1;
	}
	else if(map[yNext][xNext]=='b')
	{
		(*enemy).IsAlive=false;
		map[yNext][xNext]=' ';
		result=1;
	}
	else if(map[yNext][xNext]=='o')
	{
		(*enemy).IsAlive=false;
		map[yNext][xNext]=' ';
		result=1;
	}
	else if(map[yNext][xNext]=='P')//portal
	{
		result=0;
	}
	else if(map[yNext][xNext]=='J')//Isaac
	{
		(*isaac).nLifes-=1;(isaac);
		result=0;
	}
	//printf("\n%d",result);
	return result;
}
//isaac cant be on fire, it skips it
/*
void skipFire(struct Isaac *isaac)
{
	xNext=(*isaac).posX   +isaac->dx;
	yNext=(*isaac).posY   +isaac->dy;
}
*/

void moveAndVerifyEnemy(struct Enemy *enemy,struct Isaac *isaac)
{
	if(verifyMoveEnemy(enemy,isaac))
	{
		moveEnemy(enemy);
	}
}

#endif

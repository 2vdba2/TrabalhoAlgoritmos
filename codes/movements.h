#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include "constants.h"
#include "structs.h"
#include <stdbool.h>

void moveIsaac(struct Isaac *isaac)
{
	//Dont empty isaac position only if it is on fire
	if(map[(*isaac).posY][(*isaac).posX]!='X')
		map[(*isaac).posY][(*isaac).posX]=' ';

	(*isaac).posX  =(*isaac).posX   +isaac->dx;
	(*isaac).posY  =(*isaac).posY   +isaac->dy;
	(*isaac).posXpx=(*isaac).posX*SQUARESIZE;
	(*isaac).posYpx=(*isaac).posY*SQUARESIZE;
	
	//If next position is empty or inactive bomb, position on map receives 'J'
	//this is necessary if next position is fire, it would erase it
	if(map[(*isaac).posY][(*isaac).posX]==' '||map[(*isaac).posY][(*isaac).posX]=='B')
	{
		map[(*isaac).posY][(*isaac).posX]='J';//update position
	}
}


int verifyMoveIsaac(struct Isaac *isaac,struct MapElement mapElements[N_MAP_ELEMENTS])
{
	int result=0;
	int xNext, yNext;

	xNext=(*isaac).posX   +isaac->dx;
	yNext=(*isaac).posY   +isaac->dy;
	
	for(int i=0;i<N_MAP_ELEMENTS;i++)
	{
		if(map[yNext][xNext]==mapElements[i].id)
		{
			result=mapElements[i].canIsaacMove;
			(*isaac).nLifes-=mapElements[i].doesItDamageIsaac;
			(*isaac).nBombs+=mapElements[i].isItInactiveBomb;
			jumpFire(isaac,mapElements[i].id);
		}
	}
	return result;
}
void moveAndVerifyIsaac(struct Isaac *isaac,struct MapElement mapElements[N_MAP_ELEMENTS])
{
	if(verifyMoveIsaac(isaac,mapElements))
	{
		moveIsaac(isaac);
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

void moveAndVerifyEnemy(struct Enemy *enemy,struct Isaac *isaac)
{
	if(verifyMoveEnemy(enemy,isaac))
	{
		moveEnemy(enemy);
	}
}
void jumpFire(struct Isaac *isaac, int *result, char id)
{
	//This function avoids isaac to be inside the fire (it would crash a save
	// in god mode if isaac is inside fire)
	// when it moves to a fireplace, it goes to the next position, keeping
	// the direction, or find an adjacent empty position
	if(id!='X')
		return;
	int xNext,yNext; //next x and y position of isaac
	
	xNext=isaac->posX   +isaac->dx;
	yNext=isaac->posY   +isaac->dy;

	//keeping dx dy direction, if position after fire is empty, Isaac goes there
	if(map[yNext+isaac->dy][xNext+isaac->dx]==' ')
	{
		isaac->dy*=2;
		isaac->dx*=2;
	}
	//Otherwise loop to find an empty position adjacent to fire
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
					}
				}
			}
		}
	}
}
#endif

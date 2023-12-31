#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include "constants.h"
#include "structs.h"
#include "mazeSolverFloydWarshall.h"
#include <stdbool.h>
#include "globals.h"

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
			jumpFireIsaac(isaac,&result,mapElements[i].id);

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

}
int verifyMoveEnemy(struct Enemy *enemy,struct Isaac *isaac,struct MapElement mapElements[N_MAP_ELEMENTS])
{
	int result=0;
	int xNext, yNext;

	xNext=(*enemy).posX   +(*enemy).dx;
	yNext=(*enemy).posY   +(*enemy).dy;

	if(enemy->IsAlive)
	{

		for(int i=0;i<N_MAP_ELEMENTS;i++)
		{
			if(map[yNext][xNext]==mapElements[i].id)
			{
				result=mapElements[i].canEnemyMove;
				//(*enemy).IsAlive=!mapElements[i].doesItDamageEnemy;
				jumpFireAndBombEnemy(enemy,&result,mapElements[i].id);
				if(mapElements[i].doesItDamageEnemy)
				{
					(*enemy).IsAlive=0;
					//This condition below
					if(map[(*enemy).posY][(*enemy).posX] == (*enemy).id)
					{
						map[(*enemy).posY][(*enemy).posX]= ' ';
					}
					(*enemy).id = ' ';
					EnemiesAlive--;
				}
				if(mapElements[i].id==mapElements[MAP_ELEMENT_ISAAC_NUMBER].id)
				{
					(*isaac).nLifes-=mapElements[MAP_ELEMENT_ENEMY_NUMBER].doesItDamageIsaac;
				}
				if(mapElements[i].id==mapElements[MAP_ELEMENT_ACTIVE_BOMB_NUMBER].id)
				{
					map[yNext][xNext]= ' ';
				}
			}
		}
	}
	/*
	else if(map[(*enemy).posY][(*enemy).posX] == (*enemy).id)
	{
			map[(*enemy).posY][(*enemy).posX]= ' ';
			(*enemy).id = ' ';
			EnemiesAlive--;
	}
	*/
	return result;
}

void moveAndVerifyEnemy(struct Enemy *enemy,struct Isaac *isaac,struct MapElement mapElements[N_MAP_ELEMENTS])
{
	if(verifyMoveEnemy(enemy,isaac,mapElements))
	{
		moveEnemy(enemy);
	}
}

void moveAndVerifyAllEnemies(struct Enemy enemies[MAX_ENEMIES],struct Isaac *isaac,struct MapElement mapElements[N_MAP_ELEMENTS], int *frame, int nEnemies, char nextMoveMatrix[V][V])
{
	int dxdy[2];//variable to store enemy next move
	if(*frame==0)
	{
		for(int i=0; i<nEnemies; i++)
		{
			// if enemy.isAlive is false and his id is 'I', it is the first time he has passed through this loop.
			// The function moveAndVerifyEnemy will declare his id as ' '
			if(enemies[i].IsAlive || enemies[i].id == 'I')
			{
				getDxdyFromNextMoveMatrix(dxdy,nextMoveMatrix[enemies[i].vertex][isaac->vertex]);
				enemies[i].dx=dxdy[0];
				enemies[i].dy=dxdy[1];
				moveAndVerifyEnemy(&enemies[i],isaac,mapElements);
				isaac->vertex=indexToVertex(isaac->posY,isaac->posX);
				enemies[i].vertex=indexToVertex(enemies[i].posY,enemies[i].posX);
			}
		}
		(*frame)++;
	}
	else
	{
		(*frame)++;
		if(*frame>=ENEMY_FRAMES_PER_MOVE)
		{
			*frame=0;
		}
	}
}

void jumpFireIsaac(struct Isaac *isaac, int *result, char id)
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
	*result=0;
	//keeping dx dy direction, if position after fire is empty, Isaac goes there
	if(map[yNext+isaac->dy][xNext+isaac->dx]==' ')
	{
		isaac->dy*=2;
		isaac->dx*=2;
		*result=1;
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
						*result=1;
					}
				}
			}
		}
	}
}

void jumpFireAndBombEnemy(struct Enemy *enemy, int *result, char id)
{
	//This function avoids enemy to be inside the fire and inactive bomb (it would crash a save
	// when enemy next move is fire or inactive bomb, it goes to the next position, keeping
	// the direction, or find an adjacent empty position
	if(id!='X'||id!='B')
		return;
	int xNext,yNext; //next x and y position of isaac
	
	xNext=enemy->posX   +enemy->dx;
	yNext=enemy->posY   +enemy->dy;
	*result=0;
	//keeping dx dy direction, if position after fire/inactivebomb is empty, enemy goes there
	if(map[yNext+enemy->dy][xNext+enemy->dx]==' ')
	{
		enemy->dy*=2;
		enemy->dx*=2;
		*result=1;
	}
	//Otherwise loop to find an empty position adjacent to fire/inactive bomb
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
						enemy->dy+=i;
						enemy->dx+=j;
						*result=1;
					}
				}
			}
		}
	}
}
#endif

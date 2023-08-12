#include <stdio.h>
#include "codes/manageFiles.h"
#include "codes/structs.h"
#define MAP_SIZE_Y 30 //number of lines
#define MAP_SIZE_X 60 //number of columns


int main()
{
	char map[MAP_SIZE_Y][MAP_SIZE_X];
	struct Isaac isaac;
	struct Enemy enemies[MAX_ENEMIES];
	struct Stopwatch *stopwatch = malloc(sizeof *stopwatch);
	int EnemiesAlive;
	struct Bullet bullets[MAX_BULLLETS];
	int map_counter;
	
	loadGame(map,enemies,&isaac,stopwatch,&EnemiesAlive,bullets,&map_counter);
	for(int i=0;i<MAP_SIZE_Y;i++)
	{
		for(int j=0;j<MAP_SIZE_X;j++)
		{
			printf("%c",map[i][j]);
		}
		printf("\n");
	}
	
	printf("\nisaac.x=%d",isaac.posX);
	printf("\nisaac.nBombs=%d",isaac.nBombs);

	for(int i=0;i<MAX_ENEMIES;i++)
	{
		printf("\nenemies[%d].x=%d",i,enemies[i].posX);
	}
	printf("\n");
	puts(stopwatch->str_time);
	printf("\nenemiesAlive=%d",EnemiesAlive);
	for(int i=0;i<MAX_ENEMIES;i++)
	{
		if(enemies[i].IsAlive)
			printf("\nenemies[%d].x=%d",i,enemies[i].posX);
	}
	for(int i=0;i<MAX_BULLLETS;i++)
	{
		if(bullets[i].IsAlive)
		{
			printf("\nbullets[%d].x=%d",i,bullets[i].posX);
		}
	}
	return 0;
}

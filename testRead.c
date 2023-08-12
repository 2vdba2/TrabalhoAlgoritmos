#include <stdio.h>
#include "codes/manageFiles.h"
#define MAP_SIZE_Y 30 //number of lines
#define MAP_SIZE_X 60 //number of columns


int main()
{
	char map[MAP_SIZE_Y][MAP_SIZE_X];
	loadGame(map);
	for(int i=0;i<MAP_SIZE_Y;i++)
	{
		for(int j=0;j<MAP_SIZE_X;j++)
		{
			printf("%c",map[i][j]);
		}
		printf("\n");
	}
	return 0;
}

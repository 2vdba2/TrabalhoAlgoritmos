#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "constants.h"

extern char map[MAP_SIZE_Y][MAP_SIZE_X]={' '};
int readMap(struct Isaac *isaac,struct Enemy *enemy1,int map_counter)
{
	FILE* filePointer;
	int lineLength = MAP_SIZE_X+3; //include \n\0
	char line[lineLength]; /* not ISO 90 compatible */
	int i=0,j=0;

	sprintf(mapFileNames,"maps/map02%d.txt",map_counter);
	filePointer = fopen(mapFileNames, "r");
	//filePointer = fopen("maps/mapa1.txt", "r");

	while(fgets(line, lineLength, filePointer)) {

		printf("\n");
		for(j=0;j<MAP_SIZE_X;j++)
		{
			map[i][j]=line[j];
			// get isaac initial position
			if(map[i][j]=='J')
			{
				//initial position
				(*isaac).posX=j;
				(*isaac).posY=i;
				(*isaac).posXpx=(*isaac).posX*SQUARESIZE;
				(*isaac).posYpx=(*isaac).posY*SQUARESIZE;
			}
			if(map[i][j]=='I')
			{
				//initial position
				(*enemy1).posX=j;
				(*enemy1).posY=i;
				(*enemy1).posXpx=(*enemy1).posX*SQUARESIZE;
				(*enemy1).posYpx=(*enemy1).posY*SQUARESIZE;
			}
		}
		i++;
	}

	fclose(filePointer);

	//PRINT MATRIX MAP

	printf("\n");
	for(i=0;i<MAP_SIZE_Y;i++)
	{
		for(j=0;j<MAP_SIZE_X;j++)
		{
			printf("%c",map[i][j]);
		}
		printf("\n");
	}

	return 0;
}

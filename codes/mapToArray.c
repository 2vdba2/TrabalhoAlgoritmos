#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "constants.h"

extern char map[MAP_SIZE_Y][MAP_SIZE_X]={' '};
int readMap(struct Isaac *isaac,int map_counter, struct Enemy *enemies, int *nEnemies)
{
	FILE* filePointer;
	int lineLength = MAP_SIZE_X+3; //include \n\0
	int enemiesCounter=0;
	char line[lineLength]; /* not ISO 90 compatible */
	int i=0,j=0;
	char mapFileName[19];

	sprintf(mapFileName,"./maps/map%02d.txt",map_counter+1);
	
	filePointer = fopen(mapFileName, "r");

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
				enemies[enemiesCounter].posX=j;
				enemies[enemiesCounter].posY=i;
				enemies[enemiesCounter].posXpx=enemies[enemiesCounter].posX*SQUARESIZE;
				enemies[enemiesCounter].posYpx=enemies[enemiesCounter].posY*SQUARESIZE;
				enemies[enemiesCounter].IsAlive= true;
				enemiesCounter++;
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
	*nEnemies=enemiesCounter;
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAP_SIZE_L 30 //number of lines
#define MAP_SIZE_C 60 //number of columns

extern char map[MAP_SIZE_L][MAP_SIZE_C]={' '};
int readMap()
{
	FILE* filePointer;
	int lineLength = MAP_SIZE_C+3; //include \n\0
	char line[lineLength]; /* not ISO 90 compatible */
	int i=0,j=0;

	filePointer = fopen("maps/mapa1.txt", "r");

	while(fgets(line, lineLength, filePointer)) {

		printf("\n");
		for(j=0;j<MAP_SIZE_C;j++)
		{
			map[i][j]=line[j];
		}
		i++;
	}

	fclose(filePointer);

	//PRINT MATRIX MAP

	printf("\n");
	for(i=0;i<MAP_SIZE_L;i++)
	{
		for(j=0;j<MAP_SIZE_C;j++)
		{
			printf("%c",map[i][j]);
		}
		printf("\n");
	}

	return 0;
}

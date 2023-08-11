#ifndef MAZESOLVERFLOYDWARSHALL_H
#define MAZESOLVERFLOYDWARSHALL_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "constants.h"
#include "structs.h"
#include <sys/stat.h>   // stat

#define NO_PARENT -1
#define NROWS 30
#define NCOLS 60
void mapToMaze(int maze[][MAP_SIZE_X])
{
	int i,j;

	for(i=0; i<MAP_SIZE_Y; i++)
	{
		for(j=0; j<MAP_SIZE_X; j++)
		{
			if(map[i][j]!='#')
			{
				maze[i][j]=0;
			}
			else
			{
				maze[i][j]=1;
			}
		}
	}
	//PRINT MAZE
	/*
	printf("\n");
	for(i=0;i<MAP_SIZE_Y;i++)
	{
		printf("[");
		for(j=0;j<MAP_SIZE_X;j++)
		{
			printf("%d,",maze[i][j]);
		}
		printf("],");
		printf("\n");
	}
	*/
}
void mazeToGraph(int maze[][NCOLS],int graph[][V])
{
	int lGraph, cGraph;
	int jAdj, iAdj;
	int i,j,di,dj;
	// INITIALIZE GRAPH
	for (i=0; i<V; i++)
	{
		for(j=0; j<V; j++)
		{
			graph[i][j]=INF;
		}
	}

	// Convert Maze to Graph
	//loop in maze values (0 = void, 1 = wall)
	for (i = 0; i < NROWS; i++) {
		for (j = 0; j < NCOLS; j++) {
			lGraph = i * NCOLS + j;
			//verify adjacent positions (vertically and horizontally)
			for (di = -1; di<2; di++) {
				for (dj = -1; dj<2; dj++) {
					//if ((di * dj) == 0) { //this avoids diagonal
						iAdj = i + di;

						jAdj = j + dj;
						cGraph = iAdj * NCOLS + jAdj;
						//verify if adjacent position is valid
						if (iAdj < NROWS && iAdj >= 0 && jAdj >= 0 && jAdj < NCOLS && maze[iAdj][jAdj] == 0 ) {//removed maze[i][j] == 0 then can start from wall=character
							//verify if start and end vertices are the same
							if (i==iAdj&&j==jAdj) {
								graph[lGraph][cGraph] = 0;
								//finally, include 1 in graph matrix if adjacent position is empty
							} else {
								graph[lGraph][cGraph] = 1;
							}
						}

					//}
				}
			}
		}
	}

}
void floydWarshall(int graph[][V], int dist[][V], int Next[][V])
{
	int i, j, k;
	//Initialize dist and Next
	for (int i=0; i<V; i++)
	{
		//printf("\n");
		for(int j=0; j<V; j++)
		{
			//printf("%d\t",graph[i][j]);
			dist[i][j]=graph[i][j]; //copy graph to dist
			if (graph[i][j] == INF)
			{
				Next[i][j] = -1;
			}
			else
			{
				Next[i][j] = j;
			}
		}
	}

	/* Add all vertices one by one to
	  the set of intermediate vertices.
	  ---> Before start of an iteration, we
	  have shortest distances between all
	  pairs of vertices such that the shortest
	  distances consider only the
	  vertices in set {0, 1, 2, .. k-1} as
	  intermediate vertices.
	  ----> After the end of an iteration,
	  vertex no. k is added to the set of
	  intermediate vertices and the set
	  becomes {0, 1, 2, .. k} */
	for (k = 0; k < V; k++) {
		// Pick all vertices as source one by one
		for (i = 0; i < V; i++) {
			// Pick all vertices as destination for the
			// above picked source
			for (j = 0; j < V; j++) {
				// If vertex k is on the shortest path from
				// i to j, then update the value of
				// dist[i][j]

				if (dist[i][k] + dist[k][j] < dist[i][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					Next[i][j] = Next[i][k];
				}
			}
		}
	}

	// Print the shortest distance matrix

}
char nextVertexToDirectionx(int startVertex,int nextVertex)
{
	int l0=startVertex/NCOLS;
	int c0=startVertex%NCOLS;
	int lf=nextVertex/NCOLS;
	int cf=nextVertex%NCOLS;
	char nextMove;
	int dx,dy;
	int k;
	dx=cf-c0;
	dy=lf-l0;
	//printf("\nstartVertex=%d;NextVertex=%d\n", startVertex,nextVertex);
	//printf("dx=%d, dy=%d\n",dx,dy);

	///////////////////
	// 1 -- 2 -- 3
	// 4 -- 5 -- 6
	// 7 -- 8 -- 9
	///////////////////
	//Enemy is at position 5 (center)
	// the number 2 means go up, 3 upright, 5 keep at position
	// 0 means no next move calculated

	if(nextVertex<0)
	{
		nextMove='0';
	}
	/*
	else
	{
		//maps the next move according to dx and dy
		k=1;
		for(int j=-1;j<2;j++)
		{
			for(int i=-1;i<2;i++)
			{
				if(dx==i&&dy==j)
				{
					nextMove=k+'0';//convert int to char (if 0<=int<10)
				}
				k++;
			}
			
		}
	}
	*/
	else if(dx==-1&&dy==-1)
	{
		nextMove='1';
	}
	else if(dx==0&&dy==-1)
	{
		nextMove='2';
	}
	else if(dx==1&&dy==-1)
	{
		nextMove='3';
	}
	else if(dx==-1&&dy==0)
	{
		nextMove='4';
	}
	else if(dx==0&&dy==0)
	{
		nextMove='5';
	}
	else if(dx==1&&dy==0)
	{
		nextMove='6';
	}
	else if(dx==-1&&dy==1)
	{
		nextMove='7';
	}
	else if(dx==0&&dy==1)
	{
		nextMove='8';
	}
	else if(dx==1&&dy==1)
	{
		nextMove='9';
	}
	//printf("nextMove: %c\n",nextMove);
	
	return nextMove;
	//printf("\ndx=%d",dxdy[0]);
	//printf("\ndy=%d",dxdy[1]);
}
void buildNextMoveMatrix(int Next[V][V],char nextMoveMatrix[V][V])
{
	int startVertex;

	for(int i=0; i<V; i++)
	{
		for(int j=0; j<V; j++)
		{
			nextMoveMatrix[i][j]=nextVertexToDirectionx(i,Next[i][j]);
		}
	}
}
int indexToVertex(int l, int c)
{
	return l*NCOLS+c;
}
/* A utility function to print solution */
void printNextMove(char nextMoveMatrix[V][V])
{
	printf("\n");
	for(int i=0; i<V; i++)
	{
		for(int j=0; j<V; j++)
		{
			printf("%c",nextMoveMatrix[i][j]);
		}
		printf("\n");
	}
}
void saveNextMoveMatrix(char nextMoveMatrix[V][V],int map_counter)
{
	char fileName[30];
	sprintf(fileName,"./chase/nextMoveMatrixMap%02d.txt",map_counter+1);
	FILE *f = fopen(fileName, "wb");
	if((f = fopen(fileName, "w")) == NULL)
	{
		printf("Unable to open file - quitting\n");
		return -1;
	};
	for(int i=0; i<V; i++)
	{
		for(int j=0; j<V; j++)
		{
			fprintf(f,"%c",nextMoveMatrix[i][j]);
		}
		fprintf(f,"\n\0");
	}
	fclose(f);
}
void loadNextMoveMatrix(char nextMoveMatrix[V][V],int map_counter)
{
	char fileName[30];
	sprintf(fileName,"./chase/nextMoveMatrixMap%02d.txt",map_counter+1);
	FILE* filePointer;
	int lineLength = V+3; //include \n\0
	char line[lineLength];
	filePointer = fopen(fileName, "r");
	int i=0;
	while(fgets(line, lineLength, filePointer))
	{
		for(int j=0;j<V;j++)
		{
			nextMoveMatrix[i][j]=line[j];
		}
		i++;
	}
}

void getDxdyFromNextMoveMatrix(int dxdy[2],char nextMove)
{
	int dx,dy;
	switch (nextMove)
	{
		case '1':
		{
			dx=-1;
			dy=-1;
			break;
		}
		case '2':
		{
			dx=0;
			dy=-1;
			break;
		}
		case '3':
		{
			dx=1;
			dy=-1;
			break;
		}
		case '4':
		{
			dx=-1;
			dy=0;
			break;
		}
		case '5':
		{
			dx=0;
			dy=0;
			break;
		}
		case '6':
		{
			dx=1;
			dy=0;
			break;
		}
		case '7':
		{
			dx=-1;
			dy=1;
			break;
		}
		case '8':
		{
			dx=0;
			dy=1;
			break;
		}
		case '9':
		{
			dx=1;
			dy=1;
			break;
		}
		case '0':
		{
			dx=0;
			dy=0;
			break;
		}
	}
	dxdy[0]=dx;
	dxdy[1]=dy;
}
int checkIfFileExists(int map_counter)
{
	//this function checks if there is file name copyMap(map_counter) in the chase folder.
	//we should do that to see if there are pre calculated moves for this map
	//1 if exist, 0 if doesnt
	int fileExist=0;
	char fileName[30];
	sprintf(fileName,"./chase/copyMap%02d.txt",map_counter+1);
	struct stat   buffer;
	if(stat (fileName, &buffer)==0)//0 if exist, -1 if doesnt
	{
		fileExist=1;
		printf("FILE  EXIST");
	}
	else
	{
		printf("FILE DOESNT EXIST");
		fileExist=0;
	}
	return fileExist;
}
int checkIfMapHasChanged(int map_counter)
{
	//check if map has changed
	char copyMap[ MAP_SIZE_Y ][ MAP_SIZE_X ];
	char fileName1[30];
	sprintf(fileName1,"./chase/copyMap%02d.txt",map_counter+1);

	FILE* filePointer1;
	int lineLength = 60+3; //include \n\0
	char line[lineLength];
	filePointer1 = fopen(fileName1, "r");
	int i=0;
	while(fgets(line, lineLength, filePointer1))
	{
		for(int j=0;j<60;j++)
		{
			copyMap[i][j]=line[j];
		}
		i++;
	}
	printf("\n");
	for(int i=0;i<MAP_SIZE_Y;i++)
	{
		for(int j=0;j<MAP_SIZE_X;j++)
		{
			printf("%c",copyMap[i][j]);
		}
		printf("\n");
	}
	fclose(filePointer1);
	int mapHasChanged=0;
	for(int i=0;i<MAP_SIZE_Y&&mapHasChanged==0;i++)
	{
		for(int j=0;j<MAP_SIZE_X&&mapHasChanged==0;j++)
		{
			if(map[i][j]!=copyMap[i][j])
			{
				mapHasChanged=1;
				printf("\nMAP HAS CHANGED");
			}
		}
		printf("\n");
	}
	return mapHasChanged;
}
int areEnemyMovesPreCalculated(int map_counter)
{
	int result=0;
	if(checkIfFileExists(map_counter)==1&&checkIfMapHasChanged(map_counter)==0)
	{
		result=1;
	}
	else
	{
		result=0;
	}
	/*
	if(checkIfFileExists(map_counter)==1)
	{
		if(checkIfMapHasChanged(map_counter)!=1)
		{
			printf("\nMAP HAS CHANGED");
			result=1;
		}
		else
		{
			printf("\nMAPDIDNT CHANGe");
		}
	}
	else
	{
		printf("\nFile DOESNT EXISTI");
	}
	*/
	return result;
}
void calculateEnemyMovesIfNeeded(int map_counter,int graph[][V], int dist[][V], int Next[][V],char nextMoveMatrix[V][V])
{
	//printf("\nFile exist= %d",checkIfFileExists(map_counter));
	//printf("\nMap has changed= %d",checkIfMapHasChanged(map_counter));
	//printf("\nenemy moves pre calculated= %d",areEnemyMovesPreCalculated(map_counter));
	if(areEnemyMovesPreCalculated(map_counter)==0)
	{
		printf("\nareEnemyMovesPreCalculated==0\n");
		floydWarshall(graph,dist,Next);
		buildNextMoveMatrix(Next,nextMoveMatrix);
		saveNextMoveMatrix(nextMoveMatrix,map_counter);
		char fileName[30];
		sprintf(fileName,"./chase/copyMap%02d.txt",map_counter+1);
		saveState(map_counter,fileName);
	}
	else
	{
		printf("\nareEnemyMovesPreCalculated==1\n");
		loadNextMoveMatrix(nextMoveMatrix,map_counter);



	}
}
void saveState(int map_counter,char fileName[30])

{
	//sprintf(fileName,"stateMap%02d.txt",map_counter+1);
	FILE *f = fopen(fileName, "wb");
	if((f = fopen(fileName, "w")) == NULL)
	{
		printf("Unable to open file - quitting\n");
		return -1;
	};
	for(int i=0; i<MAP_SIZE_Y; i++)
	{
		for(int j=0; j<MAP_SIZE_X; j++)
		{
			fprintf(f,"%c",map[i][j]);
		}
		fprintf(f,"\n\0");
	}
	fclose(f);

}
#endif

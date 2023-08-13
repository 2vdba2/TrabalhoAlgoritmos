#ifndef MAZESOLVERFLOYDWARSHALL_H
#define MAZESOLVERFLOYDWARSHALL_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "constants.h"
#include "structs.h"
#include <sys/stat.h>   // stat

void mapToMaze(int maze[][MAP_SIZE_X])
{
	//this function converts the map into a matrix of 0 and 1, named maze
	// 1 means walls
	// 0 means floor or No wall
	int i,j;
	
	//Loop for all map positions
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
void mazeToGraph(int maze[][MAP_SIZE_X],int graph[][V])
{
	//This function calculates the graph from maze
	//The graph is a matrix of costs from one position in the maze to another position
	
	//graph[nVertices][nVertices], where the line is start position and the column the end position

	// for going from vertex A to B
	// cost = 0, means A=B
	// cost = 1, means B is adjacent vertex of A
	// cost = 999 means it is impossible that an enemy can go from A to B in just one move
	//that means B is not adjacent of A, or B is a wall

	int lGraph; // line of graph, means start position
	int cGraph; // column of graph, means end position
	int jAdj, iAdj;
	int i,j,di,dj;
	// INITIALIZE GRAPH WITH INFINITE (999) cost
	for (i=0; i<V; i++)
	{
		for(j=0; j<V; j++)
		{
			graph[i][j]=INF;
		}
	}

	// Convert Maze to Graph
	//loop in maze values (0 = floor, 1 = wall)
	for (i = 0; i < MAP_SIZE_Y; i++) {
		for (j = 0; j < MAP_SIZE_X; j++) {
			lGraph = indexToVertex(i,  j);//convert line and column to vertex

			//loop for all adjacent positions
			for (di = -1; di<2; di++) {
				for (dj = -1; dj<2; dj++) {
					//if ((di * dj) == 0) { //this avoids diagonal
						iAdj = i + di;
						jAdj = j + dj;
						cGraph = indexToVertex(iAdj, jAdj); //convert line and column to vertex
						//verify if adjacent position is valid
						if (iAdj < MAP_SIZE_Y && iAdj >= 0 && jAdj >= 0 && jAdj < MAP_SIZE_X && maze[iAdj][jAdj] == 0 ) 
						{
							//verify if start and end vertices are the same
							if (i==iAdj&&j==jAdj)
							{
								graph[lGraph][cGraph] = 0;
							}
							//include 1 (cost to go to next vertex) in graph matrix 
							else
							{
								graph[lGraph][cGraph] = 1;
							}
						}

					//}//this would avoid diagonal
				}
			}
		}
	}

}
void floydWarshall(int graph[][V], int dist[][V], int Next[][V])
{
	//using floydWarshal routine, This function calculates the matrix of
	// next moves and the matrix of distances
	
	//Example: for going from vertex A to B
	// next move matrix: for any A (line) to any B(column) what is the
	// next vertex to achieve B with the lowest cost
	//distance matrix: matrix of total cost from A to B. In our case, it
	//means the number os "steps" the enemy will take to go from A to B  
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
				//-1 means it is impossible to go from vertex i to j in
				//in one move
				Next[i][j] = -1;
			}
			else
			{
				//in our case, this condition means i and j are adjacent
				// or equal
				Next[i][j] = j;
			}
		}
	}

	// For going from vertex i to j, there is a distance dist[i][j]
	// verify if there is an intermediate vertex k that lower 
	// the distance from i to j
	// then update distance (dist) and next vertex to go (Next)
	
	//loop for all intermediate vertices
	for (k = 0; k < V; k++) {
		// loop for all start vertices
		for (i = 0; i < V; i++) {
			//loop for all end vertices
			for (j = 0; j < V; j++) {
				// If vertex k is on the shortest path from
				// i to j, then update the value of
				// dist[i][j] and Next[i][j]

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
char nextVertexToDirection(int startVertex,int nextVertex)
{
	int l0=startVertex/MAP_SIZE_X;
	int c0=startVertex%MAP_SIZE_X;
	int lf=nextVertex/MAP_SIZE_X;
	int cf=nextVertex%MAP_SIZE_X;
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
			nextMoveMatrix[i][j]=nextVertexToDirection(i,Next[i][j]);
		}
	}
}
int indexToVertex(int l, int c)
{
	return l*MAP_SIZE_X+c;
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
	//this function converts back next move matrix to dxdy
	///////////////////        (dx, dy)
	// 1 -- 2 -- 3           (-1,-1) -- (0,-1) -- (1,-1)
	// 4 -- 5 -- 6    --->   (-1,0)  -- (0,0)  -- (1,0)
	// 7 -- 8 -- 9           (-1,1)  -- (0,1)  -- (1,1) 
	///////////////////
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
	
	//Original map
	char originalMap[ MAP_SIZE_Y ][ MAP_SIZE_X ];
	char fileName1[30];
	sprintf(fileName1,"./maps/map%02d.txt",map_counter+1);
	FILE* filePointer1;
	int lineLength = 60+3; //include \n\0
	char line[lineLength];
	filePointer1 = fopen(fileName1, "r");
	int i=0;
	while(fgets(line, lineLength, filePointer1))
	{
		for(int j=0;j<60;j++)
		{
			originalMap[i][j]=line[j];
		}
		i++;
	}
	printf("\n");
	fclose(filePointer1);


	//Copy of Map
	char copyMap[ MAP_SIZE_Y ][ MAP_SIZE_X ];
	sprintf(fileName1,"./chase/copyMap%02d.txt",map_counter+1);
	filePointer1 = fopen(fileName1, "r");
	i=0;
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
			if(originalMap[i][j]!=copyMap[i][j])
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
	// For a given map, this function verifies if enemy moves are already calculated by
	// by seeing if the there is copy of the map in chase folder and
	// if the map has changed
	
	int result=0;
	if(checkIfFileExists(map_counter)==1&&checkIfMapHasChanged(map_counter)==0)
	{
		result=1;
	}
	else
	{
		result=0;
	}
	return result;
}

void calculateEnemyMovesIfNeeded(int map_counter,char nextMoveMatrix[V][V])
{
	static int graph[V][V];
	static int dist[V][V];
	static int Next[V][V];
	static int path[V];
	static int maze[MAP_SIZE_Y][MAP_SIZE_X];
	//this function calculates enemy moves if they arent calculated already for a given map
	if(areEnemyMovesPreCalculated(map_counter)==0)
	{
		mapToMaze(maze);
		mazeToGraph(maze,graph);
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
//This function saves the state of the game (variable map) into a file
{
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

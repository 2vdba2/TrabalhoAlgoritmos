#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "constants.h"
#include "structs.h"

#define NO_PARENT -1
#define NROWS 30
#define NCOLS 60

void printPath(int currentVertex, int* parents, int nVertices,int i) {
    if (currentVertex == NO_PARENT) {
		
        return;
    }
    if(i==1)
    {
    printf("\ni=%d, V=%d\n",i,currentVertex);
	}
    printPath(parents[currentVertex], parents, nVertices,i+1);
    printf("%d ", currentVertex);
}
int printFirstPath(int startVertex, int endVertex,int* parents, int nVertices, int* distances) {
    int path[nVertices];
    
	if (parents[endVertex] == -1)
	{
		return;
	}
	
	int distance=distances[endVertex];
	int i=distance;
	int u=endVertex;
	path[i] = u;
	//printf("%d",u);
	while (u !=  startVertex){
		u = parents[u];
		i--;
		path[i]=u;
		
	}

	for(int i=0;i<=distance;i++)
	{
		printf("%d",path[i]);
		if(i!=distance)
		{
			printf("-->");
		}
	}
	printf("\nNext vertex: %d",path[1]);
	return path[1]; 
}

void printSolution(int startVertex, int* distances, int* parents, int nVertices, int endVertex) {
    printf("\nVertex\t Distance\tPath");
    for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++) {
        if (vertexIndex != startVertex && vertexIndex==endVertex) {
            printf("\n%d -> ", startVertex);
            printf("%d \t\t ", vertexIndex);
            printf("%d\t\t", distances[vertexIndex]);
            printPath(vertexIndex, parents, nVertices,0);
        }
    }
}

void dijkstra(int** adjacencyMatrix, int startVertex, int nVertices, int endVertex, int *dxdy) {
    static int distances[V];
    static int parents[V];
    static int  visited[V];

    for (int i = 0; i < nVertices; i++) {
        distances[i] = INT_MAX;
        parents[i] = NO_PARENT;
        visited[i] = 0;
    }

    distances[startVertex] = 0;

    for (int i = 0; i < nVertices - 1; i++) {
        int minDistance = INT_MAX;
        int minIndex = -1;

        for (int j = 0; j < nVertices; j++) {
            if (!visited[j] && distances[j] < minDistance) {
                minDistance = distances[j];
                minIndex = j;
            }
        }

        int u = minIndex;
        visited[u] = 1;

        for (int v = 0; v < nVertices; v++) {
            if (!visited[v] && adjacencyMatrix[u][v] && distances[u] != INT_MAX &&
                distances[u] + adjacencyMatrix[u][v] < distances[v]) {
                distances[v] = distances[u] + adjacencyMatrix[u][v];
                parents[v] = u;
            }
        }
    }
	
    printSolution(startVertex, distances, parents, nVertices, endVertex);
    int nextVertex = printFirstPath(startVertex, endVertex,parents, nVertices, distances);
    //int dxdy[2];
    nextVertexToDirection(startVertex,nextVertex, dxdy);

    //return  dxdy[0];//next step


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
}

void nextVertexToDirection(int startVertex,int nextVertex, int dxdy[])
{
	int l0=startVertex/NCOLS;
	int c0=startVertex%NCOLS-1;
	int lf=nextVertex/NCOLS;
	int cf=nextVertex%NCOLS-1;
	
	dxdy[0]=cf-c0;
	dxdy[1]=lf-l0;
	
	printf("\ndx=%d",dxdy[0]);
	printf("\ndy=%d",dxdy[1]);
	
	
}

int indexToVertex(int l, int c)
{
	return l*NCOLS+c;
}

void enemyMove(struct Isaac isaac, struct Enemy *enemy)
{
	static int graph[V][V];
	static int dist[V][V];
	static int Next[V][V];
	static int path[V];
	int nVertices=V;
	static int maze[MAP_SIZE_Y][MAP_SIZE_X];
	mapToMaze(maze);
	mazeToGraph(maze,graph);
    int** adjacencyMatrix = (int**)malloc(nVertices * sizeof(int*));
    for (int i = 0; i < nVertices; i++) {
        adjacencyMatrix[i] = (int*)malloc(nVertices * sizeof(int));
    }

    for (int i = 0; i < nVertices; i++) {
        for (int j = 0; j < nVertices; j++) {
            adjacencyMatrix[i][j]=graph[i][j];
        }
    }
    int dxdy[2];
    
    int vertexIsaac = indexToVertex(isaac.posY, isaac.posX);
	int vertexEnemy = indexToVertex((*enemy).posY, (*enemy).posX);
    
    dijkstra(adjacencyMatrix, vertexEnemy, V, vertexIsaac, dxdy);
	

	(*enemy).dx=dxdy[0];
	(*enemy).dy=dxdy[1];
}

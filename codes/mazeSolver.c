#include <stdio.h>
#define NROWS 2
#define NCOLS 2
#define INF 999
#define V ( NROWS * NCOLS )

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
					if ((di * dj) == 0) { //this avoids diagonal
						iAdj = i + di;

						jAdj = j + dj;
						cGraph = iAdj * NCOLS + jAdj;
						//verify if adjacent position is valid
						if (iAdj < NROWS && iAdj >= 0 && jAdj >= 0 && jAdj < NCOLS && maze[iAdj][jAdj] == 0 && maze[i][j] == 0) {
							//verify if start and end vertices are the same
							if (i==iAdj&&j==jAdj) {
								graph[lGraph][cGraph] = 0;
								//finally, include 1 in graph matrix if adjacent position is empty
							} else {
								graph[lGraph][cGraph] = 1;
							}
						}

					}
				}
			}
		}
	}

}
void printSolution(int dist[][V])
{
	printf("\n");
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INF)
				printf("%7s", "INF");
			else
				printf("%7d", dist[i][j]);
		}
		printf("\n");
	}
}
void floydWarshall(int dist[][V], int Next[][V])
{
	int i, j, k;

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

/* A utility function to print solution */

int main()
{
	/*
	int maze[10][10]=	{	{0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
							{0, 1, 0, 1, 0, 0, 0, 1, 0, 0},
							{0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
							{1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
							{0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
							{0, 1, 0, 0, 0, 0, 1, 0, 1, 1},
							{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
							{0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
							{0, 0, 1, 1, 1, 1, 0, 1, 1, 0}};
	*/
	int maze[2][2]=	{	{0, 1},{ 0, 0}};

	int graph[V][V], dist[V][V], Next[V][V];

	mazeToGraph(maze,graph);
	printf("\nMaze");
	for (int i=0; i<NROWS; i++)
	{
		printf("\n");
		for(int j=0; j<NCOLS; j++)
		{
			printf("%d\t",maze[i][j]);

		}
	}

	//print graph and initalize dist and next
	printf("\nGraph");
	for (int i=0; i<V; i++)
	{
		printf("\n");
		for(int j=0; j<V; j++)
		{
			printf("%d\t",graph[i][j]);
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
	printf("\nNext0");
	printSolution(Next);
	floydWarshall(graph,Next);
	printf("\ndist");
	printSolution(dist);
	printf("\nNextF");
	printSolution(Next);
	return 0;
}

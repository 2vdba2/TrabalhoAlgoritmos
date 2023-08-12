#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SQUARESIZE 20
#define BULLETSIZE (20 / 2)
#define MAP_SIZE_Y 30 //number of lines
#define MAP_SIZE_X 60 //number of columns
#define MAP_SIZE_X_PX (MAP_SIZE_X * SQUARESIZE)
#define MAP_SIZE_Y_PX (MAP_SIZE_Y * SQUARESIZE)
#define MAX_BULLLETS 100
#define INFORMATION_BAR_X_PX (MAP_SIZE_X_PX)
#define INFORMATION_BAR_Y_PX (MAP_SIZE_Y_PX / 4)
#define V (MAP_SIZE_X * MAP_SIZE_Y)
#define INF 999
#define MAX_ENEMIES 15
#define N_MAP_ELEMENTS 9 // #,I,J,o,X,b,B,P,' '
#define MAP_ELEMENT_PORTAL_NUMBER 5

extern int EnemiesAlive = 0;
extern int orderToSaveGame = 0;
extern int orderToLoadGame = 0;
extern GameState gameState = GAME;

#endif

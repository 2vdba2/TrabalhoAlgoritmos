#ifndef GLOBALS_H
#define GLOBALS_H

#include "constants.h"

extern int EnemiesAlive = 0;
extern int orderToNewGame = 0;
extern int orderToSaveGame = 0;
extern int orderToLoadGame = 0;
extern int gameMessageOn = 0;
extern int godMode = 0;
extern int closeGame = 0;
extern char map[MAP_SIZE_Y][MAP_SIZE_X]={' '};
#endif

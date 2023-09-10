#ifndef KEYBOARDFUNCTIONS_H
#define KEYBOARDFUNCTIONS_H

#include "constants.h"
#include "structs.h"
#include "globals.h"
#include <stdbool.h>

// This file contains functions for reading keyboard inputs and performing corresponding actions.

// Function to detect pressed keys for shooting
void readKeyboardShoot(struct Isaac isaac,struct Bullet bullets[])
{
    int i,j;
    i=isaac.posY;
    j=isaac.posX;
    if (IsKeyDown(KEY_UP))
    {
        if(map[i - 1][j] == ' ')
        {
            Shoot(bullets, j, i, 0, -1);
        }
    }

    if (IsKeyDown(KEY_DOWN))
    {
        if(map[i + 1][j] == ' ')
        {
            Shoot(bullets, j, i, 0, 1);
        }
    }

    if (IsKeyDown(KEY_LEFT))
    {
        if(map[i][j - 1] == ' ')
        {
            Shoot(bullets, j, i, -1, 0);
        }
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        if(map[i][j + 1] == ' ')
        {
            Shoot(bullets, j, i, 1, 0);
        }
    }
}

// Function to read movement inputs
void readKeyboardMove(struct Isaac *isaac,struct MapElement mapElements[N_MAP_ELEMENTS])
{
    if (IsKeyDown(KEY_D))
    {
        isaac->dx=1;
        isaac->dy=0;
        moveAndVerifyIsaac(isaac,mapElements);
    }
    if (IsKeyDown(KEY_A))
    {
        isaac->dx=-1;
        isaac->dy=0;
        moveAndVerifyIsaac(isaac,mapElements);
    }
    if (IsKeyDown(KEY_W))
    {
        isaac->dx=0;
        isaac->dy=-1;
        moveAndVerifyIsaac(isaac,mapElements);
    }
    if (IsKeyDown(KEY_S))
    {
        isaac->dx=0;
        isaac->dy=1;
        moveAndVerifyIsaac(isaac,mapElements);
    }

}

// Function to read special command inputs
void readKeyboardSpecialKeys(struct MapElement mapElements[N_MAP_ELEMENTS],struct Stopwatch *stopwatch, GameState *gameState)
{
    // Load Game
    if (IsKeyDown(KEY_L))
    {
        orderToLoadGame = 1;
    }
    // Save game
    if (IsKeyDown(KEY_O))
    {
        orderToSaveGame = 1;
    }
    // God mode
    if (IsKeyPressed(KEY_G))
    {
        printf("god mode on");
        if(godMode == 1)
        {
            godMode = 0;
            mapElements[MAP_ELEMENT_ENEMY_NUMBER].doesItDamageIsaac = 1;
            mapElements[MAP_ELEMENT_ISAAC_NUMBER].doesItDamageEnemy = 0;
            mapElements[MAP_ELEMENT_ISAAC_NUMBER].canEnemyMove = 0;
            mapElements[MAP_ELEMENT_FIRE_NUMBER].doesItDamageIsaac = 1;

            printf("god mode off");
        }
        else if(godMode == 0)
        {
            mapElements[MAP_ELEMENT_ENEMY_NUMBER].doesItDamageIsaac = 0;
            mapElements[MAP_ELEMENT_ISAAC_NUMBER].doesItDamageEnemy = 1;
            mapElements[MAP_ELEMENT_ISAAC_NUMBER].canEnemyMove = 1;
            mapElements[MAP_ELEMENT_FIRE_NUMBER].doesItDamageIsaac = 0;
            godMode = 1;
            printf("god mode on");
        }
    }
    // Go to Menu
    
    if (IsKeyPressed(KEY_ESCAPE))
    {
        // Toggle the game state between GAME and MENU
        if (*gameState == GAME || *gameState == MESSAGE)
        {
            *gameState = MENU;
        }
        else if (*gameState == MENU && gameMessageOn)
        {
            *gameState = MESSAGE;
        }
        else if (*gameState == MENU)
        {
            restart_chronometer(stopwatch);
            *gameState = GAME;
        }
    }
    if (IsKeyPressed(KEY_R)){
        *gameState = WarningMenu;
    }
    
}

// Function to read input for leaving a bomb
void readKeyboardLeaveBomb(struct Isaac *isaac)
{
    int lastX,lastY;
    lastX=isaac->posX-isaac->dx;
    lastY=isaac->posY-isaac->dy;
    if (IsKeyDown(KEY_E) && isaac->nBombs > 0)
    {
        if(map[lastY][lastX] == ' ')
        {
            map[lastY][lastX] = 'b';
            isaac->nBombs -= 1;
        }
    }
}

// Function to read all keyboard inputs
void readKeyboard(struct Isaac *isaac, struct Bullet bullets[], struct MapElement mapElements[N_MAP_ELEMENTS], struct Stopwatch *stopwatch)
{
    readKeyboardMove(isaac,mapElements);
    readKeyboardLeaveBomb(isaac);
    readKeyboardShoot(*isaac,bullets);
    // readKeyboardSpecialKeys(mapElements,stopwatch);
}

#endif

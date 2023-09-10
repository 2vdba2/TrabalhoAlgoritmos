#ifndef VISUALINTERFACE_H
#define VISUALINTERFACE_H

#include "constants.h"
#include "structs.h"
#include <string.h>
#include <raylib.h>
#include "initializeVariables.h"
#include <stdlib.h>

// Function to draw the map on the screen
void drawMap(struct MapElement mapElements[N_MAP_ELEMENTS])
{
	int xpx,ypx;
	for(int k=0; k<N_MAP_ELEMENTS; k++)
	{
		for(int i=0; i<MAP_SIZE_Y; i++)
		{
			for(int j=0; j<MAP_SIZE_X; j++)
			{
				xpx=j*SQUARESIZE;
				ypx=i*SQUARESIZE;

				//draw background on all map first because MAP_ELEMENT_BACKGROUND_NUMBER==0
				// and then draw other elements, because they have some transparents parts
				if(map[i][j]==mapElements[k].id||k==MAP_ELEMENT_BACKGROUND_NUMBER)
				{
					DrawTexture(mapElements[k].sprite,xpx, ypx, WHITE);
				}
			}

		}
	}
}

// Function to draw the information bar
void informationBar(struct Isaac isaac, struct InformationBarStrings informationBarStrings)
{
    int xPxCol1  = INFORMATION_BAR_X_PX / 30;
    int xPxCol2  = xPxCol1 + INFORMATION_BAR_X_PX / 2.6;
    int xPxCol3  = xPxCol1 + INFORMATION_BAR_X_PX / 1.25;
    int yPxLine1 = MAP_SIZE_Y_PX + INFORMATION_BAR_Y_PX / 6;
    int yPxLine2 = yPxLine1 + INFORMATION_BAR_Y_PX / 4;
    int yPxLine3 = yPxLine1 + INFORMATION_BAR_Y_PX / 2;

    // draw the information bar
    DrawRectangle(0, MAP_SIZE_Y_PX, INFORMATION_BAR_X_PX, INFORMATION_BAR_Y_PX, BLACK);

    //draw the information 
    DrawText(informationBarStrings.timeText, xPxCol1, yPxLine1, 30, RED);
    DrawText(informationBarStrings.lifeText, xPxCol1, yPxLine3, 30, RED);
    DrawText(informationBarStrings.stageText, xPxCol3, yPxLine1, 30, RED);
    DrawText(informationBarStrings.enemiesText, xPxCol3, yPxLine3, 30, RED);
    DrawText(informationBarStrings.bombsText, xPxCol2, yPxLine2, 30, RED);

    if(godMode == 1)
    {
        DrawText("GOD MODE ON", xPxCol2, yPxLine3, 30, RED);
    }
}

// Function to create the strings for the information bar
void createInformationBarStrings(struct Stopwatch stopwatch, struct Isaac isaac, int map_counter, struct InformationBarStrings *informationBarStrings, int EnemiesAlive)
{
    sprintf(informationBarStrings->lifeText, "Lifes: %d", isaac.nLifes);
    sprintf(informationBarStrings->timeText, "Time alive: %s", stopwatch.str_time);
    sprintf(informationBarStrings->stageText, "Stage: %d", map_counter + 1);
    sprintf(informationBarStrings->enemiesText, "Enemies: %d", EnemiesAlive);
    sprintf(informationBarStrings->bombsText, "Bombs: %d", isaac.nBombs);
}

// Function to draw the game window
void drawWindow(char str_time[], struct Isaac isaac, struct Stopwatch stopwatch, int map_counter, struct InformationBarStrings *informationBarStrings, int EnemiesAlive, struct MapElement mapElements[N_MAP_ELEMENTS])
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    drawMap(mapElements);
    createInformationBarStrings(stopwatch, isaac, map_counter, informationBarStrings, EnemiesAlive);
    informationBar(isaac, *informationBarStrings);
    EndDrawing();
}

// Enum for the main menu options
typedef enum {
    NOVO_JOGO,
    CARREGAR_JOGO,
    SAIR
} MenuItem;

// Array with the texts of the main menu options
const char MenuItemStrings[][20] = {
    "Novo Jogo",
    "Carregar Jogo",
    "Sair"
};

// Variable indicating the selected option in the main menu
MenuItem currentMenuItem = NOVO_JOGO;

// Function to draw menu
void DrawMenu()
{
    ClearBackground(RAYWHITE);

    // Draw the game title
    DrawText("The Binding of Isaac", MAP_SIZE_X_PX / 2 - MeasureText("The Binding of Isaac", 40) / 2, 80, 40, DARKGRAY);

    for(int i = 0; i < 3; i++)
    {
        if(i == currentMenuItem)
        {
            // Draw the selected option
            DrawText("> ", MAP_SIZE_X_PX / 2 - MeasureText("> ", 30) / 2, (200 + (50 * i)), 30, GRAY);
        }
        DrawText(MenuItemStrings[i], MAP_SIZE_X_PX / 2 - MeasureText(MenuItemStrings[i], 30) / 2, (200 + (50 * i)), 30, GRAY);
    }

    DrawText("Use as setas para navegar e pressione enter para selecionar", 50, MAP_SIZE_Y_PX - 50, 20, DARKGRAY);
}

// function to Main Menu
void Menu()
{
    if(IsKeyPressed(KEY_N)) {
        currentMenuItem = NOVO_JOGO;
    } else if(IsKeyPressed(KEY_C)) {
        currentMenuItem = CARREGAR_JOGO;
    } else if(IsKeyPressed(KEY_Q)) {
        currentMenuItem = SAIR;
    }

    if(IsKeyPressed(KEY_DOWN)) {
        currentMenuItem = (currentMenuItem + 1) % 3;
    } else if(IsKeyPressed(KEY_UP)) {
        currentMenuItem = (currentMenuItem - 1 + 3) % 3;
    }

    if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    {
        switch(currentMenuItem)
        {
            case NOVO_JOGO:
                NewGame();
                break;
            case CARREGAR_JOGO:
                orderToLoadGame = 1;
                NewGame();
                break;
            case SAIR:
                CloseWindow();
                break;
        }
    }

    BeginDrawing();
    DrawMenu();
    EndDrawing();
}

// Enum for in-game menu options
typedef enum {
    INGAME_NOVO_JOGO,
    INGAME_SALVAR_JOGO,
    INGAME_CARREGAR_JOGO,
    INGAME_VOLTAR,
    INGAME_SAIR,
} InGameMenuItem;

// Array with the texts of in-game menu options
const char InGameMenuItemStrings[][20] = {
    "Novo Jogo",
    "Salvar Jogo",
    "Carregar Jogo",
    "Voltar",
    "Sair"
};

// Variable indicating the selected option in the in-game menu
InGameMenuItem currentInGameMenuItem = INGAME_NOVO_JOGO;

// Function to draw the in-game menu
void InGameMenu(GameState *gameState, struct Stopwatch *stopwatch)
{
    if(IsKeyPressed(KEY_N)) {
        currentInGameMenuItem = INGAME_NOVO_JOGO;
    } else if(IsKeyPressed(KEY_C)) {
        currentInGameMenuItem = INGAME_CARREGAR_JOGO;
    } else if(IsKeyPressed(KEY_S)) {
        currentInGameMenuItem = INGAME_SALVAR_JOGO;
    } else if(IsKeyPressed(KEY_Q)) {
        currentInGameMenuItem = INGAME_SAIR;
    } else if(IsKeyPressed(KEY_V)) {
        currentInGameMenuItem = INGAME_VOLTAR;
    }

    if(IsKeyPressed(KEY_DOWN)) {
        currentInGameMenuItem = (currentInGameMenuItem + 1) % 5;
    } else if(IsKeyPressed(KEY_UP)) {
        currentInGameMenuItem = (currentInGameMenuItem - 1 + 5) % 5;
    }

    if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    {
        switch(currentInGameMenuItem)
        {
            case INGAME_NOVO_JOGO:
                NewGame();
                break;
            case INGAME_SALVAR_JOGO:
                QuickSaveGame();
                break;
            case INGAME_CARREGAR_JOGO:
                orderToLoadGame = 1;
                break;
            case INGAME_SAIR:
                CloseWindow();
                break;
            case INGAME_VOLTAR:
                if(gameMessageOn)
                {
                    *gameState = MESSAGE;
                    restart_chronometer(stopwatch);
                }
                else
                {
                    *gameState = GAME;
                    restart_chronometer(stopwatch);
                }
                break;
        }
    }

    BeginDrawing();
    DrawMenu(InGameMenuItemStrings, InGameMenuItemStrings[currentInGameMenuItem], 5);
    EndDrawing();
}

// Confirmation menu to restart the game
int AreYouSureMenuIndex = 0;

int AreYouSureMenu()
{
    if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        AreYouSureMenuIndex = (AreYouSureMenuIndex + 1) % 2;
    }

    if(IsKeyPressed(KEY_ENTER))
    {
        if(AreYouSureMenuIndex == 1)
        {
            return 1; // return 1 if player select "Sim"
        }
        if(AreYouSureMenuIndex == 0)
        {
            return 0; // return 1 if player select "Não"
        }
    }

	Color YesColor;
	Color NoColor;

	if (AreYouSureMenuIndex == 1)
	{
		YesColor = DARKGRAY;
		NoColor = LIGHTGRAY;
	}
	else if (AreYouSureMenuIndex == 0)
	{
		YesColor = LIGHTGRAY;
		NoColor = DARKGRAY;
	}

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Você tem certeza que quer recomeçar o jogo?", MAP_SIZE_X_PX / 2 - MeasureText("Você tem certeza que quer recomeçar o jogo?", 40) / 2, 200, 40, GRAY);

    DrawRectangle(MAP_SIZE_X_PX / 2 - 60, 250, 120, 40, YesColor);
    DrawRectangle(MAP_SIZE_X_PX / 2 - 60, 300, 120, 40, NoColor);

    DrawText("Sim", MAP_SIZE_X_PX / 2 - MeasureText("Sim", 30) / 2, 255, 30, RAYWHITE);
    DrawText("Não", MAP_SIZE_X_PX / 2 - MeasureText("Não", 30) / 2, 305, 30, RAYWHITE);

    EndDrawing();

    return 2; 
}

void drawScore(char str_time[],struct Isaac isaac,struct Stopwatch stopwatch, int map_counter,  struct InformationBarStrings *informationBarStrings, int EnemiesAlive,struct MapElement mapElements[N_MAP_ELEMENTS])
{	
	char name[30];	
	char pressEnter[50]={"Press enter to continue..."};
	int score;
	int posX, posY, width,  height;
	score=3600-stopwatch.elapsed_time;
	if(score<0)
	{
		score=0;
	}
	
	sprintf(name,"You won! Your score is %d",score);
	//draw information bar strings
	BeginDrawing();
	ClearBackground(RAYWHITE);
	//draw map in background
	drawMap(mapElements);
	createInformationBarStrings(stopwatch,isaac, map_counter,informationBarStrings,EnemiesAlive);
	informationBar(isaac,*informationBarStrings);
	
	
	//Draw Score
	
	posX=MAP_SIZE_X_PX / 2 - MeasureText(name, 50) / 2-10;
	posY=MAP_SIZE_Y_PX / 2-10;
	width=MeasureText(name, 50)+20;
	height=50+20;
	
	DrawRectangle(posX,posY,width,height,BLACK); // draw background
	DrawText(name, MAP_SIZE_X_PX / 2 - MeasureText(name, 50) / 2, MAP_SIZE_Y_PX / 2, 50, RED);
	
	//Draw Press Enter to continue
	
	posX=MAP_SIZE_X_PX / 2 - MeasureText(pressEnter, 50) / 2-10;
	posY=MAP_SIZE_Y_PX / 1.25-10;
	width=MeasureText(pressEnter, 50)+20;
	height=50+20;
		
	DrawRectangle(posX,posY,width,height,BLACK);
	DrawText(pressEnter, MAP_SIZE_X_PX / 2 - MeasureText(pressEnter, 50) / 2, MAP_SIZE_Y_PX / 1.25, 50, RED);
	EndDrawing();
	
}

void drawGameOver(char str_time[],struct Isaac isaac,struct Stopwatch stopwatch, int map_counter,  struct InformationBarStrings *informationBarStrings, int EnemiesAlive,struct MapElement mapElements[N_MAP_ELEMENTS])
{	
	char name[30]={"GAME OVER"};	
	char pressEnter[50]={"Press enter to continue..."};
	int score;
	int posX, posY, width,  height;
	
	//draw information bar strings
	BeginDrawing();
	ClearBackground(RAYWHITE);
	//draw map in background
	drawMap(mapElements);
	createInformationBarStrings(stopwatch,isaac, map_counter,informationBarStrings,EnemiesAlive);
	informationBar(isaac,*informationBarStrings);
	
	
	//Draw Score
	
	posX=MAP_SIZE_X_PX / 2 - MeasureText(name, 50) / 2-10;
	posY=MAP_SIZE_Y_PX / 2-10;
	width=MeasureText(name, 50)+20;
	height=50+20;
	
	DrawRectangle(posX,posY,width,height,BLACK); // draw background
	DrawText(name, MAP_SIZE_X_PX / 2 - MeasureText(name, 50) / 2, MAP_SIZE_Y_PX / 2, 50, RED);
	
	//Draw Press Enter to continue
	
	posX=MAP_SIZE_X_PX / 2 - MeasureText(pressEnter, 50) / 2-10;
	posY=MAP_SIZE_Y_PX / 1.25-10;
	width=MeasureText(pressEnter, 50)+20;
	height=50+20;
		
	DrawRectangle(posX,posY,width,height,BLACK);
	DrawText(pressEnter, MAP_SIZE_X_PX / 2 - MeasureText(pressEnter, 50) / 2, MAP_SIZE_Y_PX / 1.25, 50, RED);
	EndDrawing();
	
}
void drawYouDied(char str_time[],struct Isaac isaac,struct Stopwatch stopwatch, int map_counter,  struct InformationBarStrings *informationBarStrings, int EnemiesAlive,struct MapElement mapElements[N_MAP_ELEMENTS])
{	
	char name[50];	
	char pressEnter[50]={"Press enter to continue..."};
	int score;
	int posX, posY, width,  height;
	
	if(isaac.nLifes>1){
		sprintf(name,"You died! Only %d lifes remaining.",isaac.nLifes);
	} else{
		sprintf(name,"You died! Only %d life remaining",isaac.nLifes);
	}

	//draw information bar strings
	BeginDrawing();
	ClearBackground(RAYWHITE);
	//draw map in background
	drawMap(mapElements);
	createInformationBarStrings(stopwatch,isaac, map_counter,informationBarStrings,EnemiesAlive);
	informationBar(isaac,*informationBarStrings);
	
	//Draw Score
	
	posX=MAP_SIZE_X_PX / 2 - MeasureText(name, 50) / 2-10;
	posY=MAP_SIZE_Y_PX / 2-10;
	width=MeasureText(name, 50)+20;
	height=50+20;
	
	DrawRectangle(posX,posY,width,height,BLACK); // draw background
	DrawText(name, MAP_SIZE_X_PX / 2 - MeasureText(name, 50) / 2, MAP_SIZE_Y_PX / 2, 50, RED);
	
	//Draw Press Enter to continue
	
	posX=MAP_SIZE_X_PX / 2 - MeasureText(pressEnter, 50) / 2-10;
	posY=MAP_SIZE_Y_PX / 1.25-10;
	width=MeasureText(pressEnter, 50)+20;
	height=50+20;
		
	DrawRectangle(posX,posY,width,height,BLACK);
	DrawText(pressEnter, MAP_SIZE_X_PX / 2 - MeasureText(pressEnter, 50) / 2, MAP_SIZE_Y_PX / 1.25, 50, RED);
	EndDrawing();
	
}
void missionComplete(char str_time[],struct Isaac isaac,struct Stopwatch stopwatch, int map_counter,  struct InformationBarStrings *informationBarStrings, int EnemiesAlive,struct MapElement mapElements[N_MAP_ELEMENTS])
{	
	char name[50];	
	char pressEnter[50]={"Press enter to continue..."};
	int score;
	int posX, posY, width,  height;

	sprintf(name,"Mission Complete! Now stage %d is coming...",map_counter+2);


	//draw information bar strings
	BeginDrawing();
	ClearBackground(RAYWHITE);
	//draw map in background
	drawMap(mapElements);
	createInformationBarStrings(stopwatch,isaac, map_counter,informationBarStrings,EnemiesAlive);
	informationBar(isaac,*informationBarStrings);
	
	
	//Draw Score
	
	posX=MAP_SIZE_X_PX / 2 - MeasureText(name, 50) / 2-10;
	posY=MAP_SIZE_Y_PX / 2-10;
	width=MeasureText(name, 50)+20;
	height=50+20;
	
	DrawRectangle(posX,posY,width,height,BLACK); // draw background
	DrawText(name, MAP_SIZE_X_PX / 2 - MeasureText(name, 50) / 2, MAP_SIZE_Y_PX / 2, 50, RED);
	
	//Draw Press Enter to continue
	
	posX=MAP_SIZE_X_PX / 2 - MeasureText(pressEnter, 50) / 2-10;
	posY=MAP_SIZE_Y_PX / 1.25-10;
	width=MeasureText(pressEnter, 50)+20;
	height=50+20;
		
	DrawRectangle(posX,posY,width,height,BLACK);
	DrawText(pressEnter, MAP_SIZE_X_PX / 2 - MeasureText(pressEnter, 50) / 2, MAP_SIZE_Y_PX / 1.25, 50, RED);
	EndDrawing();
	
}
#endif

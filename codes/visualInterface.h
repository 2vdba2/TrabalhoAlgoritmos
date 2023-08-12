#ifndef VISUALINTERFACE_H
#define VISUALINTERFACE_H

#include "constants.h"
#include "structs.h"
#include <string.h>
#include <raylib.h>
#include "initializeVariables.h"


#define MAX_CACHED_TEXTURES 2

// struct to cached textures
typedef struct {
    const char* path;
    Texture2D texture;
} CachedTexture;

CachedTexture textureCache[MAX_CACHED_TEXTURES] = { 0 }; // Initialize the cache
//textureCache[0] == Isaac Texture
//textureCache[1] == Wall Texture

void DrawIsaac(int xpx, int ypx){
	//remove logs
    SetTraceLogLevel(LOG_ERROR);

    char* currentDir = GetWorkingDirectory();

    const char* spritePath = TextFormat("%s/Sprites/Character_Isaac_appearance.png", currentDir);

    // Check if the texture is already in the cache

    if (textureCache[0].path && strcmp(textureCache[0].path, spritePath) == 0) {
        DrawTexture(textureCache[0].texture, xpx, ypx, WHITE);
        return;
    }

    // If not in the cache, load and cache the texture
    Image spriteImage = LoadImage(spritePath);
    ImageResize(&spriteImage, 25, 25);
    Texture2D spriteTexture = LoadTextureFromImage(spriteImage);

    // Store the texture in the cache
    textureCache[0].path = spritePath;
    textureCache[0].texture = spriteTexture;

    // Draw the texture
    DrawTexture(spriteTexture, xpx, ypx, WHITE);

}


void DrawWall(int xpx, int ypx) {
	//remove logs
    SetTraceLogLevel(LOG_ERROR);

    char* currentDir = GetWorkingDirectory();

    const char* WallSpritePath = TextFormat("%s/Sprites/Wall.png", currentDir);

    // Check if the texture is already in the cache

    if (textureCache[1].path && strcmp(textureCache[1].path, WallSpritePath) == 0) {
        DrawTexture(textureCache[1].texture, xpx, ypx, WHITE);
        return;
    }

    // If not in the cache, load and cache the texture
    Image WallImage = LoadImage(WallSpritePath);
    ImageResize(&WallImage, 20, 20);
    Texture2D WallTexture = LoadTextureFromImage(WallImage);

    // Store the texture in the cache
    textureCache[1].path = WallSpritePath;
    textureCache[1].texture = WallTexture;

    // Draw the texture
    DrawTexture(WallTexture, xpx, ypx, WHITE);
}

void drawMap(struct MapElement mapElements[N_MAP_ELEMENTS])
{
	int xpx,ypx;
	//DrawRectangle(0,0,MAP_SIZE_X_PX,MAP_SIZE_Y_PX,BEIGE);
	//Draw matrixMap
	for(int k=0;k<N_MAP_ELEMENTS;k++)
			{
	for(int i=0; i<MAP_SIZE_Y; i++)
	{
		for(int j=0; j<MAP_SIZE_X; j++)
		{
			xpx=j*SQUARESIZE;
			ypx=i*SQUARESIZE;
			

				if(map[i][j]==mapElements[k].id)
				{
					DrawTexture(mapElements[0].sprite ,xpx, ypx, WHITE);
					DrawTexture(mapElements[k].sprite ,xpx, ypx, WHITE);
				}
	}
			/*
			
			//walls
			if(map[i][j]=='#')
			{
				DrawWall(xpx,ypx);
			}
			//portal
			else if(map[i][j]=='P')
			{
				DrawRectangle(xpx,ypx,SQUARESIZE,SQUARESIZE,YELLOW);
			}
			//bullet
			else if(map[i][j]=='o')
			{
				DrawRectangle(xpx + SQUARESIZE/4,ypx + SQUARESIZE/4,BULLETSIZE,BULLETSIZE,BLACK);
			}
			//bullet
			else if(map[i][j]==mapElements[1].id)
			{
				DrawTexture(mapElements[1].sprite ,xpx, ypx, WHITE);
				//DrawIsaac(xpx, ypx);
			}
			//inactive Bomb
			else if(map[i][j]=='B')
			{
				DrawRectangle(xpx,ypx,SQUARESIZE,SQUARESIZE,BROWN);
			}
			//active bomb
			else if(map[i][j]=='b')
			{
				DrawRectangle(xpx,ypx,SQUARESIZE,SQUARESIZE,BLACK);
			}
			//Fire
			else if(map[i][j]=='X')
			{
				DrawRectangle(xpx,ypx,SQUARESIZE,SQUARESIZE,ORANGE);
			}
			//Enemy
			else if(map[i][j]=='I')
			{
				DrawRectangle(xpx,ypx,SQUARESIZE,SQUARESIZE,PURPLE);
			}
			*/
			
		}
	}
}
void informationBar(struct Isaac isaac,struct InformationBarStrings informationBarStrings)
{
	//This function draws the informationBar at the botton of the window
	int xPxCol1  = INFORMATION_BAR_X_PX/30;
	int xPxCol2  = xPxCol1+INFORMATION_BAR_X_PX/2.6;
	int xPxCol3  = xPxCol1+INFORMATION_BAR_X_PX/1.25;
	int yPxLine1 = MAP_SIZE_Y_PX+INFORMATION_BAR_Y_PX/6;
	int yPxLine2 = yPxLine1 + INFORMATION_BAR_Y_PX/4;
	int yPxLine3 = yPxLine1 + INFORMATION_BAR_Y_PX/2;

	DrawRectangle(0,MAP_SIZE_Y_PX,INFORMATION_BAR_X_PX,INFORMATION_BAR_Y_PX,SKYBLUE); // draw background

	//draw information bar strings
	DrawText(informationBarStrings.timeText   , xPxCol1,yPxLine1,30, BLACK);
	DrawText(informationBarStrings.lifeText   , xPxCol1,yPxLine3,30, BLACK);
	DrawText(informationBarStrings.stageText  , xPxCol3,yPxLine1,30, BLACK);
	DrawText(informationBarStrings.enemiesText, xPxCol3,yPxLine3,30, BLACK);
	DrawText(informationBarStrings.bombsText  , xPxCol2,yPxLine2,30, BLACK);
	
	if(godMode==1)
	{
		DrawText("GOD MODE ON", xPxCol2,yPxLine3,30, RED);
	}
}

void createInformationBarStrings(struct Stopwatch stopwatch, struct Isaac isaac, int map_counter, struct InformationBarStrings *informationBarStrings,int EnemiesAlive)
{
	//This function creates the information bar strings
	sprintf(informationBarStrings->lifeText   , "Lifes: %d"     , isaac.nLifes);
	sprintf(informationBarStrings->timeText   , "Time alive: %s", stopwatch.str_time);
	sprintf(informationBarStrings->stageText  , "Stage: %d"     , map_counter+1);
	sprintf(informationBarStrings->enemiesText, "Enemies: %d"   , EnemiesAlive);
	sprintf(informationBarStrings->bombsText, "Bombs: %d"   , isaac.nBombs);
}

void drawWindow(char str_time[],struct Isaac isaac,struct Stopwatch stopwatch, int map_counter,  struct InformationBarStrings *informationBarStrings, int EnemiesAlive,struct MapElement mapElements[N_MAP_ELEMENTS])
{
	//This function draws the entire game window
	BeginDrawing();//Inicia o ambiente de desenho na tela
	//ClearBackground(RAYWHITE);//Limpa a tela e define cor de fundo
	drawMap(mapElements);
	createInformationBarStrings(stopwatch,isaac, map_counter,informationBarStrings,EnemiesAlive);
	informationBar(isaac,*informationBarStrings);
	EndDrawing();//Finaliza o ambiente de desenho na tela
}

typedef enum {
    NOVO_JOGO,
    CARREGAR_JOGO,
    CONFIGURACOES,
    SAIR
 } MenuItem;



MenuItem currentMenuItem = NOVO_JOGO;

void DrawMenu() {



    ClearBackground(RAYWHITE);

    DrawText("The Binding of Isaac", MAP_SIZE_X_PX / 2 - MeasureText("The Binding of Isaac", 40) / 2, 80, 40, DARKGRAY);

    switch (currentMenuItem) {
        case NOVO_JOGO:
            DrawText("> Novo Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Novo Jogo", 30) / 2, 200, 30, GRAY);
            DrawText("Carregar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Carregar Jogo", 30) / 2, 250, 30, GRAY);
            DrawText("Configurações", MAP_SIZE_X_PX / 2 - MeasureText("Configurações", 30) / 2, 300, 30, GRAY);
            DrawText("Sair", MAP_SIZE_X_PX / 2 - MeasureText("Sair", 30) / 2, 350, 30, GRAY);
            break;
        case CARREGAR_JOGO:
            DrawText("Novo Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Novo Jogo", 30) / 2, 200, 30, GRAY);
            DrawText("> Carregar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Carregar Jogo", 30) / 2, 250, 30, GRAY);
            DrawText("Configurações", MAP_SIZE_X_PX / 2 - MeasureText("Configurações", 30) / 2, 300, 30, GRAY);
            DrawText("Sair", MAP_SIZE_X_PX / 2 - MeasureText("Sair", 30) / 2, 350, 30, GRAY);
            break;
        case CONFIGURACOES:
            DrawText("Novo Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Novo Jogo", 30) / 2, 200, 30, GRAY);
            DrawText("Carregar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Carregar Jogo", 30) / 2, 250, 30, GRAY);
            DrawText("> Configurações", MAP_SIZE_X_PX / 2 - MeasureText("Configurações", 30) / 2, 300, 30, GRAY);
            DrawText("Sair", MAP_SIZE_X_PX / 2 - MeasureText("Sair", 30) / 2, 350, 30, GRAY);
            break;
        case SAIR:
            DrawText("Novo Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Novo Jogo", 30) / 2, 200, 30, GRAY);
            DrawText("Carregar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Carregar Jogo", 30) / 2, 250, 30, GRAY);
            DrawText("Configurações", MAP_SIZE_X_PX / 2 - MeasureText("Configurações", 30) / 2, 300, 30, GRAY);
            DrawText("> Sair", MAP_SIZE_X_PX / 2 - MeasureText("Sair", 30) / 2, 350, 30, GRAY);
            break;
        default:
            break;
    }

    DrawText("Use as setas para navegar e pressione enter para selecionar", 50, MAP_SIZE_Y_PX - 50, 20, DARKGRAY);
}


void Menu(){

	 if (IsKeyPressed(KEY_DOWN)||IsKeyPressed(KEY_S)) {
            currentMenuItem = (currentMenuItem + 1) % 4;
        } else if (IsKeyPressed(KEY_UP)||IsKeyPressed(KEY_W)) {
            currentMenuItem = (currentMenuItem - 1 + 4) % 4;
        }

        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            switch (currentMenuItem) {
                case NOVO_JOGO:
                    NewGame();
                    break;
                case CARREGAR_JOGO:
                    LoadGame();
                    break;
                case CONFIGURACOES:
                    Config();
                    break;
                case SAIR:
                    // Close the window
                    CloseWindow();
                    break;
            }
        }

        BeginDrawing();
        DrawMenu();
        EndDrawing();
}


typedef enum {
    INGAME_NOVO_JOGO,
    INGAME_SALVAR_JOGO,
    INGAME_CARREGAR_JOGO,
    INGAME_CONFIGURACOES,
    INGAME_VOLTAR,
    INGAME_SAIR,
} InGameMenuItem;

InGameMenuItem currentInGameMenuItem = NOVO_JOGO;

void DrawMenuInGame() {



    ClearBackground(RAYWHITE);

    DrawText("The Binding of Isaac", MAP_SIZE_X_PX / 2 - MeasureText("The Binding of Isaac", 40) / 2, 80, 40, DARKGRAY);

    switch (currentInGameMenuItem) {
        case INGAME_NOVO_JOGO:
            DrawText("> Novo Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Novo Jogo", 30) / 2, 200, 30, GRAY);
            DrawText("Salvar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Salvar Jogo", 30) / 2, 250, 30, GRAY);
            DrawText("Carregar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Carregar Jogo", 30) / 2, 300, 30, GRAY);
            DrawText("Configurações", MAP_SIZE_X_PX / 2 - MeasureText("Configurações", 30) / 2, 350, 30, GRAY);
            DrawText("Voltar", MAP_SIZE_X_PX / 2 - MeasureText("Voltar", 30) / 2, 400, 30, GRAY);
            DrawText("Sair", MAP_SIZE_X_PX / 2 - MeasureText("Sair", 30) / 2, 450, 30, GRAY);
            break;
        case INGAME_SALVAR_JOGO:
            DrawText("Novo Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Novo Jogo", 30) / 2, 200, 30, GRAY);
            DrawText("> Salvar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Salvar Jogo", 30) / 2, 250, 30, GRAY);
            DrawText("Carregar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Carregar Jogo", 30) / 2, 300, 30, GRAY);
            DrawText("Configurações", MAP_SIZE_X_PX / 2 - MeasureText("Configurações", 30) / 2, 350, 30, GRAY);
            DrawText("Voltar", MAP_SIZE_X_PX / 2 - MeasureText("Voltar", 30) / 2, 400, 30, GRAY);
            DrawText("Sair", MAP_SIZE_X_PX / 2 - MeasureText("Sair", 30) / 2, 450, 30, GRAY);
            break;
        case INGAME_CARREGAR_JOGO:
            DrawText("Novo Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Novo Jogo", 30) / 2, 200, 30, GRAY);
            DrawText("Salvar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Salvar Jogo", 30) / 2, 250, 30, GRAY);
            DrawText("> Carregar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Carregar Jogo", 30) / 2, 300, 30, GRAY);
            DrawText("Configurações", MAP_SIZE_X_PX / 2 - MeasureText("Configurações", 30) / 2, 350, 30, GRAY);
            DrawText("Voltar", MAP_SIZE_X_PX / 2 - MeasureText("Voltar", 30) / 2, 400, 30, GRAY);
            DrawText("Sair", MAP_SIZE_X_PX / 2 - MeasureText("Sair", 30) / 2, 450, 30, GRAY);
            break;
        case INGAME_CONFIGURACOES:
            DrawText("Novo Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Novo Jogo", 30) / 2, 200, 30, GRAY);
            DrawText("Salvar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Salvar Jogo", 30) / 2, 250, 30, GRAY);
            DrawText("Carregar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Carregar Jogo", 30) / 2, 300, 30, GRAY);
            DrawText("> Configurações", MAP_SIZE_X_PX / 2 - MeasureText("Configurações", 30) / 2, 350, 30, GRAY);
            DrawText("Voltar", MAP_SIZE_X_PX / 2 - MeasureText("Voltar", 30) / 2, 400, 30, GRAY);
            DrawText("Sair", MAP_SIZE_X_PX / 2 - MeasureText("Sair", 30) / 2, 450, 30, GRAY);
            break;
        case INGAME_VOLTAR:
            DrawText("Novo Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Novo Jogo", 30) / 2, 200, 30, GRAY);
            DrawText("Salvar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Salvar Jogo", 30) / 2, 250, 30, GRAY);
            DrawText("Carregar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Carregar Jogo", 30) / 2, 300, 30, GRAY);
            DrawText("Configurações", MAP_SIZE_X_PX / 2 - MeasureText("Configurações", 30) / 2, 350, 30, GRAY);
            DrawText("> Voltar", MAP_SIZE_X_PX / 2 - MeasureText("Voltar", 30) / 2, 400, 30, GRAY);
            DrawText("Sair", MAP_SIZE_X_PX / 2 - MeasureText("Sair", 30) / 2, 450, 30, GRAY);
            break;
        case INGAME_SAIR:
            DrawText("Novo Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Novo Jogo", 30) / 2, 200, 30, GRAY);
            DrawText("Salvar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Salvar Jogo", 30) / 2, 250, 30, GRAY);
            DrawText("Carregar Jogo", MAP_SIZE_X_PX / 2 - MeasureText("Carregar Jogo", 30) / 2, 300, 30, GRAY);
            DrawText("Configurações", MAP_SIZE_X_PX / 2 - MeasureText("Configurações", 30) / 2, 350, 30, GRAY);
            DrawText("Voltar", MAP_SIZE_X_PX / 2 - MeasureText("Voltar", 30) / 2, 400, 30, GRAY);
            DrawText("> Sair", MAP_SIZE_X_PX / 2 - MeasureText("Sair", 30) / 2, 450, 30, GRAY);
            break;
        default:
            break;
    }

    DrawText("Use as setas para navegar e pressione enter para selecionar", 50, MAP_SIZE_Y_PX - 50, 20, DARKGRAY);
}


void InGameMenu(){

	 if (IsKeyPressed(KEY_DOWN)||IsKeyPressed(KEY_S)) {
            currentInGameMenuItem = (currentInGameMenuItem + 1) % 6;
        } else if (IsKeyPressed(KEY_UP)||IsKeyPressed(KEY_W)) {
            currentInGameMenuItem = (currentInGameMenuItem - 1 + 6) % 6;
        }

        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            switch (currentInGameMenuItem) {
                case INGAME_NOVO_JOGO:
                    NewGame();
                    break;
                case INGAME_SALVAR_JOGO:
                    break;
                case INGAME_CARREGAR_JOGO:
                    LoadGame();
                    break;
                case INGAME_CONFIGURACOES:
                    Config();
                    break;
                case INGAME_SAIR:
                    // Close the window
                    CloseWindow();
                    break;
                case INGAME_VOLTAR:
                    gameState = GAME;
                    break;
            }
        }

        BeginDrawing();
        DrawMenuInGame();
        EndDrawing();
}

#endif

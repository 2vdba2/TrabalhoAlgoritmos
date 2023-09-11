#include "codes/gameLoop.c"
#include "codes/globals.h"
#include "codes/manageFiles.h"
#include "codes/structs.h"
#include "codes/gameFunctions.c"


int main()
{
	printf("n=%d",numberOfMaps());

	//--------------------------------------------------------------------------------------
	//Inicializa¸c~oesdd
	InitWindow(MAP_SIZE_X_PX, MAP_SIZE_Y_PX+INFORMATION_BAR_Y_PX, "The Binding of Isaac remastered");//Inicializa janela, com certo tamanho e t´ıtulo
	SetTargetFPS(10);// Ajusta a execu¸c~ao do jogo para 60 frames por segundo
	//--------------------------------------------------------------------------------------
	while (!WindowShouldClose()&&closeGame==0) {
       Menu();
    }

	CloseWindow();// Fecha a janela e o contexto OpenGL

	return 0;
}



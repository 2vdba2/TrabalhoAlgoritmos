#include "codes/gameLoop.c"
#include "codes/manageFiles.h"
#include "codes/structs.h"
#include "codes/gameFunctions.c"


int main()
{
	printf("n=%d",numberOfMaps());

	//struct Isaac isaac;
	//struct Enemy enemy1;
	//stopwatchh->elapsed_time= time(NULL);
	//--------------------------------------------------------------------------------------
	//Inicializa¸c~oes
	InitWindow(MAP_SIZE_X_PX, MAP_SIZE_Y_PX+INFORMATION_BAR_Y_PX, "The Binding of Isaac remastered");//Inicializa janela, com certo tamanho e t´ıtulo
	SetTargetFPS(60);// Ajusta a execu¸c~ao do jogo para 60 frames por segundo
	//--------------------------------------------------------------------------------------
	while (!WindowShouldClose()) {
       Menu();
    }

	CloseWindow();// Fecha a janela e o contexto OpenGL
	
	
	return 0;
}

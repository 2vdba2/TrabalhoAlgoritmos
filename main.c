#include "codes/gameLoop.c"
#include "codes/manageFiles.h"

int main()
{
	printf("n=%d",numberOfMaps());

	
	int nMaps=numberOfMaps();
	//--------------------------------------------------------------------------------------
	//Inicializa¸c~oes
	InitWindow(MAP_SIZE_X_PX, MAP_SIZE_Y_PX+INFORMATION_BAR_Y_PX, "The Binding of Isaac remastered");//Inicializa janela, com certo tamanho e t´ıtulo
	SetTargetFPS(60);// Ajusta a execu¸c~ao do jogo para 60 frames por segundo
	//--------------------------------------------------------------------------------------
	for(int i=0;i< nMaps;i++)
	{
	 	printf("\nmaps/map%02d.txt",i);
		gameLoop(i);
	}
	CloseWindow();// Fecha a janela e o contexto OpenGL
	
	return 0;
}

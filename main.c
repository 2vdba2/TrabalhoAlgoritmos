#include "codes/gameLoop.c"
#include "codes/manageFiles.h"
#include "codes/structs.h"
int main()
{
	printf("n=%d",numberOfMaps());

	//struct Isaac isaac;
	//struct Enemy enemy1;
	int nMaps=numberOfMaps();
	
	struct Stopwatchh *stopwatchh = malloc(sizeof *stopwatchh);
	struct InformationBarStrings *informationBarStrings = malloc(sizeof *informationBarStrings);
	
	stopwatchh->start_time= time(NULL);
	stopwatchh->elapsed_time= time(NULL);
	//stopwatchh->elapsed_time= time(NULL);
	//--------------------------------------------------------------------------------------
	//Inicializa¸c~oes
	InitWindow(MAP_SIZE_X_PX, MAP_SIZE_Y_PX+INFORMATION_BAR_Y_PX, "The Binding of Isaac remastered");//Inicializa janela, com certo tamanho e t´ıtulo
	SetTargetFPS(60);// Ajusta a execu¸c~ao do jogo para 60 frames por segundo
	//--------------------------------------------------------------------------------------
	for(int i=0;i< nMaps;i++)
	{
	 	printf("\nmaps/map%02d.txt",i);
		gameLoop(i,stopwatchh,informationBarStrings);
	}
	CloseWindow();// Fecha a janela e o contexto OpenGL
	
	free(stopwatchh);
	free(informationBarStrings);
	return 0;
}

#include "manageFiles.h"

void NewGame() {
	int nMaps=numberOfMaps();

	struct Stopwatch *stopwatch = malloc(sizeof *stopwatch);
	struct InformationBarStrings *informationBarStrings = malloc(sizeof *informationBarStrings);

	stopwatch->start_time= time(NULL);
	stopwatch->elapsed_time= time(NULL);

	bool ShouldGameClose = false;

	for(int i=0; i< nMaps; i++)
	{
		if(!ShouldGameClose){
			printf("\nmaps/map%02d.txt",i);
			ShouldGameClose = gameLoop(i,stopwatch,informationBarStrings);
		}
	}
	CloseWindow();
	free(stopwatch);
	free(informationBarStrings);
};

void LoadGame() {
	//orderToLoadGame=1;
	orderToSaveGame=1; // como n tem funcao visual de salvar jogo ta aqui a gambiarra
}

void Config() {

}

void SaveGame(){
	orderToSaveGame=1;

}

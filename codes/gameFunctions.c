#include "manageFiles.h"
#include "globals.h"

void NewGame() {
	int nMaps=numberOfMaps();
	int map_counter;
	struct Stopwatch *stopwatch = malloc(sizeof *stopwatch);
	struct InformationBarStrings *informationBarStrings = malloc(sizeof *informationBarStrings);

	stopwatch->start_time= time(NULL);
	stopwatch->elapsed_time= time(NULL);

	bool ShouldGameClose = false;

	for(map_counter=0; map_counter< nMaps; map_counter++)
	{
		if(!ShouldGameClose){
			printf("\nmaps/map%02d.txt",map_counter);
			ShouldGameClose = gameLoop(&map_counter,stopwatch,informationBarStrings,nMaps);
		}
	}
	if(closeGame==1)
	{
		CloseWindow();
	}
	free(stopwatch);
	free(informationBarStrings);
};

void QuickLoadGame() {
	orderToLoadGame=1;
}


void QuickSaveGame(){
	orderToSaveGame=1;
}

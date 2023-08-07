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

}

void Config() {

}

void SaveGame(){

}

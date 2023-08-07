void NewGame() {
	printf("new game");
	int nMaps=numberOfMaps();

	struct Stopwatch *stopwatch = malloc(sizeof *stopwatch);
	struct InformationBarStrings *informationBarStrings = malloc(sizeof *informationBarStrings);

	stopwatch->start_time= time(NULL);
	stopwatch->elapsed_time= time(NULL);

	for(int i=0; i< nMaps; i++)
	{
		printf("\nmaps/map%02d.txt",i);
		gameLoop(i,stopwatch,informationBarStrings);
	}
	free(stopwatch);
	free(informationBarStrings);
};

void LoadGame() {

}

void Config() {

}




void NewGame(){
    printf("new game");
    int nMaps=numberOfMaps();
	
	struct Stopwatchh *stopwatchh = malloc(sizeof *stopwatchh);
	struct InformationBarStrings *informationBarStrings = malloc(sizeof *informationBarStrings);
	
	stopwatchh->start_time= time(NULL);
	stopwatchh->elapsed_time= time(NULL);

     for(int i=0;i< nMaps;i++)
	{
		printf("\nmaps/map%02d.txt",i);
		gameLoop(i,stopwatchh,informationBarStrings);
	}
    free(stopwatchh);
	free(informationBarStrings);
};


void LoadGame(){	

}

void Config(){

}
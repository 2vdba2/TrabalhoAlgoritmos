#ifndef MANAGEFILES_H
#define MANAGEFILES_H

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "constants.h"
#include "structs.h"
#include <time.h>

int numberOfMaps()
{
    int file_count = 0;
    DIR *dirp;
    struct dirent *entry;
    struct stat file_info;

    dirp = opendir("./maps/");
    if (dirp == NULL) {
        return -1; //ERROR
    }

    while ((entry = readdir(dirp)) != NULL) {
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s/%s", "./maps", entry->d_name); // Create the full file path

        if (stat(filepath, &file_info) == -1) {
            continue;
        }

        if (S_ISREG(file_info.st_mode)) { // Check if is a regular file
            file_count++; //add to counter
        }
    }

    closedir(dirp);
    return file_count;
}

/*
int saveGame()
{
    int file_count = 0;
    DIR *dirp;
    struct dirent *entry;
    struct stat file_info;

    dirp = opendir("./maps/");
    if (dirp == NULL) {
        return -1; //ERROR
    }

    while ((entry = readdir(dirp)) != NULL) {
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s/%s", "./maps", entry->d_name); // Create the full file path

        if (stat(filepath, &file_info) == -1) {
            continue;
        }

        if (S_ISREG(file_info.st_mode)) { // Check if is a regular file
            file_count++; //add to counter
        }
    }

    closedir(dirp);
    return file_count;
}
*/

void CreateRandomSaveFileName(char FileName[20]){
	srand(time(NULL));
	snprintf(FileName, 20, "%d", rand());
}


int saveGame(char map[MAP_SIZE_Y][MAP_SIZE_X],struct Enemy enemies[MAX_ENEMIES],struct Isaac isaac,struct Stopwatch *stopwatch, int EnemiesAlive,struct Bullet bullets[MAX_BULLLETS],int map_counter, int nEnemies, char SaveName[20])
{

	//The Save file have a random name, but in the end of the file you have the name you put when you save game
	int saved=1;
	char SaveFileName[20];
	char path[30]={"./savedGame/"};
	if (strcmp(SaveName, "QuickSave.bin") == 0) {
        strcpy(SaveFileName, "QuickSave.bin");
    } else {
        CreateRandomSaveFileName(SaveFileName);
    }
	strcat(path, SaveFileName);
	puts(path);

	FILE *arq;
	arq = fopen(path,"wb"); // w for write, b for binary

	//SAVE MAP
	for(int i=0;i<MAP_SIZE_Y;i++)
	{
		for(int j=0;j<MAP_SIZE_X;j++)
		{
			if (fwrite(&map[i][j], sizeof(char), 1, arq) != 1)
			{
				printf("Map writting error");
				saved=0;
				return saved;
			}
		}
	}
	// SAVE ISAAC
	if (fwrite(&isaac, sizeof(struct Isaac), 1, arq) != 1)
	{
		printf("isaac writing error");
		saved=0;
		return saved;
	}
	// SAVE Enemies
	//enemies
	for(int i=0;i<MAX_ENEMIES;i++)
	{
		if (fwrite(&enemies[i], sizeof(struct Enemy), 1, arq) != 1)
		{
			printf("enemy writing error");
			saved=0;
			return saved;
		}
	}
	//stopwatch
	if (fwrite(stopwatch, sizeof(struct Stopwatch), 1, arq) != 1)
	{
		printf("stopwatch writing error");
		saved=0;
		return saved;
	}
	//EnemiesAlive
	if (fwrite(&EnemiesAlive, sizeof(int), 1, arq) != 1)
	{
		printf("Enemies Alive writting error");
		saved=0;
		return saved;
	}
	//Bullets
	for(int i=0;i<MAX_BULLLETS;i++)
	{
		if (fwrite(&bullets[i], sizeof(struct Bullet), 1, arq) != 1)
		{
			printf("bullet writing error");
			saved=0;
			return saved;
		}
	}
	// map counter
	if (fwrite(&map_counter, sizeof(int), 1, arq) != 1)
	{
		printf("map_counter writing error");
		saved=0;
		return saved;
	}
	//nEnemies
	if (fwrite(&nEnemies, sizeof(int), 1, arq) != 1)
	{
		printf("nEnemies writing error");
		saved=0;
		return saved;
	}
	if(fwrite(SaveName, sizeof(SaveName), 1, arq) != 1)
	{
		printf("Error reading nome");
		return 0;
	}
	fclose(arq);
	return saved;
}

int loadGame(char map[MAP_SIZE_Y][MAP_SIZE_X],struct Enemy enemies[MAX_ENEMIES],struct Isaac *isaac,struct Stopwatch *stopwatch,int *EnemiesAlive,struct Bullet bullets[MAX_BULLLETS], int *map_counter,int *nEnemies, char SaveFileName[20])
{
	int saved=1;
	char path[30]={"./savedGame/"};
	strcat(path, SaveFileName);
	puts(path);
	int read=0;
	FILE *arq;
	arq = fopen(path,"rb"); // w for write, b for binary
	if(arq==NULL)
	{
		saved=0;
		return saved;

	}

	//MAP
	for(int i=0;i<MAP_SIZE_Y;i++)
	{
		for(int j=0;j<MAP_SIZE_X;j++)
		{
			if(fread(&map[i][j], sizeof(char), 1, arq) != 1)
			{
				printf("Erro na leitura do mapa");
				read=0;
				return read;
			}
		}
	}
	//isaac
	if(fread(isaac, sizeof(struct Isaac), 1, arq) != 1)
	{
		printf("Error reading Isaac");
		return 0;
	}
	//enemies
	for(int i=0;i<MAX_ENEMIES;i++)
	{
		if(fread(&enemies[i], sizeof(struct Enemy), 1, arq) != 1)
		{
			printf("Error reading Enemy[%d]",i);
			return 0;
		}
	}
	//Stopwatch
	if(fread(stopwatch, sizeof(struct Stopwatch), 1, arq) != 1)
	{
		printf("Error reading stopwatch");
		return 0;
	}
	//Enemies Alive
	if(fread(EnemiesAlive, sizeof(int), 1, arq) != 1)
	{
		printf("Error reading EnemiesAlive");
		return 0;
	}
	//bullets
	for(int i=0;i<MAX_BULLLETS;i++)
	{
		if(fread(&bullets[i], sizeof(struct Bullet), 1, arq) != 1)
		{
			printf("Error reading bullet[%d]",i);
			return 0;
		}
	}
	//map_counter
	if(fread(map_counter, sizeof(int), 1, arq) != 1)
	{
		printf("Error reading map_counter");
		return 0;
	}
	//nEnemies
	if(fread(nEnemies, sizeof(int), 1, arq) != 1)
	{
		printf("Error reading nEnemies");
		return 0;
	}
	fclose(arq);
	return read;
}





#endif

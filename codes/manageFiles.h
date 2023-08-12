#ifndef MANAGEFILES_H
#define MANAGEFILES_H

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "constants.h"
#include "structs.h"

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
int saveGame(char map[MAP_SIZE_Y][MAP_SIZE_X])
{
	int saved=1;
	char name[30]={"./savedGame/savedGame.bin"};
	FILE *arq;
	arq = fopen(name,"wb"); // w for write, b for binary
	
	//SAVE MAP
	for(int i=0;i<MAP_SIZE_Y;i++)
	{
		for(int j=0;j<MAP_SIZE_X;j++)
		{
			if (fwrite(&map[i][j], sizeof(char), 1, arq) != 1)
			{
				printf("Erro na escrita do mapa");
				saved=0;
				return saved;
			}
		}
	}
	// SAVE ISAAC
	/*
	if (fwrite(&isaac, sizeof(struct Isaac), 1, arq) != 1)
	{
		printf("Erro na escrita");
		salvou=0;
	}
	*/
	fclose(arq);
	return saved;
}

int loadGame(char map[MAP_SIZE_Y][MAP_SIZE_X])
{
	int saved=1;
	char name[30]={"./savedGame/savedGame.bin"};
	int read=0;
	FILE *arq;
	arq = fopen(name,"rb"); // w for write, b for binary
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

	fclose(arq);
	return read;
}





#endif

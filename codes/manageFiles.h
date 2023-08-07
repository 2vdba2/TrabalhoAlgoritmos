#ifndef MANAGEFILES_H
#define MANAGEFILES_H

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

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

#endif

#ifndef MANAGEFILES_H
#define MANAGEFILES_H

#include <dirent.h>
#include <stdio.h>
#include <string.h>

int numberOfMaps()
{
	int file_count = 0;
	DIR * dirp;
	struct dirent * entry;

	dirp = opendir("./maps/"); /* There should be error handling after this */
	while ((entry = readdir(dirp)) != NULL) {
		if (entry->d_type == DT_REG) { /* If the entry is a regular file */
			 file_count++;
		}
	}
	closedir(dirp);
	return file_count;
}

#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

int isDirectoryEmpty(const char *d_name){
	DIR *dp;
	struct dirent *dent;

	dp = opendir(d_name);
	while((dent = readdir(dp))){
		if(strcmp(dent->d_name, ".") !=0 && strcmp(dent->d_name, "..")) {
			closedir(dp);
			return 0;
		}
	}
	closedir(dp);
	return 1;
}
int main() {
	DIR *dp;
	struct dirent *dent;
	struct stat statbuf;

	dp = opendir(".");
	while((dent = readdir(dp))) {
		stat(dent->d_name, &statbuf);

		if(S_ISDIR(statbuf.st_mode)) {
			if(isDirectoryEmpty(dent->d_name)) {
				printf("This directory is empty : %s\n", dent->d_name);
				rmdir(dent->d_name);
			} else {
				printf("This directory is not empty : %s\n", dent->d_name);
			}
		}
	}
	closedir(dp);
}

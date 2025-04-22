#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

int main(){
	DIR *dp;
	struct dirent *dent;
	struct stat statbuf;
	
	dp = opendir(".");
	while((dent = readdir(dp))){
		stat(dent->d_name, &statbuf);
		printf("Name : %s ", dent->d_name);
		printf("Inode : %d\n", (int)statbuf.st_ino);
	}
	return 0;
}

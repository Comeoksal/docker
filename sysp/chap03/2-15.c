#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	DIR *dp;
	struct dirent *dent;

	dp = opendir(argv[2]);
	while((dent = readdir(dp))){
		if(strcmp(dent->d_name, argv[1])==0){
			printf("Exist\n");
			return 0;
		}
	}
	printf("Not Exist\n");
	return 0;
}

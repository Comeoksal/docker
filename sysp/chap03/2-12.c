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
	
	dp = opendir(".");
	while((dent = readdir(dp))){
		if(strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..")==0) {
			continue;
		}
		printf("%s ", dent->d_name);
	}
	printf("\n");
	return 0;
}

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
	int count = 1;
	long loc;
	dp = opendir(".");
	while((dent = readdir(dp))){
		if(count==2){
			loc = telldir(dp);
		}
		printf("%s ", dent->d_name);
		count++;
	}
	printf("\n");

	seekdir(dp, loc);
	dent = readdir(dp);
	printf("%s\n", dent->d_name);
	return 0;
}

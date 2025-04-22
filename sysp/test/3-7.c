#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	struct stat statbuf;
	
	stat(argv[1], &statbuf);
	
	unsigned int mode = statbuf.st_mode;
	
	if(S_ISDIR(mode)){
		printf("DIR\n");
	}
	if(S_ISREG(mode)){
		printf("REG\n");
	}
	if(S_ISCHR(mode)){
		printf("CHR\n");
	}
	if(S_ISBLK(mode)){
		printf("BLK\n");
	}
	return 0;
}

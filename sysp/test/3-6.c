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
	
	printf("size : %ld\n", statbuf.st_size);
	return 0;
}

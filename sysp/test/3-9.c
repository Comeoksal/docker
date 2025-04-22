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
	char buf[9] = "---------";
	stat(argv[1], &statbuf);
	printf("%s ", argv[1]);
	printf("%d ", statbuf.st_uid);
	
	unsigned int mode = statbuf.st_mode;

	if((mode & S_IRUSR) !=0){
		buf[0] = 'r';
	}
	if((mode & S_IWUSR) !=0){
		buf[1] = 'w';
	}
	if((mode & S_IXUSR) !=0){
		buf[2] = 'x';
	}
	if((mode & S_IRGRP) !=0) {
		buf[3] = 'r';
	}
	if((mode & S_IWGRP) !=0) {
		buf[4] = 'w';
	}
	if((mode & S_IXGRP) !=0) {
		buf[5] = 'x';
	}
	printf("%s\n", buf);
	return 0;
}

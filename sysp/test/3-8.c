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

	printf("파일명 : %s\n", argv[1]);
	printf("inode 번호 : %d\n", (int)statbuf.st_ino);
	if(S_ISDIR(statbuf.st_mode)){
		printf("파일 종류 : 디렉터리\n");
	} else if(S_ISREG(statbuf.st_mode)){
		printf("파일 종류 : 일반 파일\n");
	}
	printf("접근 권한 : %o\n", (unsigned int)statbuf.st_mode);
	printf("UID : %d\n", (int)statbuf.st_uid);
	return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

void printfMode(unsigned int mode, char *buf){
	strcpy(buf, "---------");

	 if (mode & S_IRUSR) buf[0] = 'r';
    if (mode & S_IWUSR) buf[1] = 'w';
    if (mode & S_IXUSR) buf[2] = 'x';

    // 그룹 권한
    if (mode & S_IRGRP) buf[3] = 'r';
    if (mode & S_IWGRP) buf[4] = 'w';
    if (mode & S_IXGRP) buf[5] = 'x';

    // 기타 사용자 권한
    if (mode & S_IROTH) buf[6] = 'r';
    if (mode & S_IWOTH) buf[7] = 'w';
    if (mode & S_IXOTH) buf[8] = 'x';

    buf[9] = 0;
}
int main(int argc, char *argv[]){
	struct stat statbuf;
	char buf[10];
	stat(argv[2], &statbuf);
	
	printfMode(statbuf.st_mode, buf);
	printf("Current Mode : %s\n", buf);

	if(argv[1][0]=='g') {
		switch(argv[1][2]){
			case 'r':
				statbuf.st_mode |=S_IRGRP;
				break;
			case 'w':
				statbuf.st_mode |=S_IWGRP;
				break;
			case 'x':
				statbuf.st_mode |=S_IXGRP;
				break;
		}
		chmod(argv[2], statbuf.st_mode);
	} else {
		printf("No\n");
	}
	printfMode(statbuf.st_mode, buf);
	printf("Change Mode : %s\n", buf);
	return 0;
}

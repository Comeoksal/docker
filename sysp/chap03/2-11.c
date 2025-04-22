#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

void copyDIR(const char *argv, const char *d_name){
	chdir(argv);
	mkdir(d_name, 0644);
	chdir("..");
}
void copyREG(const char *argv, const char *d_name){
	int rfd, wfd, nbyte;
           		char buf[BUFSIZ];
                        rfd = open(d_name, O_RDWR);
                        nbyte = read(rfd, buf, sizeof(buf));

                        chdir(argv);
                        wfd = open(d_name, O_CREAT |O_RDWR, 0644);
                        write(wfd, buf, nbyte);

                        chdir("..");

                        close(rfd);
                        close(wfd);
}
int main(int argc, char *argv[]){
	DIR *dp;
	struct dirent *dent;
	struct stat statbuf;

	mkdir(argv[1], 0755);

	dp = opendir(".");
	while((dent = readdir(dp))){
		stat(dent->d_name, &statbuf);
		if(S_ISDIR(statbuf.st_mode)){
			if(strcmp(dent->d_name, argv[1])==0){
				continue;
			}
			copyDIR(argv[1], dent->d_name);
			continue;
		}
		if(S_ISREG(statbuf.st_mode)){
			copyREG(argv[1], dent->d_name);
			continue;
		}
	}
	closedir(dp);
	return 0;
}

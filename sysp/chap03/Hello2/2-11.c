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
	struct stat statbuf;

	mkdir(argv[1], 0755);

	dp = opendir(".");
	while((dent = readdir(dp))){
		stat(dent->d_name, &statbuf);
		if(S_ISDIR(statbuf.st_mode)){
			
			continue;
		}
		if(S_ISREG(statbuf.st_mode)){
			int rfd, wfd, nbyte;
			char buf[BUFSIZ];
			rfd = open(dent->d_name, O_RDWR);
			nbyte = read(rfd, buf, sizeof(buf));
			
			chdir(argv[1]);
			wfd = open(dent->d_name, O_CREAT |O_RDWR, 0644);
			write(wfd, buf, nbyte);
			
			chdir("..");

			close(rfd);
			close(wfd);
			continue;
		}
	}
	closedir(dp);
	return 0;
}

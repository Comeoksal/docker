#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int rfd, wfd, nbyte;
	char buf[BUFSIZ];
	
	rfd = open(argv[1], O_RDONLY);
	wfd = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0644);

	while((nbyte = read(rfd, buf, sizeof(buf))) > 0) {
		write(wfd, buf, nbyte);
	}
	return 0;
}

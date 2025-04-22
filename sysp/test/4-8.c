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

	mkdir(argv[1], 0755);
	rfd = open(argv[2], O_RDONLY);
	nbyte = read(rfd, buf, sizeof(buf));

	chdir(argv[1]);
	wfd = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0644);
	write(wfd, buf, nbyte);

	return 0;
}

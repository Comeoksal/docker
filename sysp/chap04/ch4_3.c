#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int rfd, wfd, nbyte;
	char buf[10];
	
	rfd = open("linux.txt", O_RDONLY);
	if(rfd == -1) {
		perror("open linux");
		exit(1);
	}
	
	wfd = open("linux.bak", O_CREAT|O_WRONLY|O_TRUNC, 0644);
	if(wfd == -1) {
		perror("open linux.bak");
		exit(1);
	}
	
	while((nbyte = read(rfd, buf, 5)) > 0) {
		if(write(wfd, buf, nbyte) != nbyte) perror("WRITE");
	}
	
	close(rfd);
	close(wfd);
}

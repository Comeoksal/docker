#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int fd, nbyte;
	char buf[10];
	
	fd = open("linux.txt", O_RDONLY);
	if(fd == -1) {
		perror("OPEN");
		exit(1);
	}
	
	nbyte = read(fd, buf, 5);
	printf("size of buf : %ld", sizeof(buf));
	if(nbyte == -1) {
		perror("READ");
		exit(1);
	}
	
	buf[nbyte] = 0;
	printf("nbyte = %d, buf = %s\n", nbyte, buf);
	close(fd);
}

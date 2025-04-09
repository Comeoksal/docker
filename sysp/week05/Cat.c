#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	int fd, n;
	char buf[BUFSIZ];
	
	if(argc < 2) {
		perror("usage");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);

	while(read(fd, buf, sizeof(BUFSIZ)) >0) {
		write(1, buf, sizeof(BUFSIZ));
	}
	printf("\n");
	close(fd);
}

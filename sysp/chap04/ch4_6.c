#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int fd, flags;
	
	fd = open("linux.txt", O_RDWR);
	
	flags = fcntl(fd, F_GETFL);
	
	flags |= O_APPEND;
	
	fcntl(fd, F_SETFL, flags);
	
	write(fd, "Hanbit Academy\n", 15);
	
	close(fd);
}

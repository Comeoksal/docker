#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int fd, nbyte;
	off_t start, cur, end;
	char buf[256];
	
	fd = open("linux.txt", O_RDONLY);
	
	start = lseek(fd, 0, SEEK_CUR);
	nbyte = read(fd, buf, 255);
	buf[nbyte] = 0;
	printf("Offset start = %d, nbyte = %d, READ str = %s", (int)start, nbyte, buf);

	cur = lseek(fd, 0, SEEK_CUR);
	printf("Offset cur = %d\n", (int)cur);

	start = lseek(fd, 6, SEEK_SET);
	nbyte = read(fd, buf, 255);
        buf[nbyte] = 0;
        printf("Offset start = %d, nbyte = %d, READ str = %s", (int)start, nbyte, buf);

	end = lseek(fd, -5, SEEK_END); //끝 위치로부터 오프셋이 -5인 위치
	printf("SEEK_ENDD -5 : %ld\n", end);
}

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int fd, fd1;
	
	fd = open("tmp.bbb", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	
	//가능한 파일 기술자를 부여
	fd1 = dup(fd);
	//지정한 파일 기술자를 부여(1번은 표준 출력(화면))
	dup2(fd, 1);
	printf("DUP2 : standard output redirection\n");
	
	close(fd);
	close(fd1);
}

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
	int fd1[2], fd2[2];
	pid_t pid;
	char buf[257];
	int len, status;

	if(pipe(fd1) == -1){
		perror("pipe");
		exit(1);
	}

	if(pipe(fd2) == -1){
		perror("pipe");
		exit(1);
	}

	switch(pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			close(fd1[1]);
			close(fd2[0]);

			len = read(fd1[0], buf, 256);
			write(1, "Child Process:", 15);
			write(1, buf, len);

			strcpy(buf, "Good\n");
			write(fd2[1], buf, strlen(buf));
			break;
		default:
			close(fd1[0]);
			close(fd2[1]);

			write(fd1[1], "Hello\n", 6);

			len = read(fd2[0], buf, 256);
			write(1, "Parent Process:", 15);
			write(1, buf, len);
			wait(NULL);
			break;
	}
}

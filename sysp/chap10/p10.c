#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
	int fd[2], len;
	pid_t pid;
	char buf[256];

	if(pipe(fd)==-1){
		perror("pipe");
		exit(1);
	}

	switch(pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			close(fd[0]);
			write(1, "Input Message:", 14);
			len = read(0, buf, sizeof(buf));
			write(fd[1], buf, len);
			close(fd[1]);
			break;
		default:
			close(fd[1]);
			wait(NULL);
			write(1, "Child Process Said:", 20);
			len = read(fd[0], buf, 256);
			write(1, buf, len);
			break;
	}
}

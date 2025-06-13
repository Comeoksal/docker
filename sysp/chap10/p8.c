#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd[2], len;
	pid_t pid;
	char buf[256];

	if(argc!=2){
		printf("Usage : %s argname\n", argv[0]);
		exit(1);
	}

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
			strcpy(buf, argv[1]);
			write(1, "Child Process:", 15);
			printf("%s\n", buf);
			write(fd[1], buf, 256);
			close(fd[1]);
			break;
		default:
			close(fd[1]);
			wait(NULL);
			write(1, "Parent Process:", 15);
			len = read(fd[0], buf, 256);
			printf("%s\n", buf);
			buf[len] = '\0';
			execlp("man", "man", buf, (char *)NULL);
			break;
	}
}

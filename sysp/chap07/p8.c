#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t pid;
	char wd[BUFSIZ];

	switch(pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			getcwd(wd, BUFSIZ);
			printf("-->Child : %s\n", wd);
			break;
		default:
			printf("-->Parent\n");
			execl("/bin/ls", "ls", "-a", (char *)NULL);
			break;
		}
}

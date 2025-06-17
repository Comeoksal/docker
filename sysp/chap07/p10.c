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
			switch(pid = fork()){
				case -1:
					perror("fork");
					exit(1);
					break;
				case 0:
					printf("Baby Process\n");
					exit(0);
					break;
				default:
					printf("-->Parent : Baby PID : %d\n", pid);
					break;
			}
			break;
		default:
			printf("-->Grand Parent : Child PID : %d\n", pid);
			break;
		}
}

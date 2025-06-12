#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t pid;
	pid_t pid2;

	switch(pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			switch(pid2 = fork()){
				case -1:
					perror("fork");
					exit(1);
					break;
				case 0:
					printf("Baby Process : my Parent PID : %d\n", getppid());
					exit(0);
					break;
				default:
					printf("-->Parent : Baby PID : %d\n", pid2);
					printf("--->Parent : my Parent(Grand) PID : %d\n", getppid());
					break;
			}
			break;
		default:
			printf("-->Grand Parent : Child PID : %d\n", pid);
			printf("--->Grand Parent : my Parent(Bash) PID : %d\n", getppid());
			break;
		}
}

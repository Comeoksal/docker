#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int status;
	pid_t pid;
	pid_t pid2;

	switch(pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			execlp("ls", "ls", "-a",  (char *)NULL);
			perror("execlp");
			break;
		default:
			waitpid(pid, &status, 0);
			printf("-->Grand Parent : Child PID : %d\n", pid);
			printf("--->Grand Parent : my Parent(Bash) PID : %d\n", getppid());
			break;
		}
}

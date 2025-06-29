#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	pid_t pid;

	switch(pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			printf("-->Child\n");
			if(execlp("ls", "ls", "-a", (char *)NULL) == -1){
				perror("execlp");
				exit(1);
			}
			exit(0);
			break;
		default:
			printf("--> Parent - My PID:%d\n", (int)getpid());
			break;
		}
}

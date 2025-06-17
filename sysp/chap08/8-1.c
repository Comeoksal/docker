#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main(){
	printf("Before SIGCONT to parent.\n");
	kill(getppid(), SIGCONT);

	printf("Before SIGQUIT to me.\n");
	kill(getpid(), SIGKILL);

	printf("======================");
}

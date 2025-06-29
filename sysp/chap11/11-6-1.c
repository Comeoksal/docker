#include <sys/mman.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void handler(int dummy){
	;
}

int main(){
	key_t key;
	int shmid;
	void *shmaddr;

	char buf[1024];
	sigset_t mask;

	key = ftok("shmfile", 1);
	shmid = shmget(key, 1024, IPC_CREAT | 0666);

	sigfillset(&mask);
	sigdelset(&mask, SIGUSR1);
	signal(SIGUSR1, handler);

	printf("Listener wait for Talker\n");
	sigsuspend(&mask);

	printf("Listener Start =====\n");
	shmaddr = shmat(shmid, NULL, 0);
	strcpy(buf, shmaddr);

	printf("Listener Received : %s\n", buf);

	strcpy(shmaddr, "Have a nice day\n");
	sleep(3);
	shmdt(shmaddr);
}

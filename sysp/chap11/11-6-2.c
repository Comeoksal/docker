#include <sys/mman.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	key_t key;
	int shmid;
	void *shmaddr;

	char buf[1024];
	sigset_t mask;

	key = ftok("shmfile", 1);
	shmid = shmget(key, 1024, 0);
	
	shmaddr = shmat(shmid, NULL, 0);
	strcpy(shmaddr, "Hello I'm Talker\n");

	kill(atoi(argv[1]), SIGUSR1);
	sleep(2);
	strcpy(buf, shmaddr);

	printf("Listener said : %s\n", buf);
	system("ipcs -m");
	shmdt(shmaddr);
	shmctl(shmid, IPC_RMID, NULL);
}

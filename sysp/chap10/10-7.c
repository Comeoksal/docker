#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(){
	int pd, n;
	char msg[] = "Hello, FIFO";

	printf("Server ==========\n");

	if(mkfifo("./S_FIFO", 0666) ==-1 && errno != EEXIST){
		perror("mkfifo");
		exit(1);
	}

	if((pd = open("./S_FIFO", O_WRONLY)) == -1){
		perror("open");
		exit(1);
	}

	printf("To Client : %s\n", msg);

	n = write(pd, msg, strlen(msg)+1);
	if(n==-1){
		perror("write");
		exit(1);
	}
	close(pd);
}

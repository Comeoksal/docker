#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	int pd, len, fd;
	char buf[BUFSIZ];
	pid_t pid;
	if(argc!=2){
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}

	if(mkfifo("./13FIFO", 0666) == -1 && errno != EEXIST){
		perror("mkfifo");
		exit(1);
	}

	switch(pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			if((pd = open("./13FIFO", O_WRONLY)) == -1){
				perror("open");
				exit(1);
			}
			if((fd = open(argv[1], O_RDONLY)) == -1){
				perror("open");
				exit(1);
			}
			len = read(fd, buf, sizeof(buf));
			write(pd, buf, len);
			break;
		default:
			if((pd = open("./13FIFO", O_RDONLY)) == -1){
				perror("open");
				exit(1);
			}
			wait(NULL);
			if((fd = open("zzz.txt", O_RDWR | O_CREAT), 0666) == -1){
				perror("open");
				exit(1);
			}
			len = read(pd, buf, sizeof(buf));
			buf[len] = '\0';
			write(1, buf, len);
			write(fd, buf, len);
			break;
	}
}

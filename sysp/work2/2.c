#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

void read_and_print();

int main(){
	int fd, status;
	char buf[BUFSIZ];
	pid_t pid;
	
	pid = fork();
	if(pid>0){
		printf("Input an expression : ");
		if(fgets(buf, sizeof(buf), stdin) == NULL){
			perror("input fail");
			exit(1);
		}
		fd = open("input.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fd==-1){
			perror("open fail");
			exit(1);
		}
		if(write(fd, buf, strlen(buf)) != strlen(buf)){
			perror("write fail");
			exit(1);
		}
	} else if (pid == 0){
		read_and_print();
	} else {
		perror("fork fail");
		exit(1);
	}
	return 0;
}

void read_and_print(){
	int fd, nbyte, len, idx=0;
	char c, buf[BUFSIZ];

	fd = open("input.txt", O_RDONLY);
	if(fd==-1){
		perror("open fail");
		exit(1);
	}

}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

void read_and_input();

int main(){
	int fd, status;
	char buf[BUFSIZ];
	pid_t pid;

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
	switch(pid=fork()){
		case -1:
			perror("fork fail");
			exit(1);
		case 0:
			read_and_input();
			break;
		default:
			while(wait(&status) !=pid){
				continue;
			}
			break;
	}
	return 0;
}

void read_and_input(){
	int fd, nbyte, len, idx=0;
	char c, buf[BUFSIZ];

	fd = open("input.txt", O_RDONLY);
	if(fd==-1){
		perror("open fail");
		exit(1);
	}
	len = read(fd, buf, sizeof(buf));
	int stack[len];

	lseek(fd, 0, SEEK_SET);
	while((nbyte = read(fd, &c, 1)) > 0) {
		int isMinus = 0;
		switch(c){
			case '+':
				break;
			case '-':
				isMinus = 1;
				break;
			case '*':
				idx--;
				

	}
}

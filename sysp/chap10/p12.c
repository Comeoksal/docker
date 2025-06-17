#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
	int fd1[2], fd2[2], len;
	pid_t pid;
	char buf[256], name[10], sendbuf[1024]="";


	if(pipe(fd1)==-1){
		perror("pipe");
		exit(1);
	}

	if(pipe(fd2)==-1){
                perror("pipe");
                exit(1);
        }

	switch(pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			close(fd1[1]);
			close(fd2[0]);
			strcpy(name, "[Child] ");
			while(1){
				sendbuf[0]='\0';
				buf[0] = '\0';
				len = read(fd1[0], sendbuf, sizeof(sendbuf));
				sendbuf[len] = '\0';
				write(1, sendbuf, len);
				write(1, "Input Message(Child): ", 22);
				len = read(0, buf, sizeof(buf));
				buf[len] ='\0';
				sendbuf[0] = '\0';
				strcat(sendbuf, name);
				strcat(sendbuf, buf);
				write(fd2[1], sendbuf, strlen(sendbuf));
			}
			break;
		default:
			close(fd1[0]);
			close(fd2[1]);
			strcpy(name, "[Parent] ");
			while(1){
				sendbuf[0]='\0';
				buf[0] = '\0';
				write(1, "Input Message(Parent): ", 23);
				len = read(0, buf, sizeof(buf));
				buf[len] = '\0';
				strcat(sendbuf, name);
				strcat(sendbuf, buf);
				write(fd1[1], sendbuf, strlen(sendbuf));
				sendbuf[0]='\0';
				len = read(fd2[0], sendbuf, sizeof(sendbuf));
				sendbuf[len] = '\0';
				write(1, sendbuf, len);
			}
			break;
	}	
}


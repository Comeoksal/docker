#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAXLINE 1014
#define NAMELEN 10
int main(){
	int pd[2], namelen, len;
	char sendbuf[MAXLINE+NAMELEN], recvbuf[MAXLINE+NAMELEN], *bufmsg;
	
	if(mkfifo("./14-1FIFO", 0666) == -1 && errno != EEXIST){
		perror("mkfifo");
		exit(1);
	}
	if(mkfifo("./14-2FIFO", 0666) == -1 && errno != EEXIST){
                perror("mkfifo");
                exit(1);
        }
	if((pd[1] = open("./14-1FIFO", O_WRONLY)) == -1){
		perror("open");
		exit(1);
	}
	if((pd[0] = open("./14-2FIFO", O_RDONLY)) == -1){
		perror("open");
		exit(1);
	}
	snprintf(sendbuf, sizeof(sendbuf), "[%s] ", "14-1");
	namelen = strlen(sendbuf);
	bufmsg = sendbuf + namelen;
	while(1){
		memset(recvbuf, 0, sizeof(recvbuf));
		
		write(1, "Input Message(14-1): ", 21);
		len = read(0, bufmsg, 1014);
		bufmsg[len] = '\0';
		write(pd[1], sendbuf, strlen(sendbuf));

		len = read(pd[0], recvbuf, sizeof(recvbuf));
		write(1, recvbuf, strlen(recvbuf));
	}
}
	

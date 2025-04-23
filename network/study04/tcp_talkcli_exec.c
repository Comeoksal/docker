#include "netprog.h"
#define MAXLINE 511

int input_and_send(int sd);

int main(int argc, char *argv[]){
	struct sockaddr_in servaddr;
	int s, nbyte;
	pid_t pid;

	if(argc!=3){
		printf("usage : ");
		exit(0);
	}
	if((s = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		errquit();
	}
	bzero((char*)&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	servaddr.sin_port = htons(atoi(argv[2]));

	if(connect(s, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
		errquit();
	}

	if((pid = fork()) > 0){
		input_and_send(s);
	} else if(pid==0){
		char line[80];
		sprintf(line, "%d", s);
		execl("tcp_talkexec", "tcp_talkexec", line);
	}
	close(s);
	return 0;
}

int input_and_send(int sd){
	char buf[MAXLINE+1];

	while(fgets(buf, sizeof(buf), stdin) !=NULL) {
		write(sd, buf, sizeof(buf));

		if(strstr(buf, EXIT_STRING) !=NULL) {
			puts("bye");
			close(sd);
			exit(0);
		}
	}
	return 0;
}

#include "netprog.h"
#define MAXLINE 511

int recv_and_print(int sd);
int input_and_send(int sd);

int main(int argc, char*argv[]){
	static struct sockaddr_in servaddr;
	static int s;
	pid_t pid;

	if(argc!=3){
		printf("usage : ");
		exit(0);
	}
	if((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		errquit();
	}
	bzero((char*)&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	servaddr.sin_pot = htons(atoi(argv[2]));

	if(connect(s, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
		errquit();
	}

	if((pid=fork()) > 0) {
		input_and_send(s);
	} else if(pid==0){
		recv_and_print(s);
	}
	close(s);
	return 0;
}

int input_and_send(int sd){
	char buf[MAXLINE+1];
	int nbyte;

	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		write(sd, buf, sizeof(buf));

		if(strstr(buf, EXIT_STRING) !=NULL){
			puts("bye");
			close(sd);
			exit(0);
		}
	}
	return 0;
}
int recv_and_print(int sd){
	char buf[MAXLINE+1];
	int nbyte;

	while(1) {
		if((nbyte = read(sd, buf, MAXLINE)) < 0){
			errquit();
			close(sd);
			exit(0);
		}
		buf[nbyte] = 0;

		if(strstr(buf, EXIT_STRING) !=NULL){
			break;
		}
		printf("%s", buf);
	}
	return 0;
}


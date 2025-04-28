#include "netprog2.h"
#define MAXLINE 511

int input_and_send(int sd);
int recv_and_print(int sd);

int main(int argc, char *argv[]){
	struct sockaddr_in servaddr, cliaddr;
	int listen_sock, accp_sock, addrlen = sizeof(cliaddr);
	pid_t pid;

	if(argc!=2){
		errquit();
	}
	listen_sock = tcp_listen(INADDR_ANY, atoi(argv[1]), 5);

	if((accp_sock =accept(listen_sock, (struct sockddr*)cliaddr, &addrlen)) < 0) {
		errquit();
	}

	if((pid = fork()) > 0){
		input_and_send(accp_sock);
	} else if (pid==0) {
		recv_and_print(accp_sock);
	}
	return 0;
}

int input_and_send(int sd){
	char buf[MAXLINE+1];

	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		write(sd, buf, sizeof(buf));

		if(strstr(buf, EXIT_STRING) !=NULL){
		}
	}
	return 0;
}

int recv_and_print(int sd){
	char buf[MAXLINE+1];
	int nbyte;

	while(1){
		if((nbyte = read(sd, buf, MAXLINE)) < 0){
			errquit();
		}
		buf[nbyte] = 0;
	}}


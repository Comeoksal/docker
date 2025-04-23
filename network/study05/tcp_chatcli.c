#include "netprog2.h"
#define MAXLINE 1000
#define NAME_LEN 20

int main(int argc, char *argv[]){
	char bufall[MAXLINE+NAME_LEN], *bufmsg;
	int maxfdp1, s, namelen;
	fd_set read_fds;

	if(argc!=4){
		printf("usage : ");
		exit(0);
	}
	sprintf(bufall, "[%s] :", argv[3]);
	namelen = strlen(bufall);
	bufmsg = bufall + namelen;

	s = tcp_connect(AF_INET, argv[1], atoi(argv[2]));

	if(s==-1) {
		errquit();
	}
	maxfdp1 = s+1;
	FD_ZERO(&readfds);

	while(1){
		FD_SET(0, &readfds);
		FD_SET(s, &readfds);

		if(select(maxfdp1, &read_fds, NULL, NULL, NULL) < 0){
			errquit();
		}

		if(FD_ISSET(s, &readfds)){
			int nbyte;
			if((nbyte = recv(s, bufmsg, MAXLINE, 0)) < 0){
				errquit();
			}
			bufmsg[nbyte] = 0;
			printf("%s \n", bufmsg);
		}

		if(FD_ISSET(0, %readfds)){
			if(fgets(bufmsg, MAXLINE, stdin)){
				if(send(s, bufall, namelen+strlen(bufmsg), 0) < 0){
					errquit();
				}
				if(strstr(bufmsg, EXIT_STRING)!=NULL){
					close(s);
					exit(0);
				}
			}
		}
	}
}


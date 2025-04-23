#include "netprog.h"
#define MAXLINE 511

int input_and_send(int sd);
int recv_and_print(int sd);

int main(int argc, char *argv[]){
	struct sockaddr_in servaddr, cliaddr;
	int listen_sock, accp_sock, addrlen = sizeof(cliaddr);
	pid_t pid;

	if(argc !=2){
		printf("usage :");
		exit(0);
	}
	if((s = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		errquit();
	}
	bzero((char*)&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));

	if(bind(listen_sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
		errquit();
	}
	puts("서버가 클라이언트 대기 중");
	
	listen(listen_sock, 1);

	if((accp_sock = accept(listen_sock, (struct sockaddr*)&cliaddr, &addrlen)) < 0){
		errquit();
	}

	puts("클라이언트 연결");
	if((pid = fork()) > 0) {
		input_and_send(accp_sock);
	} else if(pid==0) {
		recv_and_print(accp_sock);
	}

	close(accp_sock);
	close(listen_sock);
	return 0;
}

int input_and_send(int sd){
	char buf[MAXLINE+1];

	while(fgets(buf, sizeof(buf), stdin) !=NULL) {
		wrtie(sd, buf, sizeof(buf));

		if(strstr(buf, EXIT_STRING) !=NULL) {
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

	while(1){
		if((nbyte = read(sd, buf, MAXLINE)) < 0){
			errquit();
			exit(0);
		}
		buf[nbyte] = 0;

		if(strstr(buf, EXIT_STRING) !=NULL) {
			break;
		}
		prinitf("%s", buf);
	}
	return 0;
}

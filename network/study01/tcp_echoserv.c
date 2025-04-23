#include "netprog.h"
#define MAXLINE 127

int main(int argc, char *argv[]){
	struct sockaddr_in servaddr, cliaddr;
	int listen_sock, accp_sock, nbyte, addrlen = sizeof(cliaddr);
	char buf[MAXLINE+1];

	if(argc!=2){
		printf("USAGE : ");
		exit(0);
	}

	if((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		errquit();
	}

	bzero((char *)&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));

	if(bind(listen_sock, (struct sockaddr*)servaddr, sizeof(servaddr)) < 0) {
		errquit();
	}

	listen(listen_sock, 5);

	while(1){
		puts("서버가 대기 중..");
		
		accp_sock = accept(listen_sock, (struct sockaddr*)&cliaddr, &addrlen);

		if(accp_sock < 0){
			errquit();
		}

		puts("클라이언트 연결 됨");
		nbyte = read(accp_sock, buf, MAXLINE);
		write(accp_sock, buf, nbyte);

		close(accp_sock);
	}
	close(listen_sock);
}

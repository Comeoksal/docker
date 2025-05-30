#include "netprog.h"
#define MAXLINE 512

int main(int argc, char *argv[]){
	struct sockaddr_in servaddr, cliaddr;
	int s, nbyte, addrlen = sizeof(cliaddr);
	char buf[MAXLINE+1];

	if(argc!=2){
		printf("usage : ");
		exit(0);
	}
	if((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
		errquit();
	}
	bzero((char*)&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));

	if(bind(s, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		errquit();
	}

	while(1){
		puts("서버 대기 중...");
		
		nbyte = recvfrom(s, buf, MAXLINE, 0, (struct sockaddr*)&cliaddr, &addrlen);
		if(nbyte < 0){
			errquit();
		}
		buf[nbyte] = 0;
		printf("%s", buf);

		if(sendto(s, buf, nbyte, 0, (struct sockaddr*)&cliaddr, addrlen) < 0){
			errquit();
		}
	}
}

#include "netprog.h"
#define MAXLINE 511

struct calcmsg {
	char type;
	char status;
	char op;
	char padding;
	int32_t op1, op2;
}

int main(int argc, char *argv[]){
	struct sockaddr_in servaddr, cliaddr;
	int s, nbyte, addrlen = sizeof(cliaddr);
	char buf[MAXLINE+1];

	if(argc!=2){
		printf("usage:");
		exit(0);
	}

	if((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		errquit();
	}

	bzero((char*)&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));

	if(bind(s, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0 ){
		errquit();
	}

	struct calcmsg reqmsg;
	while(1){
		puts("서버 대기 중...");
		if((nbyte = recvfrom(s, &reqmsg, sizeof(reqmsg), 0, (struct sockaddr*)&cliaddr, &addrlen)) < 0){
			errquit();
		}
		struct calcmsg rspmsg;
		rspmsg.type = 1;
		rspmsg.op = reqmsg.op;
		rspmsg.op1 = ntohl(reqmsg.op1);
		rspmsg.op2 = ntohl(reqmsg.op2);
		sendmsg.status = 0;
		switch(rspmsg.op){
			case '+': 
		}

		if(sendto(s, &rspmsg, sizeof(rspmsg), 0, (struct sockaddr*)&cliaddr, addrlen) < 0){
			errquit();
		}
	}
}

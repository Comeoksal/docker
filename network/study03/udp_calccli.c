#include "netprog.h"
#define MALINE 511

struct calcmsg{
	char type; //0:req, 1:resp
	char status;
	char op;
	int32_t op1, op2, result;
}

int main(int argc, char *argv[]){
	struct sockaddr_in servaddr;
	int s, nbyte; addrlen = sizeof(servaddr);
	char buf[MAXLINE+1];

	if(argc!=3){
		printf("usage:");
		exit(0);
	}

	if((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0 ) {
		errquit();
	}
	bzero((char*)&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	servaddr.sin_port = htons(atoi(argv[2]));

	printf("입력 : ");
	char op;
	int32_t op1, op2;
	scanf("%d %c %d", op1, op, op2);

	struct calcmsg reqmsg;
	reqmsg.type = 0;
	reqmsg.status = 0;
	reqmsg.op = op;
	reqmsg.op1 = htonl(op1);
	reqmsg.op2 = htonl(op2);

	if(sendto(s, &reqmsg, sizeof(reqmsg), 0, (struct sockaddr*)&servaddr, addrlen) < 0 ) {
		errquit();
	}

	struct calcmsg rspmsg;
	if((nbyte = recvfrom(s, &rspmsg, sizeof(rspmsg), 0, (struct sockaddr*)&servaddr, &addrlen)) < 0){
		errquit();
	}
	if(rspmsg.status==0) {
		printf("출력 : %d %c %d = %d", ntohl(rspmsg.op1), rspmg.op, ntohl(rspmsg.op2), ntohl(rspmsg.result));
	} else {
		errquit();
	}

	close(s);
}

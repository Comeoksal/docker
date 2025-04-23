#include "netprog.h"
#define MAXLINE 127

int main(int argc, char *argv[]){
	struct sockaddr_in servaddr;
	int s, nbyte;
	char buf[MAXLINE+1];

	if(argc!=3){
		printf("Usage : \n");
		exit(0);
	}

	if((s = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		errquit();
	}

	bzero((char*)&servaddr, sizeof(servaddr)); //서버 주소 구조체 초기화
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	servaddr.sin_port = htons(atoi(argv[2]));

	if(connect(s, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
		errquit();
	}

	printf("입력 : ");
	if(fgets(buf, sizeof(buf), stdin) == NULL){
		errquit();
	}

	nbyte = strlen(buf);
	if(write(s, buf, nbyte) < 0){
		errquit();
	}

	printf("수신 : ");
	if((nbyte = read(s, buf, MAXLINE)) < 0){
		errquit();
	}

	buf[nbyte] = 0;
	printf("%s", buf);
	close(s);

	return 0;
}

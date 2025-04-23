#include "netprog.h"
#define MAXLINE 511

int main(int argc, char*argv[]){
	char buf[MAXLINE+1];
	int sd, nbyte;

	sd = atoi(argv[1]);

	while(1){
		if((nbyte = read(sd, buf, MAXLINE)) < 0){
			errquit();
		}
		buf[nbyte] = 0;
		if(strstr(buf, EXIT_STRING)!=NULL) {
			break;
		}
		printf("%s", buf);
	}
	close(sd);
}

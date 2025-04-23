#include "netprog2.h"
#define MAXLINE 511
#define MAX_SOCK 1024

int num_chat = 0;
int listen_sock, clisock_list[MAX_SOCK];

void addClient(int sd, struct sockaddr_in *newcliaddr);
void removeClient(int i);
int getmax();
int set_nonblock(int sockfd);
int is_nonblock(int sockfd);

int main(int argc, char *argv[]){
	struct sockaddr_in cliaddr;
	char buf[MAXLINE+1];
	int i, j, nbyte, maxfdp1, accp_sock, addrlen = sizeof(cliaddr);

	if(argc!=2){
		printf("usage :");
		exit(0);
	}
	listen_sock = tcp_listen(INADDR_ANY, atoi(argv[1]), 5);
	if(listen_sock==-1){
		errquit();
	}
	if(set_nonblock(listen_sock)==-1){
		errquit();
	}
	while(1){
		sleep(1);
		putchar('.');
		fflush(stdout);

		accp_sock = accept(listen_sock, (struct sockaddr*)&cliaddr, &addrlen);
		if(accp_sock == -1 && errno != EWOULDBLOCK){
			errquit();
		} else if(accp_sock > 0){
			if(is_nonb(accp_sock) !=0 && set_nonb(accp_sock) < 0){
				errquit();
			}
			addClient(accp_sock, &cliaddr);
			send(accp_sock, START_STRING, strlen(START_STRING), 0);
			printf("사용자 추가 : ");
		}
		for(i=0; i<num_chat; i++){
			errno = 0;
			nbyte = recv(clisock_list[i], buf, MAXLINE, 0);
			if(nbyte==0){
				removeClient(i);
				continue;
			} else if(nbyte == -1 && errno ==EWOULDBLOCK){
				continue;
			}
			buf[nbyte] = 0;
			if(strstr(buf, EXIT_STRING) !=NULL){
				removeClient(i);
				continue;
			}
			for(j=0; j<num_chat; j++){
				send(clisock_list[j], buf, nbyte, 0);
			}
		}
	}
}

void addClient(int sd, struct sockaddr_in *newcliaddr){
	char buf[20];
	inet_ntop(AF_INET, &newcliaddr->sin_addr, buf, sizeof(buf));
	printf("new Client : %s(%d)", buf, ntohs(newcliaddr->sin_port));

	clisock_list[num_chat] = sd;
	num_chat++;
}
void removeClient(int i){
	close(clisock_list[i]);

	if(i!=num_chat-1){
		clisock_list[i] = clisock_list[num_chat-1];
	}
	num_chat--;
}

int getmax(){
	int max = listen_sock;
	int i;
	for(i=0; i<num_chat; i++){
		if(clisock_list[i]>max){
			max = clisock_list[i];
		}
	}
	return max;
}

int is_nonblock(int sockfd){
	int val = fcntl(sockfd, F_GETFL, 0);
	if(val & O_NONBLOCK){
		return 0;
	}
	return -1;
}

int set_nonblock(int sockfd){
	int val = fcntl(sockfd, F_GETFL, 0);
	if(fcntl(sockfd, F_SETFL, val|O_NONBLOCK, 0) == -1){
		return -1;
	}
	return 0;
}


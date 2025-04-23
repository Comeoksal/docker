#include "netprog2.h"
#define MAXLINE 511
#define MAX_SOCK 1024

int numchat = 0;
int listen_sock, clisock_list[MAX_SOCK];

void addClient(int s, struct sockaddr_in *newcliaddr);
void removeClient(int s);
int getmax();

int main(int argc, char*argv[]){
	struct sockaddr_in cliaddr;
	char buf[MAXLIE+1];

	int i, j, nbyte, maxfdp1, accp_sock, addrlen = sizeof(cliaddr);
	fd_set read_fds;

	if(argc!=2){
		printf("usage : ");
		exit(0);
	}
	listen_sock = tcp_listen(INADDR_ANY, atoi(argv[1]), 5);

	while(1){
		FD_ZERO(&read_fds);
		FD_SET(listen_sock, &read_fds);
		for(i=0; i<numchat; i++){
			FD_SET(clisock_list[i], &read_fds);
		}
		maxfdp1 = getmax()+1;

		puts("wait for client");
		if(select(maxfdp1, &read_fds, NULL, NULL, NULL) < 0){
			errquit();
		}
		if(FD_ISSET(listen_sock, &read_fds)){
			accp_sock = accept(listen_sock, (struct sockaddr*)cliaddr, &addrlen);
			if(accp_sock == -1){
				errquit();
			}
			addClient(accp_sock, &cliaddr);
			send(accp_sock, START_STRING, strlen(START_STRING), 0);
			printf("%d번째 사용자 추가", numchat);
		}

		for(i=0; i<num_chat; i++){
			if(FD_ISSET(clisock_list[i], &read_fds)){
				nbyte = recv(clisock_list[i], buf, MAXLINE, 0);
				if(nbyte <=0){
					removeClient(i);
					continue;
				}
				buf[nbyte] = 0;
				if(strstr(buf, EXIT_STRING)!=NULL){
					removeClient(i);
					continue;
				}
				for(j=0; j<num_chat; j++){
					send(clisock_list[j], buf, nbyte, 0);
				}
			}
		}
	}
	return 0;
}

void addClient(int s, struct sockaddr_in *newcliaddr){
	char buf[20];
	inet_ntop(AF_INET, &newcliaddr->sin_addr, buf, sizeof(buf));
	printf("new client : %s(%d)", buf, ntohs(newcliaddr->sin_port));

	clisock_list[num_chat] = s;
	num_chat++;
}

void removeClient(int i){
	close(clisock_list[i]);
	if(i != num_chat-1){
		clisock_list[i] = clisock_list[num_chat-1];
	}
	num_chat--;

}

int getmax(){
	int max = listen_sock;
	int i;
	for(i=0; i<num_chat; i++){
		if(clisock_list[i] > max){
			max = clisock_list[i];
		}
	}
	return max;
}


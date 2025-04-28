#include "netprog2.h"
#define MAXLINE 511
#define MAX_SOCK 1024

int num_chat = 0;
int listen_sock, clisock_list[MAX_SOCK]

void addClient(int sd, struct sockaddr_in* newcliaddr);
void removeClient(int i);
int getmax();

int main(int argc, char*argv[]){
	struct sockaddr_in cliaddr;
	char buf[MAXLINE+1];
	int i, j, nbyte, maxfdp1, accp_sock, addrlen = sizeof(cliaddr);
	fd_set read_fds;

	listen_sock = tcp_listen(INADDR_ANY, atoi(argv[1]), 5);

	while(1){
		FD_ZERO(&read_fds);
		FS_SET(listen_sock, &read_fds);
		for(i=0; i<num_chat; i++){
			FD_SET(clisock_list[i], &read_fds);
		}
		maxfdp1 = getmax() + 1;
		if(select(maxfdp1, &read_fds, NULL, NULL, NULL) < 0){
			errquit();
		}

		if(FS_ISSET(listen_sock, &read_fds)){
			accp_sock = accept(listen_sock, (struct sockaddr*)&cliaddr, &addrlen);

			addClient(accp_sock, &cliaddr);
		}

		for(i=0; i<num_chat; i++){
			if(FD_ISSET(clisock_list[i], &read_fds)){
				nbyte = read

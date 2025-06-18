#include "netprog2.h"
#include <pthread.h>

#define MAXLINE 1024
#define MAX_SOCK 10
void addClient(int sock);
void removeClient(int sock);
void *recv_and_send(void *arg);

int socklist[MAX_SOCK];
int num_chat = 0;
pthread_mutex_t socklist_lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct{
	char name[20], msg[1001];
}User;

int main(int argc, char *argv[]){
	struct sockaddr_in cliaddr;
	int listen_sock, sock, addrlen = sizeof(cliaddr);

	if(argc !=2){
		printf("usage : %s port\n", argv[0]);
		exit(1);
	}
	listen_sock = tcp_listen(INADDR_ANY, atoi(argv[1]), 5);

	while(1){
		sock = accept(listen_sock, (struct sockaddr*)&cliaddr, &addrlen);
		printf("사용자 연결 %d\n", sock);
		addClient(sock);
	}
	return 0;
}

void addClient(int sock){
	pthread_t tid;

	pthread_mutex_lock(&socklist_lock);
	socklist[num_chat] = sock;
	num_chat++;
	pthread_mutex_unlock(&socklist_lock);

	pthread_create(&tid, NULL, recv_and_send, &sock);
}

void removeClient(int sock){
	int i;
	
	pthread_mutex_lock(&socklist_lock);
	for(i=0; i<num_chat; i++){
		if(sock==socklist[i]){
			if(i!=num_chat-1){
				socklist[i] = socklist[num_chat-1];
			}
			pthread_mutex_unlock(&socklist_lock);
			break;
		}
	}
	num_chat--;
	close(sock);
}

void *recv_and_send(void *arg){
	int i, nbyte, sock = *((int *)arg);
	char name[20];
	User user;

	while(1){
		nbyte = read(sock, &user, sizeof(user));
		printf("%s : %s\n", user.name, user.msg);
		if(strcmp(user.msg, "Joined.") == 0){
			strcpy(name, user.name);
		}
		if(nbyte<=0 || strcmp(user.msg, "exit") == 0){
			close(sock);
			removeClient(sock);
			strcpy(user.msg, "Left.");
		}
		pthread_mutex_lock(&socklist_lock);
		for(i=0; i<num_chat; i++){
			write(socklist[i], &user, sizeof(user));
		}
		pthread_mutex_unlock(&socklist_lock);
	}
}

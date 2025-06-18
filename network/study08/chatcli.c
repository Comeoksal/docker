#include "netprog2.h"
#include <pthread.h>

#define MAXLINE 1024

void *send_msg(void *arg);
void *recv_msg(void *arg);

typedef struct{
	char name[20], msg[1001];
}User;

User user;

pthread_mutex_t user_lock = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]){
	int sock, nbyte;
	pthread_t sendtid, recvtid;
	if(argc!=4){
		printf("usage : %s server_ip port name\n", argv[0]);
		exit(1);
	}
	strcpy(user.name, argv[3]);
	strcpy(user.msg, "Joined.");
	sock = tcp_connect(AF_INET, argv[1], atoi(argv[2]));
	
	write(sock, &user, sizeof(user));
	pthread_create(&sendtid, NULL, send_msg, &sock);
	pthread_create(&recvtid, NULL, recv_msg, &sock);

	pthread_join(recvtid, NULL);
	pthread_cancel(sendtid);

	return 0;
}

void *send_msg(void *arg){
	int nbyte, sock = *((int *)arg);
	char buf[1001];
	
	while(nbyte = read(0, buf, sizeof(buf))){
		buf[nbyte] = 0;
		pthread_mutex_lock(&user_lock);
		strcpy(user.msg, buf);
		write(sock, &user, sizeof(user));
		pthread_mutex_unlock(&user_lock);
		if(strcmp(buf, "exit")==0){
			break;
		}
	}
	return NULL;
}

void *recv_msg(void *arg){
	int sock = *((int *)arg);
	
	while(1){
		pthread_mutex_lock(&user_lock);
		read(sock, &user, sizeof(user));
		printf("%s : %s\n", user.name, user.msg);
		pthread_mutex_unlock(&user_lock);
	}
	return NULL;
}
	

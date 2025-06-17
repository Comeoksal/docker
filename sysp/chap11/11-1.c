#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct mymsgbuf{
	long mtype;
	char mtext[80];
}Message;

int main(){
	key_t key;
	int msgid;
	Message msg;

	key = ftok("keyfile", 1);
	msgid = msgget(key, IPC_CREAT | 0644);
	if(msgid == -1){
		perror("msgget");
		exit(1);
	}

	msg.mtype = 2;
	strcpy(msg.mtext, "Message Q Test");

	if(msgsnd(msgid, &msg, 80, IPC_NOWAIT) == -1){
		perror("msgmd");
		exit(1);
	}
	return 0;
}

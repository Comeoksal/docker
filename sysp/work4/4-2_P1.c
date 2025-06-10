#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct _msg {
    long msg_type;
    char msg_text[BUFSIZ];
} msg_t;

void message_send(int qid, long type, const char *text) {
    msg_t pmsg;
    pmsg.msg_type = type;
    int len = strlen(text);
    strncpy(pmsg.msg_text, text, len);
    pmsg.msg_text[len] = '\0';
    msgsnd(qid, &pmsg, len + 1, 0);
}

char* message_receive(int qid, long type) {
    static msg_t rmsg;
    int nbyte = msgrcv(qid, &rmsg, sizeof(rmsg.msg_text), type, 0);
    rmsg.msg_text[nbyte] = '\0';
    return rmsg.msg_text;
}

int main(){
	key_t key;
	int msgid;
	char select[3];
	
	key = ftok("keyfile", 1);
	if(key == -1){
		perror("ftok");
		exit(1);
	}
	
	msgid = msgget(key, IPC_CREAT|0666);
	if(msgid == -1){
		perror("msgget");
		exit(1);
	}

	while(1){
		char text[BUFSIZ];
		printf("Enter name & score (name score) : ");
		fgets(text, BUFSIZ, stdin);
		message_send(msgid, 1, text);
		
		if(strcmp(text, "\n")==0 || strcmp(text, " \n")==0){
			while(1){
				puts("(1) Print best student's name & score");
				puts("(2) Print average of score");
				puts("(3) Exit");
				printf(">> ");
				fgets(select, 3, stdin);
				
				message_send(msgid, 1, select);
				
				if(strcmp(select, "1\n")==0){ 
					printf("%s\n", message_receive(msgid, 10));
				} else if(strcmp(select, "2\n")==0){
					printf("%s\n", message_receive(msgid, 20));
				} else {
					exit(0);
				}

			}
		}
	}
}

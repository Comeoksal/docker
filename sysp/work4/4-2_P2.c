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

typedef struct {
	char name[20];
	int score;
} Student;

int main(){
	key_t key;
	int msgid, i, select, count = 0, init = 2, bestscore = 0, totalScore = 0;
	char beststudentInfo[1024], averageInfo[1024];
	Student *students = (Student *)malloc(init * sizeof(Student));

	key = ftok("keyfile", 1);
	if(key == -1){
		perror("ftok");
		exit(1);
	}

	msgid = msgget(key, IPC_CREAT |0666);
	if(msgid == -1){
		perror("msgget");
		exit(1);
	}

	puts("Waiting for P1 Enter...");
	while(1){
		char *token;
		char *text = message_receive(msgid, 1);
		if(strlen(text) == 1 || strlen(text) == 2){
			for(i=0; i<count; i++){
				if(students[i].score > bestscore){
					snprintf(beststudentInfo, 1024, "%s %s %d", "best student : ", students[i].name, students[i].score);
					bestscore = students[i].score;
				}
				totalScore += students[i].score;
			}
			snprintf(averageInfo, 1024, "%s %.1f", "score average : ", (float)totalScore/count);
		       	printf("best student info : %s\n", beststudentInfo);
			printf("score average : %s\n", averageInfo);	
			while(1){
				select = atoi(message_receive(msgid, 1));
				
				if(select == 1){
					message_send(msgid, 10, beststudentInfo);
				} else if(select == 2){
					message_send(msgid, 20, averageInfo);
				} else {
					exit(0);
				}
			}
		}
		if(count >= init){
                        init +=1;
                        students = (Student *) realloc(students, init * sizeof(Student));
                }

		token = strtok(text, " ");
		strcpy(students[count].name, token);
		token = strtok(NULL, " ");
		students[count].score = atoi(token);
		
		printf("%d.student name & score : %s %d\n", count+1, students[count].name, students[count].score);
		count++;
	}
}

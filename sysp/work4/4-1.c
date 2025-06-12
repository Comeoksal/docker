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

int main() {
    key_t key;
    int msgid, i, result = 0;
    char text[BUFSIZ];
    key = ftok("keyfile", 1);

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    switch (fork()) {
        case -1:
            perror("fork");
            exit(1);

        case 0:  
            msgid = msgget(key, IPC_CREAT | 0666);
            if (msgid == -1) {
                perror("msgget");
                exit(1);
            }
            for (i = 0; i < 10; i++) {
                result += atoi(message_receive(msgid, 1));
            }
            printf("result : %d\n", result);
            break;

        default:
            msgid = msgget(key, IPC_CREAT | 0600);
            if (msgid == -1) {
                perror("msgget");
                exit(1);
            }
            for (i = 0; i < 10; i++) {
                printf("Enter %dth number : ", i + 1);
                fgets(text, BUFSIZ, stdin);
                message_send(msgid, 1, text);
            }
            wait(NULL);
            break;
    }
    return 0;
}


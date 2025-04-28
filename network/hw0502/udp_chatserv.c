#include "netprog2.h"
#define MAXLINE 1024
#define MAX_SOCK 1024

char *EXIT_STRING = "exit";
char *START_STRING = "start connecting";

int num_chat = 0;
struct sockaddr_in addr_list[MAX_SOCK];

void addClient(struct sockaddr_in *newcliaddr);
void removeClient(struct sockaddr_in *oldcliaddr);

int main(int argc, char *argv[]){
        struct sockaddr_in cliaddr;
        int s, i, nbyte, addrlen = sizeof(cliaddr);
        char buf[MAXLINE+1];

        if(argc!=2){
                printf("usage : %s port\n", argv[0]);
                exit(0);
        }
        s = udp_server_socket(INADDR_ANY, atoi(argv[1]));
        if(s==-1){
            errquit("udp_server_socket fail");
        }

        while(1){
                nbyte = recvfrom(s, buf, MAXLINE, 0, (struct sockaddr*)&cliaddr, &addrlen);
                if(nbyte < 0){
                    errquit("recvfrom fail");
                }
                buf[nbyte]=0;
                if(strstr(buf, START_STRING) !=NULL){
                        addClient(&cliaddr);
                        continue;
                } else if(strstr(buf, EXIT_STRING) !=NULL){
                        removeClient(&cliaddr);
                        continue;
                } else {
			 for(i=0; i<num_chat; i++){
                                if(addr_list[i].sin_addr.s_addr == cliaddr.sin_addr.s_addr && addr_list[i].sin_port == cliaddr.sin_port){
                                        continue;
                                }
                                if(sendto(s, buf, nbyte, 0, (struct sockaddr*)&addr_list[i], addrlen) < 0) {
                                        errquit("sendto message fail");
                                }
                        }
                }
        }
}
void addClient(struct sockaddr_in *newcliaddr){
        char buf[20];
        inet_ntop(AF_INET, &newcliaddr->sin_addr, buf, sizeof(buf));
        addr_list[num_chat++] = *newcliaddr;
        printf("%s:%d 입장, 참가자수 = %d\n", buf, ntohs(newcliaddr->sin_port), num_chat);
}
void removeClient(struct sockaddr_in *oldcliaddr){
        char buf[20];
        int i;
        inet_ntop(AF_INET, &oldcliaddr->sin_addr, buf, sizeof(buf));
        for(i=0; i<num_chat; i++){
                if(addr_list[i].sin_addr.s_addr == oldcliaddr->sin_addr.s_addr && addr_list[i].sin_port == oldcliaddr->sin_port) {
                        addr_list[i] = addr_list[num_chat-1];
                        num_chat--;
                        printf("%s:%d 나감, 참가자수 = %d\n", buf, ntohs(oldcliaddr->sin_port), num_chat);
                        break;
                }
        }
}


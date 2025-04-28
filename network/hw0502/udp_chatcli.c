#include "netprog2.h"
#define MAXLINE 1000
#define NAME_LEN 20

char *EXIT_STRING = "exit";
char *START_STRING = "start connecting";

int main(int argc, char *argv[]){
        struct sockaddr_in servaddr;
        char bufall[MAXLINE+NAME_LEN], *bufmsg;
        int maxfdp1, s, namelen, addrlen = sizeof(servaddr);
        fd_set read_fds;

        if(argc!=4){
                printf("usage : %s server_ip port username\n", argv[0]);
                exit(0);
        }
        sprintf(bufall, "[%s]: ", argv[3]);
        namelen = strlen(bufall);
        bufmsg = bufall+namelen;

        s = udp_client_socket(argv[1], atoi(argv[2]), &servaddr);
        if(s==-1){
                errquit("udp_client_socket fail");
        }
        if(sendto(s, START_STRING, strlen(START_STRING)+1, 0, (struct sockaddr*)&servaddr, addrlen) < 0){
                errquit("sendto start fail");
        }

        puts("채팅방에 입장하였습니다.");
        maxfdp1 = s+1;
        FD_ZERO(&read_fds);

        while(1){
                FD_SET(0, &read_fds);
                FD_SET(s, &read_fds);

                if(select(maxfdp1, &read_fds, NULL, NULL, NULL) < 0){
                        errquit("select fail");
                }
		 if(FD_ISSET(s, &read_fds)){
                        int nbyte;
                        if((nbyte = recvfrom(s, bufmsg, MAXLINE, 0, (struct sockaddr*)&servaddr, &addrlen)) < 0){
                                errquit("recvfrom fail");
                        }
                        bufmsg[nbyte] = 0;
                        printf("%s", bufmsg);
                }
                if(FD_ISSET(0, &read_fds)){
                        if(fgets(bufmsg, MAXLINE, stdin)){
                                if(sendto(s, bufall, namelen+strlen(bufmsg), 0, (struct sockaddr*)&servaddr, addrlen) < 0){
                                        errquit("sendto fail");
                                }
                                if(strstr(bufmsg, EXIT_STRING)!=NULL){
                                        close(s);
                                        exit(0);
                                }
                        }
                }
        }
}


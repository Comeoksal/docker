#include "netprog2.h"
#define BUFSIZE 1024

void file_transfer(int sock);

int main(int argc, char *argv[]){
    struct sockaddr_in cliaddr;
    int listen_sock, sock, addrlen = sizeof(struct sockaddr_in);

    if(argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }
    listen_sock = tcp_listen(AF_INET, atoi(argv[1]), 5);
    while(1){
        sock = accept(listen_sock, (struct sockaddr *)&cliaddr, &addrlen);
       file_transfer(sock);
    }
    return 0;
}

void file_transfer(int sock) {
    int nbyte;
    char buf[BUFSIZE];
    FILE *fp;
    nbyte = read(sock, buf, BUFSIZE);
    fp = fopen(buf, "wb");
    if(!fp) {
        perror("Error opening file for writing");
        close(sock);
        return;
    }
    while(!feof(fp)){
        nbyte = fread(buf, 1, BUFSIZE, fp);
        if(nbyte > 0)
            write(sock, buf, nbyte);
    }
    close(sock);
    fclose(fp);
}

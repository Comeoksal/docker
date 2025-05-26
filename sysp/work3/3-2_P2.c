#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
        int pd1, pd2, nbyte;
        char buf[1024], total[8192]="";

        if((pd1 = open("./P1_to_P2", O_RDONLY)) == -1){
                perror("open pd1");
                exit(1);
        }
        if((pd2 = open("./P2_to_P1", O_WRONLY)) == -1){
                perror("open pd2");
                exit(1);
        }
        while(1){
                puts("Waiting P1 msg..........");
		nbyte = read(pd1, total, sizeof(total));
		total[nbyte] = 0;
		printf("P1 : %s", total);

		write(1, "input your(P2) msg : ", 22);
		nbyte = read(0, buf, sizeof(buf));
		write(pd2, buf, nbyte);
        }
}

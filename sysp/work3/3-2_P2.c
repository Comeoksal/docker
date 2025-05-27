#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
        int pd1, pd2, nbyte, total_byte;
        char buf[1024], total[8192]="", *token;

        if((pd1 = open("./P1_to_P2", O_RDONLY)) == -1){
                perror("open pd1");
                exit(1);
        }
        if((pd2 = open("./P2_to_P1", O_WRONLY)) == -1){
                perror("open pd2");
                exit(1);
        }
        while(1){
		total[0]='\0';
		total_byte=0;
                puts("Waiting P1 msg..........");
		while(1){
			nbyte = read(pd1, buf, sizeof(buf));
			buf[nbyte] = '\0';
			strcat(total, buf);
			total_byte += nbyte;
			if(buf[nbyte-2] == '.'){
				break;
			}
		}
		if(total_byte == 2 && total[total_byte-2] == '.'){
			exit(0);
		}
		token = strtok(total, "\n");
		while(token !=NULL){
			printf("P1 : %s\n", token);
			token = strtok(NULL, "\n");
		}
		
		total[0]='\0';
		total_byte=0;
		while(1){
			write(1, "input your(P2) msg > ", 22);
			nbyte = read(0, buf, sizeof(buf) -1);
			buf[nbyte]='\0';
			write(pd2, buf, nbyte);
			total_byte += nbyte;
			if(buf[nbyte-2] == '.'){
				break;
			}
		}
		if(total_byte == 2 && buf[nbyte-2] == '.'){
			exit(0);
		}
        }
}

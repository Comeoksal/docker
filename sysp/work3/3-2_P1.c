#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(){
	int pd1, pd2, nbyte, total_byte;
	char buf[1024], total[8192]="", *token;

	if(mkfifo("./P1_to_P2", 0666) == -1 && errno != EEXIST){
		perror("mkfifo P1_to_P2");
		exit(1);
	}
	if(mkfifo("./P2_to_P1", 0666) == -1 && errno != EEXIST){
		perror("mkfifo P2_to_P1");
		exit(1);
	}
	if((pd1 = open("./P1_to_P2", O_WRONLY)) == -1){
                perror("open pd1");
                exit(1);
        }
	if((pd2 = open("./P2_to_P1", O_RDONLY)) == -1){
		perror("open pd2");
		exit(1);
	}
	while(1){
		total_byte=0;
		while(1){
			write(1, "input your(P1) msg > ", 22);
			nbyte = read(0, buf, sizeof(buf) -1);
			buf[nbyte] = '\0';
			write(pd1, buf, nbyte);
			total_byte+=nbyte;
			if(buf[nbyte-2] == '.'){
				break;
			}
		}
		if(total_byte == 2 && buf[nbyte-2] == '.'){
			exit(0);
		}
		
		total[0]='\0';
		total_byte=0;
		puts("Waiting P2 msg..........");
		while(1){
			nbyte = read(pd2, buf, sizeof(buf));
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
			printf("P2 : %s\n", token);
			token = strtok(NULL, "\n");
		}
	}
}




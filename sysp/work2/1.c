#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(){
	int status, result=0;
	char c, buf[BUFSIZ], *token;
	pid_t pid;
	
       	while(1){
		printf("Input numbers : ");
                fgets(buf, sizeof(buf), stdin);
		pid = fork();
		if(pid > 0){
			while(wait(&status) !=pid)
                                continue;
                        printf("try again (Y/N) : ");
                        scanf("%c", &c);
                        if(c=='Y'){
                        	getchar();
                                continue;
                        } else {
                                exit(0);
                        }
		} else if(pid==0) {
			token = strtok(buf, " \n");
                        while(token!=NULL){
                        	result+=atoi(token);
                             	token = strtok(NULL, " ");
                        }
                        printf("result = %d\n", result);
                        exit(0);
		} else {
			perror("fork fail");
			exit(1);
		}
	}
	return 0;
}	

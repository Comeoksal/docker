#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(){
	int n, status, countToken=0, result=0;
	char c, buf[BUFSIZ], *token;
	pid_t pid;
	
       	while(1){
		printf("How many numbers to input : ");
		scanf("%d", &n);
		int nums[n];

		printf("Input numbers : ");
		getchar();
                fgets(buf, sizeof(buf), stdin);
		
		pid = fork();
		if(pid > 0){
			while(wait(&status) !=pid)
                                continue;
                        printf("try again (Y/N) : ");
                        scanf(" %c", &c);
                        if(c=='Y'){
				getchar();
                                continue;
                        } else if(c=='N') {
                                exit(0);
                        } else {
				puts("exit(input error)");
				exit(1);
			}
		} else if(pid==0) {
			token = strtok(buf, " \n");
                        while(token!=NULL && countToken < n){
				nums[countToken] = atoi(token);
                        	result+=nums[countToken];
                             	token = strtok(NULL, " ");
				countToken++;
                        }
			if(countToken==n){
            			printf("result = %d\n", result);
            		} else {
            			printf("Please Input %d numbers\n", n);
            		}
			countToken = 0;
                        exit(0);
		} else {
			perror("fork fail");
			exit(1);
		}
	}
	return 0;
}	

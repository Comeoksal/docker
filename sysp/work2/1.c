#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int a, b, status;
	char c;
	pid_t pid;
	
       	while(1){
		printf("Input two numbers : ");
                scanf("%d %d", &a, &b);
		switch(pid=fork()){
			case -1:
				perror("fork");
				exit(1);
			case 0:
				printf("result = %d\n", a+b);
				exit(1);
			default:
				while(wait(&status) !=pid)
					continue;
				printf("try again (Y/N) : ");
				scanf(" %c", &c);
				if(c=='Y'){
					continue;
				} else {
					exit(1);
				}
		}
	}
	return 0;
}	

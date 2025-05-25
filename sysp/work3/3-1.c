#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(){
	DIR *dp;
	int fd1[2], fd2[2];
	int status, count = 0, result = 0, len;
	char buf[1024];
	pid_t pid;

	if(pipe(fd1) == -1){
		perror("pipe");
		exit(1);
	}
	if(pipe(fd2) == -1){
		perror("pipe");
		exit(1);
	}

	switch (pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			close(fd1[1]);
			close(fd2[0]);
			while((len = read(fd1[0], buf, sizeof(buf)))>0){
				buf[len] = 0;
				if(strcmp(buf, "//")==0){
					break;
				}
				chdir(buf);
				dp = opendir(".");
				count = 0;
				while(readdir(dp)){
					count++;
				}
				result+=count;
				closedir(dp);
			}
			write(fd2[1], &result, sizeof(int));
			close(fd1[0]);
			close(fd2[1]);
			break;
		default:
			close(fd1[0]);
			close(fd2[1]);
			while(1){
				write(1, "input directory name(or path): ", 32); 
				len = read(0, buf, sizeof(buf));
				buf[len-1] = 0;
				write(fd1[1], buf, sizeof(buf));
				if(strcmp(buf, "//") == 0){
					break;
				}
			}
			//waitpid(pid, &status, 0);
			len = read(fd2[0], &result, sizeof(int));
			printf("total number of file : %d\n", result);	
			close(fd1[1]);
			close(fd2[0]);
			break;
	}
}



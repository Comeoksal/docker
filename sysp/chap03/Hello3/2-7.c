#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){

	if(rmdir("hanbit2")==-1) {
		perror("rmdir fail : ");
		exit(1);
	}
	return 0;
}

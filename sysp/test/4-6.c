#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int curlen=0, totallen=0;
	int fd, nbyte, totalnbyte;
	char c;
	char buf[1024];
	int idx = 0, count = 0;
	fd = open(argv[1], O_RDONLY);
	
	while(read(fd, &c, 1)== 1){
		if(c=='\n'){
			buf[idx] = 0;
			printf("%s\n", buf);
			idx = 0;
			count++;
			printf("%d : ", count);
		} else {
			buf[idx++] = c;
		}

	}
	printf("%s\n", buf);
	return 0;
}



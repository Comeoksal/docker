#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[]){
	char buf[1024];
	int len = 0, count = 0;
	DIR *dir;
	struct dirent * dent;
	dir = opendir(argv[1]);
	if(dir !=NULL){
		while((dent = readdir(dir)) != NULL) {
			strcpy(buf + len, dent->d_name);
			len +=strlen(dent->d_name);
			buf[len++] = '\n';
			count++;
	}
	closedir(dir);
	printf("%s\nTotal %d files. String length = %d\n", buf, count, len);
	}
}

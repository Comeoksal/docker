#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char*argv[]){
	char *name;
	char oldpath[BUFSIZ], buf[BUFSIZ];
	char *extension;
	int lenOftotal;
	int lenOfex;
	int nbyte;
	strcpy(oldpath, argv[1]);

	name = argv[1];
	lenOftotal = strlen(argv[1]);

	extension = strchr(argv[1], '.');
	lenOfex = strlen(extension);
	
	name[lenOftotal-lenOfex] = 0;
	strcat(name, ".sym");

	symlink(oldpath, name);
	
	nbyte = readlink(name, buf, sizeof(buf));
	buf[nbyte] = 0;
	printf("%s ", buf);

	realpath(name, buf);
	printf("%s\n", buf);
	return 0;
}

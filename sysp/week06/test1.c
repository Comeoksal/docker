#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]){
	DIR *dp;
	char *cwd;

	puts("----opendir 하기 전 경로-------");
	cwd = getcwd(NULL, 0);
	printf("opendir 전 경로 : %s\n", cwd);

	puts("----openrdir 한 후 경로--------");
	dp = opendir(argv[1]);
	cwd = getcwd(NULL, 0);
	printf("open dir 후 경로 : %s\n", cwd);

	puts("-------chdir 한 후 경로--------");
	chdir(argv[1]);
	cwd = getcwd(NULL, 0);
	printf("chdir 후  경로 : %s\n", cwd);

	return 0;
}

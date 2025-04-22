#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	char *cwd;

	cwd = getcwd(NULL, 0);
	printf("Current : %s\n", cwd);

	chdir("hanbit");
	cwd = getcwd(NULL, 0);
	printf("Next : %s\n", cwd);

	chdir("..");
	cwd = getcwd(NULL, 0);
	printf("Current : %s\n", cwd);

	return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){

	mkdir("dir1", 0755);
	mkdir("dir2", 0755);

	rmdir("dir1");
	rename("dir2", "hanbit");
	
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
	DIR *dp;
	struct dirent *dent;

	if(argc==1) {
		dp = opendir(".");
		while((dent = readdir(dp))) {
			if(strcmp(dent->d_name, ".")==0 || strcmp(dent->d_name, "..")==0) {
				continue;
			}
			printf("%s  ", dent->d_name);
		}
		printf("\n");
		closedir(dp);
		return 0;
	} else {
		if(strcmp(argv[1], "-l")==0) {
		
		} else if (strcmp(argv[1], "-R")==0) {
		
		} else {
		dp = opendir(argv[1]);
		while((dent = readdir(dp))) {
                        if(strcmp(dent->d_name, ".")==0 || strcmp(dent->d_name, "..")==0) {
                                continue;
                        }
                        printf("%s  ", dent->d_name);
                }
                printf("\n");
                closedir(dp);
                return 0;
		}
	}
}

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void LS1(DIR *dp, struct dirent *dent){
	dp = opendir(".");
                while((dent = readdir(dp))) {
                        if(strcmp(dent->d_name, ".")==0 || strcmp(dent->d_name, "..")==0) {
                                continue;
                        }
                        printf("%s  ", dent->d_name);
                }
                printf("\n");
                closedir(dp);;
}
void LS2(DIR *dp, struct dirent *dent, char*argv1){
	dp = opendir(argv1);
                while((dent = readdir(dp))) {
                        if(strcmp(dent->d_name, ".")==0 || strcmp(dent->d_name, "..")==0) {
                                continue;
                        }
                        printf("%s  ", dent->d_name);
                }
                printf("\n");
		closedir(dp);
}
void LS3(DIR *dp, struct dirent *dent){
	struct stat statbuf;
	int totalCount = 0;
	dp = opendir(".");
	while((dent = readdir(dp))) {
                if(strcmp(dent->d_name, ".")==0 || strcmp(dent->d_name, "..")==0) {
                        continue;
                }
		stat(dent->d_name, &statbuf);
		totalCount+=(int)statbuf.st_blocks;
        }
	printf("total %d\n", totalCount/2);
	dp = opendir(".");
	while((dent = readdir(dp))) {
                if(strcmp(dent->d_name, ".")==0 || strcmp(dent->d_name, "..")==0) {
                        continue;
                }
                stat(dent->d_name, &statbuf);

		mode_t mode =  statbuf.st_mode;

		struct passwd *pass;
		pass = getpwuid(statbuf.st_uid);
		struct group *group;
		group = getgrgid(statbuf.st_gid);
		
		struct tm *time = localtime(&statbuf.st_mtime);
		char temp[11] = "----------";
		if (S_ISREG(mode)) temp[0] = '-';
		else if (S_ISDIR(mode)) temp[0] = 'd';
		else if (S_ISLNK(mode)) temp[0] = 'l';
		else if (S_ISCHR(mode)) temp[0] = 'c';
		else if (S_ISBLK(mode)) temp[0] = 'b';
		else if (S_ISFIFO(mode)) temp[0] = 'p';
		else if (S_ISSOCK(mode)) temp[0] = 's';

		if (mode & S_IRUSR) temp[1] = 'r';
		if (mode & S_IWUSR) temp[2] = 'w';
		if (mode & S_IXUSR) temp[3] = 'x';

		if (mode & S_IRGRP) temp[4] = 'r';
		if (mode & S_IWGRP) temp[5] = 'w';
		if (mode & S_IXGRP) temp[6] = 'x';

		if (mode & S_IROTH) temp[7] = 'r';
		if (mode & S_IWOTH) temp[8] = 'w';
		if (mode & S_IXOTH) temp[9] = 'x';

		char *months[] = {
		 "Jan", "Feb", "Mar", "Apr", "May", "Jun",
       		 "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
   		};
		
		temp[10] = '\0';
		printf("%s ", temp);
                printf("%d ", (unsigned int)statbuf.st_nlink);
		printf("%s %s ", pass->pw_name, group->gr_name);
		printf("%5d ", (int)statbuf.st_size);
		printf("%s %2d %02d:%02d ", months[time->tm_mon], time->tm_mday, time->tm_hour, time->tm_min);
                printf("%s\n", dent->d_name);
        }
        closedir(dp);;
}
void LS4(DIR *dp, struct dirent *dent, char* argv) {
	struct stat statbuf;
	char *dirs[1000];
	int dirCount = 0;
	dp = opendir(argv);
	printf(".");
	if(strcmp(argv, ".")!=0) {
		printf("/%s", argv);
	}
	printf(":\n");
                while((dent = readdir(dp))) {
                        if(strcmp(dent->d_name, ".")==0 || strcmp(dent->d_name, "..")==0) {
                                continue;
                        }
			stat(dent->d_name, &statbuf);
               		mode_t mode =  statbuf.st_mode;
			if(S_ISDIR(mode)) {
				dirs[dirCount] = dent->d_name;
				dirCount++;
			}
                        printf("%s  ", dent->d_name);
                }
		for(int k=0; k<dirCount; k++) {
			printf("\n\n");
			LS4(dp, dent, dirs[k]);
		}
                closedir(dp);;
}
int main(int argc, char *argv[]) {
	DIR *dp;
	struct dirent *dent;

	if(argc==1) {
		LS1(dp, dent);
	} else {
		if(strcmp(argv[1], "-l")==0) {
			LS3(dp, dent);
		} else if (strcmp(argv[1], "-R")==0) {
			LS4(dp, dent, ".");
		} else {
			LS2(dp, dent, argv[1]);
		}
	}
}

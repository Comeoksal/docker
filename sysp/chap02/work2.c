#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
	DIR *dp;
	struct dirent *dent;
	
	dp = opendir("."); //디렉터리 포인터 반환
	
	while((dent = readdir(dp))) { //dirent 구조체 반환
		printf("Name : %s", dent->d_name);
		printf("Inode : %d\n", (int)dent->d_ino); //★
	}
	
	closedir(dp); //성공시 0, 실패시 -1 반환
}

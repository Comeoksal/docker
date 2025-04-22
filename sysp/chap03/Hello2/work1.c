#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	struct stat statbuf;
	//stat 함수로 검색한 inode 정보는 stat 구조체에 저장되어 리턴
	stat("linux.txt", &statbuf); //성공시 0, 실패시 -1 리턴
	
	//inode 번호
	printf("Inode = %d\n", (int)statbuf.st_ino);
	//파일 종류 및 접근 권한
	printf("Mode = %o\n", (unsigned int)statbuf.st_mode);
	//하드 링크 개수
	printf("Nlink = %o\n", (unsigned int)statbuf.st_nlink);
	//파일 소유자의 UID
	printf("UID = %d\n", (int)statbuf.st_uid);
	//파일 소유 그룹의 GID
	printf("GID = %d\n", (int)statbuf.st_gid);
	//파일 내용을 입출력할 때 사용하는 버퍼 크기
	printf("Blksize = %d\n", (int)statbuf.st_blksize);
	//파일에 할당된 파일 시스템 블록 수 (블록의 크기는 512바이트)
	printf("Blocks = %d\n", (int)statbuf.st_blocks);
	
	printf("** timespec Style\n");
	//마지막으로 읽거나 실행한 시각
	printf("Atime = %d\n", (int)statbuf.st_atim.tv_sec);
	//마지막으로 변경(쓰기)한 시각
	printf("Btime = %d\n", (int)statbuf.st_mtim.tv_sec);
	//마지막으로 inode 내용을 변경한 시각
	printf("Ctime = %d\n", (int)statbuf.st_ctim.tv_sec);
}

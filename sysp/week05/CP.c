#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if(argc<3){
		printf("usage : ./CP a.txt b.txt\n");
		exit(1);
	}
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

	if(input == NULL || output == NULL) {
		printf("파일 열기 실패\n");
		return 1;
	}

	char buffer[1024];
	size_t bytesRead;

	while((bytesRead = fread(buffer, 2, sizeof(buffer), input)) > 0) {
		fwrite(buffer, 1, bytesRead, output);
	}

	fclose(input);
	fclose(output);

	return 0;
}


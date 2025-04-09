#include <stdio.h>
#include <stdlib.h>

int main(){
	char* str = (char *)malloc(sizeof(char) * 5);
	str[0] = 'a';
	str[1] = 'b';
	str[3] = 'c';
	int* ip = (int *)calloc(5, sizeof(int));
	str = (char*)realloc(str, sizeof(char) * 10);
	str[5] = 'd';
	str[6] = 'e';
	str[7] = 'f';
	int i;
	for(i=0; i<10; i++){
		printf("%c\n", str[i]);
	}
	for(i=0; i<5; i++){
		printf("%d ", *(ip + i));
	}
	free(str);
	free(ip);

	return 0;
}

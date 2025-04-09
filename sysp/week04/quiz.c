#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int count = 0;
	char str[1024];
	char *list[1000];
	while(1) {
		printf("enter a string : ");
		scanf("%s", str);
		if(strcmp(str, "\n")==0) {
			break;
		}
		list[count++] = strdup(str);
	}
	printf("Your input is ");
	int i;
	for(int i=0; i<count; i++) {
		printf("%s ", list[i]);
	}
	printf("\n");
	return 0;
}


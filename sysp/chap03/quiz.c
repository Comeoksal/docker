#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char buf[BUFSIZ];
	char *str = malloc(1);
	str[0] = '\0';
	int len;

	while(1) {
		printf("enter a string : ");
		fgets(buf, sizeof(buf), stdin);
		
		len = strlen(buf);

		if(buf[0]=='\n' && len==1) {
			printf("%s", str);
			break;
		}
		str = realloc(str, strlen(str) + len + 1);
		strcat(str, buf);
	}
	free(str);
	return 0;
}

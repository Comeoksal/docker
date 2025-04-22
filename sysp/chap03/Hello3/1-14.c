#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int i = atoi(argv[1]);
	int k = atoi(argv[2]);
	int result = 0;
	for(; i<=k; i++) {
		result+=i;
	}
	printf("%d", result);
	return 0;
}


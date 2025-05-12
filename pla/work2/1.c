#include <stdio.h>

int f(){
	float b = 3.1;
	int c = b;
	printf("%f\n", (float)c);
	return b;
}
int main(){
	int a = f();
	printf("%d\n", a);

	return 0;
}


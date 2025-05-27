#include <stdio.h>
#include <stdlib.h>

int f1(int a) {
	return a+1;
}

int main() {
	int(*f)(int b);

	f= f1;
	printf("%p - %p\n", f, f1);

	return 0;
}

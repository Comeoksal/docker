#include <stdio.h>

int x;

int callByReference(int *a){
	printf("Variable Address : %p\n", (void *)a);
	*a *= 3;
	printf("x in callByReference = %d\n", x);
	return *a;
}
int callByValueResult(int a){
	printf("Variable Address : %p\n", (void *)&a);
	a *=3;
	printf("x in callByValueResult= %d\n", x);
	
	x=a;
	return a;
}

int main(){
	int temp;

	printf("x address : %p\n\n", (void *)&x);
	x=3;
	temp = callByReference(&x);
	printf("x : %d\n", x);
	printf("temp : %d\n\n", temp);
	
	x=3;
	temp = callByValueResult(x);
	printf("x : %d\n", x);
	printf("temp : %d\n", temp);

	return 0;
}

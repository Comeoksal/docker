#include <stdio.h>

void f1(double x);
int main(){
	int x;

	printf("input : ");
	scanf("%d", &x);	

	f1(10/x);
	return 0;
}
void f1(double x){
	printf("Hello\n");
}

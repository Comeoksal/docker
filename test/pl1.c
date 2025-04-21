#include <stdio.h>

int a = 5;

int f(){
        a = a+3;
        return a;
}
int main() {
	a = f() + a;
	printf("%d\n", a);
}

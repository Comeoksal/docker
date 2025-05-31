#include <stdio.h>

int main(){
	int j=3;
	int i=0;

start:
	if(i>=3) goto end;
	
	if(j+2==2){
		j--;
	} else if(j+2 == 0){
		j+=2;
	} else if(j+2!=3){
		j=0;
	}

	if(j>0) {
		printf("out j : %d\n", j);
		goto end;
	}
	
	j=3-i;
	printf("repeat j : %d\n", j);
	i++;
	goto start;

end:
}

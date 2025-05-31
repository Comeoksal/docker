#include <stdio.h>

int main(){
	int j=-3;
	int i;
	for(i=0; i<3; i++){
		switch(j+2){
			case 3:
			case 2: j--; break;
			case 0: j+=2; break;
			default: j=0;
		}
		if(j>0) { 
			printf("out j : %d\n", j); 
			break;
		}
		j=3-i;
		printf("repeat j : %d\n", j);
	}
}

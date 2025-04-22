#include <stdlib.h>
#include <stdio.h>

int main() {
	FILE *rfp, *wfp;
	char buf[BUFSIZ];
	int nbyte;
	
	if((rfp = fopen("linux.txt", "r")) == NULL) {
		perror("fopen1");
		exit(1);
	}
	
	if((wfp = fopen("linux.out", "a")) == NULL) {
		perror("fopen2");
		exit(1);
	}
	
	if((nbyte = fread(buf, 1, sizeof(buf), rfp)) > 0) {
		fwrite(buf, 1, nbyte, wfp);
	}
	
	fclose(rfp);
	fclose(wfp);
}

#define PLUS_CODE '+'
#define MINUS_CODE '-'
#define AST_CODE '*'
#define SLASH_CODE '/'
#define ID_CODE 256
#define NUM_CODE 257
#define LEFT_PAREN_CODE '('
#define RIGHT_PAREN_CODE ')'
#include <stdio.h>
#include <stdlib.h>

int nextToken, idx = 0;
char input[1024];
extern void perror(const char*msg){
	printf("%s", msg);
}
void lex();
void expr();
void term();
void factor();

int main(){
        printf("연산 입력 : ");
        scanf("%s", input);
	lex();
        expr();
	if(nextToken != -1){
		printf("parsing error!!!\n");
	} else {
		printf("parsing success\n");
	}
        return 0;
}
void lex(){
	char c = input[idx];
	
	if (c == '+') nextToken = PLUS_CODE;
    	else if (c == '-') nextToken = MINUS_CODE;
    	else if (c == '*') nextToken = AST_CODE;
    	else if (c == '/') nextToken = SLASH_CODE;
    	else if (c == '(') nextToken = LEFT_PAREN_CODE;
    	else if (c == ')') nextToken = RIGHT_PAREN_CODE;
    	else if (c >= '0' && c <= '9') nextToken = NUM_CODE;
    	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) nextToken = ID_CODE;
    	else if (c == '\0') nextToken = -1;
    	else {perror("parsing error in lex\n"); exit(1);}
	idx++;
}
void expr(){
	term();
	while(nextToken == PLUS_CODE || nextToken == MINUS_CODE) {
		lex();
		term();
	}
}
void term(){
	factor();
	while(nextToken == AST_CODE || nextToken == SLASH_CODE) {
		lex();
		factor();
	}
}
void factor(){
	if(nextToken == ID_CODE){
		lex();
	} else if(nextToken == NUM_CODE){
		lex();
	} else if(nextToken == LEFT_PAREN_CODE){
		lex();
		expr();
		if(nextToken == RIGHT_PAREN_CODE){
			lex();
		} else {
			perror("no more token in factor\n");
			exit(1);
		}
	} else {
		perror("factor is not work\n");
		exit(1);
	}
}

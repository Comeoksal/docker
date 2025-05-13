#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
void read_and_print();
int main(){
 int fd, status;
 char buf[BUFSIZ];
 pid_t pid;
 pid = fork();
 if(pid==0){
 printf("Input an expression : ");
 if(fgets(buf, sizeof(buf), stdin) == NULL){
 perror("input fail");
 exit(1);
 }
 fd = open("input.txt", O_WRONLY | O_CREAT | O_TRUNC, 
0644);
 if(fd==-1){
 perror("open fail");
 exit(1);
 }
 if(write(fd, buf, strlen(buf)) != strlen(buf)){
 perror("write fail");
 exit(1);
 }
 } else if (pid > 0){
 while(wait(&status) !=pid) continue;
 read_and_print();
 exit(0);
 } else {
 perror("fork fail");
 exit(1);
 }
 return 0;
}
void read_and_print(){
 //1. open input.txt and read to buf
 int fd, nbyte, len;
 char buf[BUFSIZ];
 fd = open("input.txt", O_RDONLY);
 if(fd==-1){
 perror("open fail");
 exit(1);
 }
 nbyte = read(fd, buf, sizeof(buf));
 buf[nbyte] = 0;
 len = strlen(buf);
 //2. store numbers and operators individually
 int i, numCount = 0, numbers[1024];
 char opCount = 0, operators[1024], buf2[BUFSIZ], *token;
 strcpy(buf2, buf);
 token = strtok(buf, "+-*/");
 while(token!=NULL){
 numbers[numCount++] = atoi(token);
 token = strtok(NULL, "+-*/");
 }
 for(i=0; i<len; i++){ if(strchr("+-*/", buf2[i])){
 operators[opCount++] = buf2[i];
 }
 }
 //3. calculate * and / operators first
 int newNumCount = 0, numForCalculate[1024];
 char newOpCount = 0, opForCalculate[1024];
 numForCalculate[newNumCount++] = numbers[0];
 for(i=0; i<opCount; i++){
 int num = numbers[i+1];
 if(operators[i] == '*'){
 numForCalculate[newNumCount - 1] *=num;
 } else if(operators[i] =='/'){
 numForCalculate[newNumCount -1] /=num;
 } else {
 opForCalculate[newOpCount++] = operators[i];
 numForCalculate[newNumCount++] = num;
 }
 }
 //4. calculate + and - operators and printf the result
 int result = numForCalculate[0];
 for(i=0; i<newOpCount; i++){
 if(opForCalculate[i] == '+'){
 result +=numForCalculate[i+1];
 } else if (opForCalculate[i] == '-'){
 result -=numForCalculate[i+1];
 }
 }
 printf("calculate result : %d\n", result);
}

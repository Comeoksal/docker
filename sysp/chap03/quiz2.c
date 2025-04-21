#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

int main() {
   char buf[MAXLINE];
   int count = 0, n = 10;
   char** arr = (char**)malloc(sizeof(char*) * n);
   while (1) {
      fgets(buf, MAXLINE, stdin);
      if (buf[0] == '\n' && buf[1] == '\0') {
         break;
      }

      if (count >= 10) {
         n *= 2;
         arr = (char**)realloc(arr, sizeof(char*) * n);
      }

      arr[count] = (char*)malloc(strlen(buf) + 1);
      strcpy(arr[count], buf);
      count++;

   }
   for (int i = 0; i < count; i++) {
      printf("%s", arr[i]);
      free(arr[i]);
   }
   free(arr);
   return 0;
}

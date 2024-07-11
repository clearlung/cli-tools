#include <stdio.h>
#define MAXLINE 100
/*These are my goals:
Copy file to temporary file
Find line with matching string
Delete line with matching string
Overwrite original file with temporary file*
exit*/

const char *path="/home/clear/todo/todo.txt";
char pattern[] = "apples";

int getLine(char s[], int lim, FILE *fptr) {
  int c, i;
  i = 0;

  while(--lim > 0 && (c=getc(fptr)) != EOF && c!= '\n')
    s[i++] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';
  return i;
}

int strindex(char s[], char t[]) {
  int i, j, k;

  for (i = 0; s[i] != '\0'; i++) {
    for(j=i, k=0; t[k] != '\0' && s[j]==t[k]; j++, k++)
      ;
    if (k > 0 && t[k] == '\0')
      return i;
  }
  return -1;
}

int deleteLine(FILE *fptr) {
  char line[MAXLINE];
  int found = 0;
  
  while (getLine(line, MAXLINE, fptr) > 0)
    if (strindex(line, pattern) >= 0) {
      printf("%s", line);
      found++;
    }
  return found;
}

int main(void) {
  FILE *fptr;  
  fptr = fopen(path, "r");
  deleteLine(fptr);
}

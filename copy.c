#include <stdio.h>

const char *path="/home/clear/programming/cli.tools/todo.txt";

void copy(char *array) {
  FILE *fptr;
  fptr = fopen(path, "r");
  int i, c;
  i = 0;
  
  while ((c = getc(fptr)) != EOF) {
    array[i++] = c;
  }
  array[i] = '\0';

  fclose(fptr);
}

void main(void) {
  char myArray[1000];

  copy(myArray);
  
  int i=0;
  while (myArray[i] != '\0')
    putchar(myArray[i++]);
}

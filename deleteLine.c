#include <stdio.h>
const char *path="/home/clear/todo/todo.txt";
int lineNumber = 2;

void deleteLine(FILE *fptr1, FILE *fptr2, int lineNumber) {
  int counter = 1;
  char ch;
  fptr1 = fopen(path, "r");
  fptr2 = fopen("todo.new", "w");
  while(ch != EOF) {
    ch = getc(fptr1);
    if(counter != lineNumber && ch != EOF) {
      putc(ch, fptr2);
    }
    if(ch == '\n') {
      counter++;
    }
  }
  fclose(fptr1);
  fclose(fptr2);
  remove(path);
  rename("todo.new", path);
}

int main(void) {
  FILE *fptr1, *fptr2;
  deleteLine(fptr1, fptr2, lineNumber);
}

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

char sentence[] = "apples\noranges\npears\ntomatoes";
char searchTerm[] = "pears";

int sentenceLength = sizeof(sentence) / sizeof(sentence[0]);
int searchTermLength = sizeof(searchTerm) / sizeof(searchTerm[0]);

int urine2(void) {
  int offset;
  int lineNumber = 1;
  for(int i=0;i<sentenceLength;i++) {
    if(sentence[i] == '\n')
      lineNumber++;
    if(sentence[i] == searchTerm[0]) {
      offset = i;
      while(sentence[i] == searchTerm[i - offset] && sentence[i] != '\0') {
        i++;
      }
      if(i-offset == searchTermLength -1)
        return lineNumber;
    }
  }
  return -1;
}

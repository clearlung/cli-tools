#include <stdio.h>
const char *path="/home/clear/todo/todo.txt";
char *searchTerm="pears";

int characterCount(FILE *fptr) { //returns number of characters in file
  fptr = fopen(path, "r");
  char c;
  int counter = 0;

  for(c=getc(fptr); c != EOF; c=getc(fptr)) {
    counter += 1;
  }
  fclose(fptr);
  return counter;
}

char * copy(FILE *fptr, char *sentence, int max) { //copy file content to array
  fptr = fopen(path, "r");
  char c;

  if(fptr != NULL) {
    for(int i=0;i<max;i++) {
      c = getc(fptr); 
      sentence[i] = c;
    }
  }
  fclose(fptr);
  return sentence;
}

int indexLine(int sentenceLength, int searchTermLength, char * sentence) { //returns lineNumber of string
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
      if(i-offset == searchTermLength - 1)
        return lineNumber;
    }
  }
  return -1;
}

void deleteLine(FILE *fptr, FILE *fptr2, int lineNumber) { //deletes line from file
  int counter = 1;
  char ch;
  fptr = fopen(path, "r");
  fptr2 = fopen("todo.new", "w");
  while(ch != EOF) {
    ch = getc(fptr);
    if(counter != lineNumber && ch != EOF) {
      putc(ch, fptr2);
    }
    if(ch == '\n') {
      counter++;
    }
  }
  fclose(fptr);
  fclose(fptr2);
  remove(path);
  rename("todo.new", path);
}

int main(void) {
  FILE *fptr, *fptr2;
  int max = characterCount(fptr);
  int searchTermLength = sizeof(searchTerm) / sizeof(searchTerm[0]);
  int sentenceLength = characterCount(fptr);
  char sentence[max];

  printf("Sentence Length: %d\nSearchTermLength: %d\n", sentenceLength, searchTermLength);

  copy(fptr, sentence, max);
  printf("%d", indexLine(sentenceLength, searchTermLength, sentence));
  printf("%c", sentence[max]);
}

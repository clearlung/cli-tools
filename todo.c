#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

const char *path="/home/clear/todo/todo.txt";

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

int indexLine(int sentenceLength, int searchTermLength, char *searchTerm, char *sentence) { //returns lineNumber of string
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
      if(i-offset == searchTermLength - 1) {
        return lineNumber;
      }
    }
  }
  return -1;
}

void deleteLine(FILE *fptr, FILE *fptr2, int lineNumber) { //deletes line from file
  char ch;
  int counter = 1;
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

void read(FILE *fptr, int fileLength) {
	fptr = fopen(path, "r");
  char readFile;
  if (fptr != NULL) {
    char readFile[fileLength];
    while(fgets(readFile, fileLength, fptr)) {
      printf("%s", readFile);
    }
  }
  fclose(fptr);
}

void appendLine(FILE *fptr, char *task) {
  fptr = fopen(path, "a");
  fprintf(fptr, "%s\n", task);
  fclose(fptr);
}

int main(int argc, char **argv) {
  FILE *fptr, *fptr2;
  int optionVal = 0;
  int lineNumber;
  int max = characterCount(fptr);
  char fileContents[max];    
  int searchTermLength;

  while(optionVal = getopt(argc, argv, "rn")) {
  	switch(optionVal) {
  		case 'r':
        copy(fptr, fileContents, max);
        if(argc == 3) {
          searchTermLength = strlen(argv[2]) + 1; 
          lineNumber = indexLine(max, searchTermLength, argv[2], fileContents);
        }
        else {
          char task[30];
          printf("name of task: ");
          scanf("%s", task);
          searchTermLength = strlen(task) + 1;
          lineNumber = indexLine(max, searchTermLength, task, fileContents); 
        }
        deleteLine(fptr, fptr2, lineNumber);
  	    break;
  	  case 'n':
        if(argc == 3)
          appendLine(fptr, argv[2]);
        else {
          char task[30];
          printf("name of task: ");
          fgets(task, sizeof(task), stdin);
          appendLine(fptr, task);
        }
        break;
  	  default:
        read(fptr, max);
  			return 0;
  	}
  }
  return 0;
}

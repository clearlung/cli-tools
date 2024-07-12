#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

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
      if(i-offset == searchTermLength - 1)
        return lineNumber;
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


void read(FILE *fptr) {
	fptr = fopen(path, "r");
  char readFile;
  if (fptr != NULL) {
    char readFile[100];
    while(fgets(readFile, 100, fptr)) {
      printf("%s", readFile);
    }
  }
  fclose(fptr);
}

void appendLine(FILE *fptr, int argc, char **argv) {
  fptr = fopen(path, "a");
  if(argc == 3) {
    fprintf(fptr, "%s\n", argv[2]);
    fclose(fptr);
  } else if(argc == 2) {
    char task[30];
    printf("name of task: ");
    fgets(task, sizeof(task), stdin);
    fprintf(fptr, "%s\n", task);
    fclose(fptr);
  }
}

int main(int argc, char **argv) {
  FILE *fptr, *fptr2;
  int optionVal = 0;
  int lineNumber;
  int max = characterCount(fptr);
  char sentence[max];

  while(optionVal = getopt(argc, argv, "rn")) {
  	switch(optionVal) {
  		case 'r':
        int searchTermLength;
        int sentenceLength = characterCount(fptr);
        copy(fptr, sentence, max);
        searchTermLength = sizeof(argv[2]) / sizeof(argv[2][0]); 
        int lineNumber = indexLine(sentenceLength, searchTermLength, argv[2], sentence);
        deleteLine(fptr, fptr2, lineNumber);
  	    break;
  	  case 'n':
        appendLine(fptr, argc, argv);
        break;
  	  default:
        read(fptr);
  			return 0;
  	}
  }
  return 0;
}

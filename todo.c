#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#define MAX 1000

const char *path="/home/clear/programming/cli.tools/todo.txt";

void copy(FILE *fptr, char *array);
int indexLine(int searchTermLength, char *searchTerm, char *array);
void deleteLine(FILE *fptr1, int lineNumber);
void read(FILE *fptr);
void appendLine(FILE *fptr, char *taask);

int main(int argc, char **argv) {
  FILE *fptr;
  int optionVal = 0;
  int lineNumber;
  char fileContents[MAX];    
  int searchTermLength;

  while(optionVal = getopt(argc, argv, "ra")) {
  	switch(optionVal) {
  	  case 'r':
        copy(fptr, fileContents);
        if(argc == 3) {
          searchTermLength = strlen(argv[2]) + 1; 
          lineNumber = indexLine(searchTermLength, argv[2], fileContents);
        }
        else {
          char task[30];
          printf("name of task: ");
          scanf("%s", task);
          searchTermLength = strlen(task) + 1;
          lineNumber = indexLine(searchTermLength, task, fileContents); 
        }
        printf("test");
        deleteLine(fptr, lineNumber);
  	    break;
  	  case 'a':
        if(argc == 3) {
          appendLine(fptr, argv[2]);
        }
        else {
          char task[30];
          printf("name of task: ");
          fgets(task, sizeof(task), stdin); //fgets includes the '\n' so I should make my own function to replace it.
          appendLine(fptr, task);
        }
        break;
  	  default:
        read(fptr);
        return 0;
  	}
  }
  return 0;
}

void copy(FILE *fptr, char *array) { //copy file content to array
  fptr = fopen(path, "r+");
  int i, c;

  if (fptr == NULL) {
    printf("File does not exist.\n");
    return;
  }

  i=0;
  while ((c = getc(fptr)) != EOF) { // this loop dosen't end for some reason? never had a problem with this before.
    printf("char c: %c\n", c);
    array[i++] = c; //this line is what's broken. I don't see anything wrong with this though. 
  }
  array[i] = '\0';
  printf("test");
  fclose(fptr);
}


int indexLine(int searchTermLength, char *searchTerm, char *array) { //returns lineNumber of string
  int offset, lineNumber, i;
  i = 0; lineNumber = 1;

  while (array[i] != '\0') {
    if (array[i] == '\n')
      lineNumber++;
    if (array[i] == searchTerm[0]) {
      offset = i;
      while (array[i] == searchTerm[i - offset] && array[i] != '\0') {
        i++;
      }
      if (i-offset == searchTermLength - 1) {
        return lineNumber;
      }
    }
  }
  return -1;
}

void deleteLine(FILE *fptr1, int lineNumber) { //deletes line from file
  FILE *fptr2;
  int c, counter;
  counter = 1;
  fptr1 = fopen(path, "r");
  fptr2 = fopen("todo.new", "w");
  
  if (fptr1 == NULL) {
    printf("File does not exist.\n");
  }

  while ((c = getc(fptr1)) != EOF) {
    putchar(c);
    if (counter != lineNumber) {
      putc(c, fptr2);
    }
    if (c == '\n') {
      counter++;
    }
  }

  fclose(fptr1);
  fclose(fptr2);
  remove(path);
  rename("todo.new", path);
}

void read(FILE *fptr) {
  char array;
  int c;

  fptr = fopen(path, "r");

  if (fptr == NULL) {
    printf("File does not exist.\n");
    return;
  }
  
  while ((c = getc(fptr)) != EOF)
    putchar(c);
  fclose(fptr);
}

void appendLine(FILE *fptr, char *task) {
  fptr = fopen(path, "a");
  fprintf(fptr, "%s\n", task);  
  fclose(fptr);
}

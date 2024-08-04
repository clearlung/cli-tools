#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#define MAX 1000

const char *path="/home/clear/programming/cli.tools/todo.txt";

void copy(FILE *fptr, char *array);
int indexLine(char *searchTerm, int searchTermLength, char *array);
void deleteLine(FILE *fptr1, int lineNumber);
void read(FILE *fptr);
void appendLine(FILE *fptr, char *task, int mode);
void returnTask(char *array);

int main(int argc, char **argv) {
  FILE *fptr;
  int optionVal = 0;
  int lineNumber;
  char fileContents[MAX];    
  int searchTermLength;

  while (optionVal = getopt(argc, argv, "ar")) {
  	switch(optionVal) {
  	  case 'r':
        copy(fptr, fileContents);
        if (argc == 3) {
          searchTermLength = strlen(argv[2]) + 1; 
          lineNumber = indexLine(argv[2], searchTermLength, fileContents);
        }
        else {
          char task[30];
          printf("name of task: ");
          scanf("%s", task);
          searchTermLength = strlen(task) + 1;
          lineNumber = indexLine(task, searchTermLength, fileContents); 
        }
        deleteLine(fptr, lineNumber);
  	    break;
  	  case 'a':
        if(argc == 3) {
          appendLine(fptr, argv[2], 1);
        }
        else {
          char task[MAX];
          printf("name of task: ");
          returnTask(task);
          appendLine(fptr, task, 2);
        }
        break;
  	  default:
        read(fptr);
        return 0;
  	}
  }
  return 0;
}

void returnTask(char *array) {
  int i, c;
  i=0;

  while ((c = getchar()) != EOF) {
    if (c != '\n') {
      array[i++] = c;
    }
    else if (c == '\n') {
      array[i] = '\0';
      break;
    }
  }
}

void copy(FILE *fptr, char *array) { //copy file content to array
  fptr = fopen(path, "r");
  int i, c;

  i=0;
  while ((c = fgetc(fptr)) != EOF) {
    array[i++] = c;
  }
  array[i] = '\0';
  
  fclose(fptr);
}


int indexLine(char *searchTerm, int searchTermLength, char *array) { //returns lineNumber of string
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
    i++;
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

void appendLine(FILE *fptr, char *task, int mode) {
  char newLine = '\n';
  fptr = fopen(path, "a");
  switch (mode) {
    case 1:
      fprintf(fptr, "%s", task);  
      break;
    case 2:
      for (int i=0; task[i] != '\0'; i++)
        putc(task[i], fptr);        
      break;
    default:
      fclose(fptr);
      return;
  }
  putc(newLine, fptr);
  fclose(fptr);
}

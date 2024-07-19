//program instructions: copy file contents to a multidimensional array

#include <stdio.h>
#include <stdlib.h>
#define maxLength 100

const char *path="/home/clear/C/replace/poem.txt";

int returnLines() { // return number of lines
  FILE *fptr = NULL;
  fptr = fopen(path, "r");
  char c;
  int i = 0;
  
  while ((c = getc(fptr)) != EOF) {
    if (c=='\n')
      i++;
  }
  fclose(fptr);
  return i;
}

int returnLineLength(int line) { // return characters in line
  FILE *fptr = NULL;
  fptr = fopen(path, "r");
  if (fptr == NULL) {
    printf("fail\n");
    exit(1);
  }

  char c;
  int lineCounter = 0;
  int i=0; 

  while ((c = getc(fptr)) != EOF) {
    if (lineCounter <= line && c == '\n') {
      lineCounter++;
    }
    else if (lineCounter == line) {
      i++;
    }
    else if (lineCounter > line) {
      break;
    }
  }
  fclose(fptr);
  return i;
}

void lineToArray(void) { // copy line to array
  FILE *fptr;
  fptr = fopen(path, "r");
  if (fptr == NULL) {
    printf("fail");
    exit(1);
  }

  int maxLines = returnLines(fptr);
  char copy[maxLines][maxLength];
  char c;
  int currentLine = 0;
  int currentChar = 0;
  int lineLength = returnLineLength(currentLine);

  while ((c = getc(fptr)) != EOF) {
    if (c == '\n') {
      copy[currentLine][currentChar] = '\0';
      currentLine++;
      currentChar = 0;
      if (currentLine < maxLines) {
        lineLength = returnLineLength(currentLine);
      }
    }
    if (currentChar <= lineLength) {
      copy[currentLine][currentChar] = c;
      currentChar++;
    }
  }
  fclose(fptr);
  copy[currentLine][currentChar] = '\0';
  for (int i = 0; i < maxLines; i++) {
    printf("%s", copy[i]);
  }
}

int main(void) {
  lineToArray();
  return 0;
}

//task 3: return the value of lineToArray to main;

/*const char *path2="/home/clear/C/replace/poem.txt.bak";

char searchTerm[] = "berries";
int searchTermLength = sizeof(searchTerm)/sizeof(searchTerm[0]);

void copy(FILE *fptr1, FILE *fptr2) { // create copy of file
  char c;
  while((c = getc(fptr1)) != EOF) {
    putc(c, fptr2);
  }
  fclose(fptr1);
  fclose(fptr2);
}
*/


/*int returnLineNumber(void) {
  int offset;
  int lineNumber = 1;
  char ch;
  FILE *fptr;
  fptr = fopen(path, "r");

  while(ch != EOF) {
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
    return -1;
  }
}*/



/*
int countMatches(char *text, char *search, int max) { //return number of matching strings
  int offset, i, matches;
  matches = 0;
  for (i=0;i<MAX_MATCHES;i++) { //inefficient check but it works for now
    for (i=0;i<max;i++) {
      if (text[i] == search[0]) {
        offset = i;
        while (text[i] == search[i - offset] && text[i] != '\0') {
          i++;
        }
        if (i - offset == searchTermLength )
          matches++;
      }
    }
  }
  return matches;
}

int findOffset(char *text, char *search, int max, int matchNumber) { //return offset of each matching string
  int offset, i;
  for (i=0;i<max;i++) {
    if (text[i] == search[0]) {
      offset = i;
      while (text[i] == search[i - offset] && text[i] != '\0') {
        i++;
      }
      if (i - offset == searchTermLength - 1)
        offset++;
    }
  }
  return offset;
}
*/

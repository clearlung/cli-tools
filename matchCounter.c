//program instructions: copy a given line to an array

#include <stdio.h>
#define maxLength 100

const char *path="/home/clear/C/replace/poem.txt";

int returnLines() { // return number of lines
  FILE *fptr;
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
  FILE *fptr;
  fptr = fopen(path, "r");
  char c;
  int lineCounter = 1;
  int i=0;
  
  if (fptr == NULL) {
    printf("fail\n");
  }

  while ((c = getc(fptr)) != EOF) {
    if (lineCounter <= line && c == '\n') {
      lineCounter++;
    }
    else if (lineCounter == line) {
      i++;
    }
    else {
      fclose(fptr);
      return i;
    }
  }
  fclose(fptr);
  return -1;
}

void lineToArray(int line) { // copy line to array
  FILE *fptr;
  fptr = fopen(path, "r");

  int maxLines = returnLines(fptr);
  char c;
  char copy[maxLines][maxLength];
  int currentLine = 1;
  int currentChar = 0;
  int lineLength = returnLineLength(currentLine);

  if (fptr == NULL) {
    printf("fail");
    return;
  }
  
  while ((c = getc(fptr)) != EOF) {
    if (c == '\n') {
      currentLine++;
      currentChar = 0;
    }
    else if (currentLine == line) { 
      if (currentChar <= lineLength + 1) {
        copy[currentLine][currentChar] = c;
        currentChar++;
      }
    }
    else if (currentLine > line) {
      break;
    }
  }
  fclose(fptr);
}

int main(void) {
  lineToArray(3); 
  return 0;
}

//task 2 copy file contents to a multidimensional array

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

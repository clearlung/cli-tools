//program instructions: replace all occurences of tab characters in a file with 2 spaces
#include <stdio.h>
#include <stdbool.h>

const char *path="/home/clear/replace/poem.txt";
const char *path2="/home/clear/replace/poem.txt.bak";

char searchTerm[] = "Blueberries";
char replaceTerm[] = "pineapple";

int searchTermLength = sizeof(searchTerm) / sizeof(searchTerm[0]);
int replaceTermLength = sizeof(replaceTerm) / sizeof(replaceTerm[0]);

int characterCount(FILE *fptr) { //returns number of characters in file 
  fptr = fopen(path, "r");
  if (fptr != NULL) {
    char c;
    int counter = 0;

    for(c=getc(fptr); c != EOF; c=getc(fptr)) {
      counter += 1;
    }
    fclose(fptr);
    return counter;
  }
  return -1;
}

char * copy(FILE *fptr, char *text, int max) { //copy file content to array
  fptr = fopen(path, "r");
  char c;

  if(fptr != NULL) {
    for(int i=0;i<max;i++) {
      c = getc(fptr); 
      text[i] = c;
    }
  }
  fclose(fptr);
  return text;
}

int find(char *text, char *search, int max) {
  int offset, i;

  for (i=0;i<max;i++) {
    if (text[i] == search[0]) {
      offset = i;
      while (text[i] == search[i - offset] && text[i] != '\0') {
        i++;
      }
      if (i - offset == searchTermLength - 1)
        return offset;
    }
  }
  printf("Match Not found\n");
  return -1;
}

void replace(char *text, char *search, char *replace, int max) {
  int offset = find(text, search, max);
  int i, j, k;
  FILE *fptr2;
  fptr2 = fopen(path2, "w");

  if (offset != -1) {
    for (i=0; i<offset; i++) {
      if (text[i] != '\0')
        putc(text[i], fptr2);    
    }
    for (j=0; j < replaceTermLength; j++) {
      if (replace[j] != '\0')
        putc(replace[j], fptr2);
    }
    for (k = offset + searchTermLength - 1; k < max; k++) {
      if(text[k] != '\0')
        putc(text[k], fptr2);
    }
    remove(path);
    rename(path2, path);
  }
}

int main(void) {
  FILE *fptr;
  int max = characterCount(fptr);
  char fileContents[max];
  copy(fptr, fileContents, max);
  replace(fileContents, searchTerm, replaceTerm, max);
}

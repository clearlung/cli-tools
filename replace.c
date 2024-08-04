//program instructions: replace occurences of searchTerm with replaceTerm
//todo: make program read input through getchar insted of getc. also remove instances of the charactercount function because it's useless.
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#define IN 1
#define OUT 0

char * copy(char *array, char *text);
int find(char *text, char *search, int max);
void replace(char *text, char *search, char *replace, int max);

int main(void) {
  char searchTerm[] = "berry";
  char replaceTerm[] = "pineapple"; 
  int searchTermLength = sizeof(searchTerm) / sizeof(searchTerm[0]);
  int replaceTermLength = sizeof(replaceTerm) / sizeof(replaceTerm[0]);
  char fileContents[1000];

  copy(fptr, fileContents, max);
  replace(fileContents, searchTerm, replaceTerm, max);
}


char * copy(char *array, int max) {
  int i, c;  
  i = 0;

  while((c = getchar) != EOF && i<max;) {
    c = getc(fptr); 
    array[i++] = c;    
  }

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

void replace(char *array, char *search, char *replace) {
  int offset = find(text, search, max);
  int i, j, k; // replace this method using state = IN/OUT for better functionality
  int state;

  if (offset != -1) {
    for (i=0; i<offset; i++) {
      if (text[i] != '\0')
        putc(text[i], fptr2);    
    }
    for (j=0; j < replaceTermLength; j++) {
      if (replace[j] != '\0')
        putc(replace[j], fptr2);
    }
    for (k = offset + searchTermLength - 1; text[k] != '\0'; k++) {
      if(text[k] != '\0')
        putc(text[k], fptr2);
    }
    remove(path);
    rename(path2, path);
  }
}

/* useless function
int characterCount(char *array) { 
  int c, counter;
  counter = 0;

  while((c=getc(fptr)) c != EOF) {
    counter += 1;
  }

  return counter;
}
*/

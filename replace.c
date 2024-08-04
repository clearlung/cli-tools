//program instructions: replace occurences of searchTerm with replaceTerm
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#define IN 1
#define OUT 0
#define EXIT 3

char searchTerm[] = "berry";
char replaceTerm[] = "pineapple"; 
int searchTermLength = sizeof(searchTerm) / sizeof(searchTerm[0]);
int replaceTermLength = sizeof(replaceTerm) / sizeof(replaceTerm[0]);

void copy(char *array);
int find(char *text, char *search);
void replace(char *text, char *search, char *replace);

int main(void) {
  char fileContents[1000];

  copy(fileContents);
  replace(fileContents, searchTerm, replaceTerm);
}

int find(char *text, char *search) {
  int offset, i;
  i = 0;
  while (text[i] != '\0') {
    if (text[i] == search[0]) {
      offset = i;
      while (text[i] == search[i - offset] && text[i] != '\0')
        i++;
      if (i - offset == searchTermLength - 1)
        return offset;
    }
    i++;
  }
  
  return -1;
}

void replace(char *array, char *search, char *replace) {
  char fileContentsNew[1000]; // new array...
  int offset = find(array, search);
  int i, j, state;
  i = 0; j = 0; state = OUT;
  
  while (state != EXIT) {
    if (state == OUT) { 
      if (offset >= 0)
        state = IN;      
      else if (offset == -1) {
        /* this fucks up atm. non priority
         * while (fileContentsNew[j] != '\0')
          putchar(fileContentsNew[j++]);
        while (array[i] != '\0')
          putchar(array[i++]);
        */ 
        state = EXIT;
      }
    }
    if (state == IN) {
      for (i=0; i<offset; i++) {
        if (array[i] != '\0')
          putchar(array[i]);
      }
      for (i=0; i<replaceTermLength; i++) {
        if (replace[i] != '\0')
          putchar(replace[i]);
      }
      for (i=offset+searchTermLength-1; array[i] != '\0'; i++) {
        fileContentsNew[j++] = array[i];  //problem with this is that array will not change. I will need a separate function to make this work.
      }
      
      fileContentsNew[j] = '\0';
      offset = find(fileContentsNew, search);
      state = OUT;
    }
  }
}


void copy(char *array) {
  int i, c;  
  i = 0;

  while((c = getchar()) != EOF) { 
    array[i++] = c;    
  }
  array[i] = '\0';
}

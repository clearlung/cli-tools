//program instructions: replace occurences of searchTerm with replaceTerm
//todo: 1: read file input instead of getchar.
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#define IN 1
#define OUT 0
#define EXIT 2
#define MAXLEN 1000

char searchTerm[] = "berry";
char replaceTerm[] = "pineapple"; 
int searchTermLength = sizeof(searchTerm) / sizeof(searchTerm[0]);
int replaceTermLength = sizeof(replaceTerm) / sizeof(replaceTerm[0]);

int find(char *array, char *search);
void replace(char *array1, char *array2, char *search, char *replace);
void copy(char *array);

int main(void) {
  char fileContents[MAXLEN];
  char fileContentsNew[MAXLEN];

  int i=0;
  
  copy(fileContents);
  replace(fileContents, fileContentsNew, searchTerm, replaceTerm);
  while (fileContentsNew[i] != '\0')
    putchar(fileContentsNew[i++]);
}

void replace(char *array1, char *array2, char *search, char *replace) {
  int offset = find(array1, search);
  int i, j, k, state;
  state = OUT;
  k=0;

  while (state != EXIT) {
    if (state == OUT) { 
      if (offset != -1)
        state = IN;      
      else if (offset == -1) {
        i = 0;
        //append [ C ] to fileContentsNew
        while (array1[i] != '\0') {
          array2[k++] = array1[i++]; 
        }
        array2[k] = '\0';
        state = EXIT;
      }
    }
    if (state == IN) {
      if (offset != -1) {
        //set i to start of the block. copy [ A ] to fileContentsNew
        for (i=0; i<offset; i++)
          array2[k++] = array1[i];
        
        //set i to start of [ D ]. append [ D ] to fileContentsNew
        for (i=0; i<replaceTermLength-1; i++)
          array2[k++] = replaceTerm[i]; 
        
        //set i to beginning of [ C ]; set j to beginning of [ A ]
        i = offset+searchTermLength-1; 
        j = 0;

        // Overwrite [ A ][ B ][ C ] with [ C ]
        while (array1[i] != '\0')  
          array1[j++] = array1[i++];      
        array1[j] = '\0'; 
      }
      offset = find(array1, search);
      state = OUT;
    }
  }
}

int find(char *array, char *search) {
  int offset, i;
  i = 0;
  while (array[i] != '\0') {
    if (array[i] == search[0]) {
      offset = i;
      while (array[i] == search[i - offset] && array[i] != '\0')
        i++;
      if (i-offset == searchTermLength-1)
        return offset;
    }
    i++;
  }
  return -1;
}


void copy(char *array) {
  int i, c;  
  i = 0;

  while((c = getchar()) != EOF) { 
    *(array++) = c;    
  }
  *array = '\0';
}

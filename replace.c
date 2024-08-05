//program instructions: replace occurences of searchTerm with replaceTerm
//todo: overwrite file
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define IN 1
#define OUT 0
#define EXIT 2
#define MAXLEN 1000

int find(char *array, char *search);
void replace(char *array1, char *array2, char *search, char *replace);
void copy(FILE *fptr, char *array);
void overwrite(FILE *fptr, char *name, char *array);

int main(int argc, char **argv) {
  FILE *fptr;
  fptr = fopen(argv[1], "r");
  
  if (argc != 4) {
    puts("replace <file> <searchTerm> <replaceTerm>");
    return 1;
  }

  if (fptr == NULL) {
    puts("File does not exist\n");
    return 1;
  }

  char fileContents[MAXLEN];
  char fileContentsNew[MAXLEN];
  char *searchTerm = argv[2];
  char *replaceTerm = argv[3]; 
  
  copy(fptr, fileContents);
  replace(fileContents, fileContentsNew, searchTerm, replaceTerm);
  overwrite(fptr, argv[1], fileContentsNew);;

  return 0;
}

void overwrite(FILE *fptr1, char *name, char *array) {
  char *path="./blahblahblah";
  FILE *fptr2;
  fptr2 = fopen(path, "w");
  
  int i = 0;
  while((array[i]) != '\0')
    putc(array[i++], fptr2);

  fclose(fptr1);
  fclose(fptr2);
  remove(name);
  rename(path, name);
}

void replace(char *array1, char *array2, char *search, char *replace) {
  int offset = find(array1, search);
  int searchTermLength = strlen(search) + 1;
  int replaceTermLength = strlen(replace) + 1;

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
          array2[k++] = replace[i]; 
        
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
  int searchTermLength = strlen(search) + 1;
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


void copy(FILE *fptr, char *array) {
  int i, c;  
  i = 0;

  while((c = getc(fptr)) != EOF) { 
    *(array++) = c;    
  }
  *array = '\0';
}

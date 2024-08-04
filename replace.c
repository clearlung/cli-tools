//program instructions: replace occurences of searchTerm with replaceTerm
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#define IN 1
#define OUT 0
#define EXIT 2

char searchTerm[] = "berry";
char replaceTerm[] = "pineapple"; 
int searchTermLength = sizeof(searchTerm) / sizeof(searchTerm[0]);
int replaceTermLength = sizeof(replaceTerm) / sizeof(replaceTerm[0]);

typedef struct {
  char fileContents[1000];
  char fileContentsNew[1000];
  char buffer[1000];
} Text;

int find(char *array, char *search);
void replace(Text *text, char *search, char *replace);
void copy(char *array);
void initializeBuffer(char *contents, char *buffer);

int main(void) {
  Text text;
  int i;
  
  copy(text.fileContents);
  initializeBuffer(text.fileContents, text.buffer);

  replace(&text, searchTerm, replaceTerm);
  i = 0;
  while (text.fileContentsNew[i] != '\0')
    putchar(text.fileContentsNew[i++]);
}

void replace(Text *text, char *search, char *replace) {
  int offset = find(text->buffer, search);
  int i, j, k, state;
  state = OUT;
  k=0;

  while (state != EXIT) {
    if (state == OUT) { 
      if (offset != -1)
        state = IN;      
      else if (offset == -1) {
        //set i to beginning of [ C ]
        i = 0;
        while (text->buffer[i] != '\0') {
          text->fileContentsNew[k++] = text->buffer[i++]; 
        }
        text->fileContentsNew[k] = '\0';
        state = EXIT;
      }
    }
    //this only works twice for some reason.
    if (state == IN) {
      if (offset != -1) {
        //set i to start of the block. copy [ A ] to fileContentsNew
        for (i=0; i<offset; i++) //stringB = [ A ]
          text->fileContentsNew[k++] = text->buffer[i];
        
        //set i to start of [ D ]. append [ D ] to fileContentsNew
        for (i=0; i<replaceTermLength-1; i++) //stringB + [ D ] = stringB
          text->fileContentsNew[k++] = replaceTerm[i]; 
        
        //set i to beginning of [ C ]; set j to beginning of [ A ]
        i = offset+searchTermLength-1; 
        j = 0;

        // Overwrite [ A ][ B ][ C ] with [ C ]
        while (text->buffer[i] != '\0')  
          text->buffer[j++] = text->buffer[i++];      

        text->buffer[j] = '\0'; 
        offset = find(text->buffer, search);

      }
      state = OUT;
    }
  }
}

/* CONCEPT just a representation
 * if offset != -1
 * [ A ][ B ][ C ] = StringA
 * [ A ] = offset
 * [ B ] = searchTerm
 * [ C ] = buffer
 * [ D ] = replaceTerm
 *
 * [ A ][ D ] = StringB
 * [ C ] = [ C.A ][ C.B ][ C.C ]
 * 
 * [ A ][ D ][ C.A ][ D ] = StringB
 * etc...
 * if offset == -1
 * StringB + buffer = StringA
 */


/* old method for reference
for (i=0; i<offset; i++) {
  if (array[i] != '\0')
    putchar(array[i]);
}
for (i=0; i<replaceTermLength; i++) {
  if (replace[i] != '\0')
    putchar(replace[i]);
}
for (i=offset+searchTermLength-1; array[i] != '\0'; i++) {
  fileContentsNew[j++] = array[i]; 
}
fileContentsNew[j] = '\0';
offset = find(fileContentsNew, search);
state = OUT;
*/

void initializeBuffer(char *contents, char *buffer) {
  int i = 0;

  while (contents[i] != '\0') {
    buffer[i++] = contents[i];
  }
  buffer[i] = '\0';
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

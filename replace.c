//program instructions: replace occurences of searchTerm with replaceTerm
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#define IN 1
#define OUT 0
#define EXIT -1

char searchTerm[] = "berry";
char replaceTerm[] = "pineapple"; 
int searchTermLength = sizeof(searchTerm) / sizeof(searchTerm[0]);
int replaceTermLength = sizeof(replaceTerm) / sizeof(replaceTerm[0]);

void copy(char *array);
int find(char *text, char *search);
void replace(char *text, char *search, char *replace);

typedef struct {
  char fileContents[1000];
  char fileContentsNew[1000];
} Text;

int main(void) {
  Text text;

  copy(&text.fileContents);
  replace(&text.fileContents, searchTerm, replaceTerm);
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
        state = EXIT;
      }
    }
    if (state == IN) {
      //refer to CONCEPT below  
      //print will be done by main
    }
  }
}

/* CONCEPT
 * if offset != -1
 * [ A ][ B ][ C ] = StringA
 * [ A ] = offset
 * [ B ] = searchTermLen
 * [ C ] = buffer
 * [ A ][ B ] = StringB
 * [ C ] = [ C.A ][ C.B ][ C.C ]
 * [ A ][ B ][ C.A ][ C.B ] = StringB
 * etc...
 * if offset == -1
 * StringB + [ C.C ] = StringA
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

void copy(Text *text) {
  int i, c;  
  i = 0;

  while((c = getchar()) != EOF) { 
    text.fileContents[i++] = c;    
  }
  array[i] = '\0';
}

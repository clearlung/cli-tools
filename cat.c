#include <stdio.h>

int main(int argc, char **argv) {
  FILE *fptr;
  int c;

  if (argc > 1) {
    fptr = fopen(argv[1], "r");
  }
  else if (argc == 1) {
    printf("Directory not provided\n");
    return 1;
  }
  
  if (fptr == NULL) {
    printf("File does not exist\n");
    return 1;
  }

  while ((c = getc(fptr)) != EOF) {
    putchar(c);
  }
  return 0;
}

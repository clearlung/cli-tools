#include <stdio.h>

int main(int argc, char **argv) {
  FILE *fptr;
  int c;

  if (argc != 2) {
    puts("cp <targetFile> <destinationFile>");
    return 1;
  }

  fptr = fopen(argv[1], "r");
  
  if (fptr == NULL) {
    printf("File does not exist\n");
    return 1;
  }

  while ((c = getc(fptr)) != EOF) {
    putchar(c);
  }
  return 0;
}

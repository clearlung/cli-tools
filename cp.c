#include <stdio.h>

void copy(FILE *fptr1, FILE *fptr2);

int main(int argc, char **argv) {
  if (argc != 3) {
    puts("cp <targetFile> <destinationFile>");
    return 1;
  }

  FILE *fptr1, *fptr2;
  fptr1 = fopen(argv[1], "r");
  fptr2 = fopen(argv[2], "w");

  if (fptr1 == NULL) {
    puts("<targetFile> does not exist");
    return 1;
  }
  else if (fptr2 == NULL) {
    puts("<destinationFile> does not exist");
    return 1;
  }

  copy(fptr1, fptr2);
  fclose(fptr1);
  fclose(fptr2);
  return 0;
}

void copy(FILE *fptr1, FILE *fptr2) {
  int c;
  while ((c = getc(fptr1)) != EOF) {
    putc(c, fptr2);
  }
}

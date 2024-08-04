//this doesn't work. I'll fix it later.
#include <stdio.h>

void copy(FILE *fptr1, FILE *fptr2);

int main(int argc, char **argv) {
  FILE *fptr1, *fptr2;

  if (argc != 3) {
    puts("mv <targetFile> <destinationFile>");
    return 1;
  }
  
  char *targetFile = argv[1]; 
  char *destinationFile = argv[2];
  printf("<targetFile>: %s, <destinationFile>: %s\n", targetFile, destinationFile);

  fptr1 = fopen(targetFile, "r");
  fptr2 = fopen(destinationFile, "w");
  
  if (fptr1 == NULL) {
    puts("<targetFile> does not exist");
    return 1;
  }
  else if (fptr2 == NULL) {
    puts("<destinationFile> does not exist");
    return 1;
  }

  move(fptr1, fptr2);
  
  fclose(fptr1);
  fclose(fptr2);
  remove(targetFile);
  rename(destinationFile, targetFile);
  return 0;
}

void copy(FILE *fptr1, FILE *fptr2) {
  int c;
  while ((c = getc(fptr1)) != EOF) {
    putc(c, fptr2);
  }
}

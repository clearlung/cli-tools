#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

const char *path="/home/clear/todo/todo.txt";

void read(FILE *fptr) {
	fptr = fopen(path, "r");
  char readFile;
  if (fptr != NULL) {
    char readFile[100];
    while(fgets(readFile, 100, fptr)) {
      printf("%s", readFile);
    }
  }
  printf("\n");
  fclose(fptr);
}

void deleteLine(FILE *fptr1, FILE *fptr2) {
  int deleteLine, counter = 1;
  char ch;
  fptr1 = fopen(path, "r");	
  fptr2 = fopen("todo.new", "w");
  printf("line to delete: ");
  scanf("%d", &deleteLine);
  while (ch != EOF) {
    ch = getc(fptr1);
    if (counter != deleteLine) {
      putc(ch, fptr2);
    }
    if (ch == '\n') {
      counter++;
    }      
  }
  fclose(fptr1);
  fclose(fptr2);
  remove(path);
  rename("todo.new", path);
}

void appendLine(FILE *fptr, int argc, char **argv) {
  fptr = fopen(path, "a");
  if(argc == 3) {
    fprintf(fptr, "%s\n", argv[2]);
    fclose(fptr);
  } else if(argc == 2) {
    char task[30];
    printf("name of task: ");
    fgets(task, sizeof(task), stdin);
    fprintf(fptr, "%s\n", task);
    fclose(fptr);
  }
}

int main(int argc, char **argv) {
	int optionVal = 0;
	FILE *fptr;
	while(optionVal = getopt(argc, argv, "lrn")) {
		switch(optionVal) {
			case 'l':
        read(fptr);
        break;
			case 'r':
				FILE *fptr1, *fptr2;
        deleteLine(fptr1, fptr2);
				break;
			case 'n':
        appendLine(fptr, argc, argv);
        break;
			default:
				return 0;
		}
	}
	return 0;
}

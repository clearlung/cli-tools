#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void list(void), new(void), rm(void);

int main(int argc, char **argv) {
	int optionVal = 0;
	while(optionVal = getopt(argc, argv, "lrn")) {
		switch(optionVal) {
			case 'l':
				list();
				break;
			case 'r':
				rm();
				break;
			case 'n':
				new();
				break;
			default:
				return 0;
		}
	}
	return 0;
}

void list(void) {
	FILE *fptr;
	fptr = fopen("todo.txt", "r");
	char readFile;
	if (fptr != NULL) {
		char readFile[100];
		while(fgets(readFile, 100, fptr)) {
			printf("%s", readFile);
		}
	}
	fclose(fptr);
}

void new(void) {
	FILE *fptr;
	fptr = fopen("todo.txt", "a");
	char task[30];
	printf("name of task: ");
	fgets(task, sizeof(task), stdin);
	fprintf(fptr, "%s", task);
	fclose(fptr);
}

void rm(void) {
    FILE *fptr1, *fptr2;
    int deleteLine, counter = 1;
   	char ch = 'A';

    fptr1 = fopen("todo.txt", "r");	
    printf("line to delete: ");
    scanf("%d", &deleteLine);
    fptr2 = fopen("todo.new", "w");
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
    remove("todo.txt");
    rename("todo.new", "todo.txt");
}

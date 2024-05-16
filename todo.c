#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

const char *path="/home/clear/projects/todo.txt";

int main(int argc, char **argv) {
	int optionVal = 0;
	FILE *fptr;
	while(optionVal = getopt(argc, argv, "lrnt")) {
		switch(optionVal) {
			case 'l':
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
				break;
			case 'r':
				FILE *fptr1, *fptr2;
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
				break;
			case 'n':
				fptr = fopen(path, "a");
				if(argc == 3) {
					fprintf(fptr, "%s", argv[2]);
					fclose(fptr);
				} else if(argc == 2) {
					char task[30];
					printf("name of task: ");
					fgets(task, sizeof(task), stdin);
					fprintf(fptr, "%s", task);
					fclose(fptr);
				}
				break;
			default:
				return 0;
		}
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main(void) {
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

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *fptr;
	fptr = fopen("todo.txt", "r");
	
	if (ftpr != NULL) {
		char readFile[100];
		while(fgets(readFile, 100, fptr)) {
			printf("%s", readFile);
		}
	} else {
		printf("Unable to open file");
	}

	fclose(fptr);
}

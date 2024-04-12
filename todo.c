#include <stdlib.h>
#include <stdio.h>

int main(void) {
	FILE *fptr;
	fptr = fopen("todo.txt", "a");

	char task[30];
	printf("name of task: ");
	fgets(task, sizeof(task), stdin);
	fprintf(fptr, "%s", task);
	
	fclose(fptr);
}

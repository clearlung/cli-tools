#include <stdio.h>

int main()
{
    FILE *fptr1, *fptr2;
    int delete_line, counter = 1;
    char readFile[100];
	char ch;

    fptr1 = fopen("todo.txt", "r");	
	if (fptr1 != NULL) {
		while(fgets(readFile, 100, fptr1)) {
			printf("%s", readFile);
		}
	}
    //rewind
    rewind(fptr1);
    printf("line to delete: ");
    scanf("%d", &delete_line);
    //open new file in write mode
    fptr2 = fopen("todo.new", "w");
    ch = getc(fptr1);
	while (ch != EOF) {
        ch = getc(fptr1);
        if (counter != delete_line) {
            //copy all lines in file replica.c
            putc(ch, fptr2);
        }
        if (ch == '\n') {
            counter++;
        }      
    }
    fclose(fptr1);
    fclose(fptr2);
    remove("todo.txt");
    //rename the file replica.c to original name
    rename("todo.new", "todo.txt");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc == 2) { 
		char *a = argv[1];
		unsigned int chama = atoi(a);
		for (int i = 0; i < chama; i++) {
			printf("chama");
		}
		printf("burger\n");
		return 0;
	} else printf("value not provided\n");
	return 0;
}

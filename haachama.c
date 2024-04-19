#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int chama, counter = 0;
	if (argc == 2) { 
		char *a = argv[1];
		int chama = atoi(a);
		while (counter < chama) {
			printf("chama");
			counter++;
		}
	} else {
		printf("number of chamas: ");
		scanf("%d", &chama);
		while (counter < chama) {
			printf("chama");
			counter++;
		}
	}
	printf("burger\n");
}

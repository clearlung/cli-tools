#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char **argv) {
	int optionVal = 0;
	
	while((optionVal = getopt(argc, argv, "l:r:n"))) {
		switch(optionVal) {
			case 'l':
				printf("list\n");
				break;
			case 'r':
				printf("remove\n");
				break;
			case 'n':
				prin tf("new\n");
				break;
			default:
				return 0;
		}
	}
	return 0;
}

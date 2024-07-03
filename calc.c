#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

const char *path="/home/clear/projects/todo.txt";

int main(int argc, char **argv) {
	int optionVal = 0;
	FILE *fptr;
	while(optionVal = getopt(argc, argv, "asdm")) {
    float x, y, answer;
		switch(optionVal) {
			case 'a':
        x = atof(argv[2]);
        y = atof(argv[3]);
        answer = x + y;
        printf("%f\n", answer);
      break;
      case 's':
        x = atof(argv[2]);
        y = atof(argv[3]);
        answer = x - y;
        printf("%f\n", answer);
      break;
      case 'd':
        x = atof(argv[2]);
        y = atof(argv[3]);
        answer = x / y;
        printf("%f\n", answer);
      break;
			case 'm':
        x = atof(argv[2]);
        y = atof(argv[3]);
        answer = x * y;
        printf("%f\n", answer);
      break;
			default:
				return 0;
		}
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h> 

int multiplication(int n) {
  return n*2;
}

int division(int n) {
  return n/2;
}
int main(int argc, const char *argv[]) {
  switch (*argv[1]) {
    case 'm':
      int x = atoi(argv[2]);
      x = multiplication(x);
      printf("Here's your number bitch: %d\n", x);
      break;
    case 'd':
      x = atoi(argv[2]);
      x = division(x);
      printf("Here's your number bitch: %d\n", x);
    default:
      return 0;
      break;
  }
  return 0;
}

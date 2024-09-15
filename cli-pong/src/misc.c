#include <stdio.h>
#include <main.h>
#include <misc.h>

void clearScreen(void) {
  printf("\033[H\033[J"); 
}

void drawChar(int x, int y) {
  printf("\033[%d;%dH#", y, x); 
}

int returnBallDir(Ball *ball) {
  if (ball->speed.x < 0)
    return 0;
  else if (ball ->speed.x > 0)
    return 1;
  return -1;
}

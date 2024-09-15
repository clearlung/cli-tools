#include <stdio.h>
#include <main.h>

void modifyNumberArray(int score, int number[][NUM_WIDTH]) {
  switch (score) {
  case 0:
    for (int y=0; y<NUM_HEIGHT; y++) {
      for (int x=0; x<NUM_WIDTH; x++) {
        if (y == 0 || y == 4 ||
            x == 0 || x == 2)
          number[y][x] = 1;
        else
          number[y][x] = 0;
      }
    } break;
  case 1:
    for (int y=0; y<NUM_HEIGHT; y++) {
      for (int x=0; x<NUM_WIDTH; x++) {
        if (x == 1)
          number[y][x] = 1;
        else
          number[y][x] = 0;
      }
    } break;
  case 2:
    for (int y=0; y<NUM_HEIGHT; y++) {
      for (int x=0; x<NUM_WIDTH; x++) {
        if (y == 0 || y == 2 || y == 4 ||
            (y == 1 && x == 2) || (y == 3 && x == 0))
          number[y][x] = 1;
        else
          number[y][x] = 0;
      }
    } break;
  case 3:
    for (int y=0; y<NUM_HEIGHT; y++) {
      for (int x=0; x<NUM_WIDTH; x++) {
        if (y == 0 || y == 2 || y == 4 ||
            x == 2)
          number[y][x] = 1;
        else
          number[y][x] = 0;
      }
    } break;
  case 4:
    for (int y=0; y<NUM_HEIGHT; y++) {
      for (int x=0; x<NUM_WIDTH; x++) {
        if (y == 2 ||
            (y < 2 && (x == 0 || x == 2)) || (y > 2 && x == 2))
          number[y][x] = 1;
        else
          number[y][x] = 0;
      }
    } break;
  case 5:
    for (int y=0; y<NUM_HEIGHT; y++) {
      for (int x=0; x<NUM_WIDTH; x++) {
        if (y == 0 || y == 2 || y == 4 ||
            (y == 1 && x == 0) || (y == 3 && x == 2))
          number[y][x] = 1;
        else
          number[y][x] = 0;
      }
    } break;
  case 6:
    for (int y=0; y<NUM_HEIGHT; y++) {
      for (int x=0; x<NUM_WIDTH; x++) {
        if (y == 0 || y == 2 || y == 4 ||
            (y == 1 && x == 0) || (y == 3 && (x == 0 || x == 2)))
          number[y][x] = 1;
        else
          number[y][x] = 0;
      }
    } break;
  case 7:
    for (int y=0; y<NUM_HEIGHT; y++) {
      for (int x=0; x<NUM_WIDTH; x++) {
        if (y == 0 ||
            (y == 1 && x == 2) || (y == 2 && (x == 1 || x == 2)) ||
            (y == 3 && (x == 0 || x == 1)) || (y == 4 && (x == 0)))
          number[y][x] = 1;
        else
          number[y][x] = 0;
      }
    } break;
  case 8:
    for (int y=0; y<NUM_HEIGHT; y++) {
      for (int x=0; x<NUM_WIDTH; x++) {
        if (y == 0 || y == 2 || y == 4 ||
            x == 0 || x == 2)
          number[y][x] = 1;
        else
          number[y][x] = 0;
      }
    } break;
  case 9:
    for (int y=0; y<NUM_HEIGHT; y++) {
      for (int x=0; x<NUM_WIDTH; x++) {
        if (y == 0 || y == 2 || y == 4 ||
            (y == 1 && (x == 0 || x == 2)) || x ==2)
          number[y][x] = 1;
        else
          number[y][x] = 0;
      }
    } break;
  default:
    puts("value outside of range 1-9");
    break;
  }
}

#include <stdio.h>
#include <main.h>
#include <render.h>
#include <misc.h>
#include <number.h>

void render(GameState *game) {
  Ball *ball = &game->ball;
  Paddle *paddles = game->paddles;
  
  renderClear(game->window);
  renderScores(paddles, game->window);
  renderBall(ball, game->window);
  renderPaddles(paddles, game->window);

  for (int y=0; y<HEIGHT; y++) {
    for (int x=0; x<WIDTH; x++)
     game->window[y][x] ? printf("#") : printf(" ");
    printf("\n");
  }
}

void renderBall(Ball *ball, int window[][WIDTH]) {
  Vec2i initial, size;
  initial.x = (int)ball->pos.x;
  initial.y = (int)ball->pos.y;
  size.x = (int)(ball->pos.x + ball->size.x);
  size.y = (int)(ball->pos.y + ball->size.y);

  for (int y=initial.y; y<size.y; y++)
    for (int x=initial.x; x<size.x; x++)
      window[y][x] = 1;
}

void renderPaddles(Paddle *paddles, int window[][WIDTH]) {
  for (int i=0; i<PADDLES; i++) {
    Vec2i initial, size;
    initial.x = (int)paddles[i].pos.x;
    initial.y = (int)paddles[i].pos.y;
    size.x = (int)(paddles[i].pos.x + paddles[i].size.x);
    size.y = (int)(paddles[i].pos.y + paddles[i].size.y);
    
    for (int y=initial.y; y<size.y; y++)
      for (int x=initial.x; x<size.x; x++)
        window[y][x] = 1;
  } 
}

void renderScores(Paddle *paddles, int window[][WIDTH]) {
  for (int i=0; i<PADDLES; i++) {
    int initialX;
    if (i == 0) 
      initialX = WIDTH/2 - WIDTH/4;
    else if (i == 1)
      initialX = WIDTH/2 + WIDTH/4 - 1;
    
    int number[NUM_HEIGHT][NUM_WIDTH];
    modifyNumberArray(paddles[i].score, number);

    int initialY = HEIGHT/2 - NUM_HEIGHT/2;
    for (int y1 = 0, y2 = initialY; y1<NUM_HEIGHT; y1++, y2++) {
      for (int x1 = 0, x2 = initialX; x1<NUM_WIDTH; x1++, x2++) {
        window[y2][x2] = number[y1][x1];
      }
    }
  }
}

void renderClear(int window[][WIDTH]) {
  clearScreen();
  for (int y=1; y<HEIGHT-1; y++)
    for (int x=1; x<WIDTH-1; x++) 
      if (x != (int)WIDTH/2)
        window[y][x] = 0;
}


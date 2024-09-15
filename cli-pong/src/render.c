#include <stdio.h>
#include <main.h>
#include <render.h>
#include <misc.h>

void render(GameState *game) {
  Ball *ball = &game->ball;
  Paddle *paddles = game->paddles;
  
  renderClear(game->window);
  renderBall(ball, game->window);
  renderPaddles(paddles, game->window);

  for (int y=0; y<HEIGHT; y++) {
    for (int x=0; x<WIDTH; x++)
     game->window[y][x] ? printf("#") : printf(" ");
    printf("\n");
  }
}

void renderBall(Ball *ball, int window[][WIDTH]) {
  int x = (int)ball->pos.x;
  int y = (int)ball->pos.y;
  window[y][x] = 1;
}

void renderPaddles(Paddle *paddles, int window[][WIDTH]) {
  for (int i=0; i<PADDLES; i++) {
    int h = paddles[i].size.y;

    for (int j=0; j<h; j++) {
      int x = paddles[i].pos.x;
      int y = paddles[i].pos.y + j;

      window[y][x] = 1;
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


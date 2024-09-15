#include <stdio.h>
#include <main.h>
#include <render.h>
#include <misc.h>

void render(GameState *game) {
  Ball *ball = &game->ball;
  Paddle *paddles = game->paddles;

  clearScreen();
  renderBall(ball);
  renderPaddles(paddles);
  renderBorders();
}

void renderBall(Ball *ball) {
  drawChar((int)ball->pos.x, (int)ball->pos.y);
}

void renderPaddles(Paddle *paddles) {
  for (int i=0; i<PADDLES; i++) {
    int h = paddles[i].size.y;

    for (int j=0; j<h; j++) {
      int x = paddles[i].pos.x;
      int y = paddles[i].pos.y + j;

      drawChar(x, y);
    }
  }
}

void renderBorders(void) {
  for (int y=0; y<HEIGHT; y++) {
    int x=0;
    switch (y) {
      case 0:
        for (; x<WIDTH-1; x++)
          drawChar(x, y);
      case HEIGHT-1:
        for (; x<WIDTH; x++)
          drawChar(x, y);
      default:
        for (; x<=WIDTH-1; x+= WIDTH/2)
          drawChar(x, y);
    }
  }
}

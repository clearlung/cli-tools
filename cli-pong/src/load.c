#include <main.h>
#include <load.h>

void load(GameState *game) {
  Ball *ball = &game->ball;
  Paddle *paddles = game->paddles;

  loadBall(ball);
  loadPaddles(paddles);
  loadWindow(game->window);
  loadBorders(game->window);
}

void loadBall(Ball *ball) {
  ball->pos.x = WIDTH/2;
  ball->pos.y = HEIGHT/2;
  ball->size.x = 1;
  ball->size.y = 1;
  ball->speed.x = BALL_SPEED;
  ball->speed.y = BALL_SPEED;
}

void loadPaddles(Paddle *paddles) {
  for (int i=0; i<PADDLES; i++) {
    paddles[i].score = 0;
    paddles[i].size.x = 1;
    paddles[i].size.y = 4;
    paddles[i].pos.y = HEIGHT/2 - paddles[i].size.y/2;
  }

  paddles[0].pos.x = 3;
  paddles[1].pos.x = WIDTH-3;
}

void loadWindow(int window[][WIDTH]) {
  for (int y=0; y<HEIGHT; y++)
    for (int x=0; x<WIDTH; x++)
      window[y][x] = 0;
}

void loadBorders(int window[][WIDTH]) {
  for (int y=0; y<HEIGHT; y++) {
    switch (y) {
      case 0:
        for (int x=0; x<WIDTH; x++)
          window[y][x] = 1;
        break;
      case HEIGHT-1:
        for (int x=0; x<WIDTH; x++)
          window[y][x] = 1;
        break;
      default:
        for (int x=0; x<WIDTH; x+=WIDTH/2) 
          window[y][x] = 1;
        break;
    }
  }
}

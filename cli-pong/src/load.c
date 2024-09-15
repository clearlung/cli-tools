#include <main.h>
#include <load.h>

void load(GameState *game) {
  Ball *ball = &game->ball;
  Paddle *paddles = game->paddles;

  loadBall(ball);
  loadPaddles(paddles);
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

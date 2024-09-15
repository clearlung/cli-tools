#include <main.h>
#include <movement.h>
#include <misc.h>

void movement(GameState *game) {
  Ball *ball = &game->ball;
  Paddle *paddle = &game->paddles[returnBallDir(ball)];

  moveBall(ball);
  movePaddle(ball, paddle);
}

void moveBall(Ball *ball) {
  ball->pos.x += ball->speed.x;
  ball->pos.y += ball->speed.y;
}

void movePaddle(Ball *ball, Paddle *paddle) {
  float middle = paddle->pos.y + paddle->size.y/2;
  
  if (middle < ball->pos.y &&
      paddle->pos.y+paddle->size.y < HEIGHT-1)
    paddle->pos.y++;
  else if (middle > ball->pos.y &&
      paddle->pos.y > 2) 
    paddle->pos.y--;
}

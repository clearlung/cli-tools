#include <main.h>
#include <collision.h> 
#include <misc.h>

void collision(GameState *game) {
  Ball *ball = &game->ball;  
  Paddle *paddles = game->paddles;

  collisionBall(ball, paddles);
  collisionPaddle(ball, paddles);
}

void collisionBall(Ball *ball, Paddle *paddles) {
  if (ball->pos.x < 0)
    paddles[1].score++;
  else if (ball->pos.x > WIDTH)
    paddles[0].score++;

  if (ball->pos.y <= 1 ||
      ball->pos.y + ball->size.y >= HEIGHT)
    ball->speed.y *= -1;
}

void collisionPaddle(Ball *ball, Paddle *paddles) {
  Paddle *paddle = &paddles[returnBallDir(ball)];

  if (ball->pos.x >= paddle->pos.x &&
      ball->pos.x <= paddle->pos.x + paddle->size.x &&
      ball->pos.y >= paddle->pos.y &&
      ball->pos.y <= paddle->pos.y + paddle->size.y)
    ball->speed.x *= -1;
}

#include <stdio.h>
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
  if (ball->pos.x < 0) {
    if (paddles[1].score <= 9)
      paddles[1].score++;
    else
      resetScores(paddles, 2);
    resetBallPos(ball);
  }
  else if (ball->pos.x > WIDTH) {
    if (paddles[0].score <= 9)
      paddles[0].score++;
    else
      resetScores(paddles, 1);
    resetBallPos(ball);
  }

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

void resetBallPos(Ball *ball) {
  ball->pos.x = WIDTH/2;
  ball->pos.y = HEIGHT/2;
  ball->speed.x *= -1;
}

void resetScores(Paddle *paddles, int i) {
  for (int i=0; i<PADDLES; i++) {
    paddles[i].score = 0;
  }
  printf("Player %d won the set\n", i);
}

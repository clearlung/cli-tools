#pragma once

#define WIDTH 121
#define HEIGHT 50
#define PADDLES 2
#define BALL_SPEED 0.5

typedef struct {
  float x, y;
} Vec2;

typedef struct {
  Vec2 pos;
  Vec2 size;
  Vec2 speed;
} Ball;

typedef struct {
  Vec2 pos;
  Vec2 size;
  int score;
} Paddle;

typedef struct {
  Ball ball;
  Paddle paddles[2];
} GameState;

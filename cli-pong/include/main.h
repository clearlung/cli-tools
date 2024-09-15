#pragma once

#define WIDTH 121
#define HEIGHT 50
#define PADDLES 2
#define BALL_SPEED 1
#define PLAYER_SPEED 0.9
#define NUM_HEIGHT 5
#define NUM_WIDTH 3

typedef struct {
  float x, y;
} Vec2;

typedef struct {
  int x, y;
} Vec2i;

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
  int window[HEIGHT][WIDTH];
  Ball ball;
  Paddle paddles[2];
} GameState;

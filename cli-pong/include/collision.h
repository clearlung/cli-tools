#pragma once

void collision(GameState *game);
void collisionBall(Ball *ball, Paddle *paddles);
void collisionPaddle(Ball *ball, Paddle *paddles);
void resetBallPos(Ball *ball);
void resetScores(Paddle *paddles, int j);

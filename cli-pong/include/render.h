#pragma once

void render(GameState *game);
void renderClear(int window[][WIDTH]);
void renderBall(Ball *ball, int window[][WIDTH]);
void renderPaddles(Paddle *paddles, int window[][WIDTH]);
void renderScores(Paddle *paddles, int window[][WIDTH]);

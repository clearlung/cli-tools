#include "SDL2/SDL.h"
#include <stdio.h>
#include <time.h>
#define WINDOW_WIDTH 48
#define WINDOW_HEIGHT 48
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

typedef struct {
  int dx, dy;
} Ball;

typedef struct {
  Ball ball;
  SDL_Renderer *renderer;
} GameState;

void loadGame(GameState *game) {  
  game->ball.dx = 0;
  game->ball.dy = 0;
} 

int processEvents(SDL_Window *window, GameState *game) {
  SDL_Event event;
  int done = 0;
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_WINDOWEVENT_CLOSE:
        if(window) {
          SDL_DestroyWindow(window);
          window = NULL;
          done = 1;
        }
        break;
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym) {
          case SDLK_q:
            done = 1;
            break;
          case SDLK_SPACE:
            srandom((int)time(NULL));
            int rnd = random();
            if(game->ball.dx == 0 && game->ball.dy == 0) {
              game->ball.dx = (rnd > RAND_MAX/2) ? 3 : -3;
              srandom((int)time(NULL));
              game->ball.dy = (rnd > RAND_MAX/2) ? 3 : -3;
            }
            break;
        } 
        break;
      case SDL_QUIT:
        done = 1;
        break;
    }
  }
}

void doRender(SDL_Renderer *renderer, GameState *game) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}

void collision(GameState *game) {
  Ball *ball = &game->ball;
  int windowX, windowY;
  windowX += ball->dx;
  windowY += ball->dy;
  if(windowX <= 0 || windowX >= SCREEN_WIDTH - WINDOW_WIDTH)
    ball->dx *= -1;
  if(windowY <= 0 || windowY >= SCREEN_HEIGHT - WINDOW_HEIGHT) 
    ball->dy *= -1;
}

int main(void) {
  GameState gameState;
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  int windowX = SCREEN_WIDTH/2, windowY = SCREEN_HEIGHT/2;
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("pong", windowX, windowY, WINDOW_WIDTH, WINDOW_HEIGHT,0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  gameState.renderer = renderer;
  SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
  loadGame(&gameState);
  int done = 0;
  while(!done) {
    done = processEvents(window, &gameState);
    collision(&gameState);
    doRender(renderer, &gameState);
  }
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  return 0;
}

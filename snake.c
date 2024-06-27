#include "SDL2/SDL.h"
#include <stdio.h>
#include <time.h> 

typedef struct {
  int x, y;
  int dir;
} Player;

typedef struct {
  int x, y;
} Apple;

typedef struct {
  Player player;
  Apple apple;
  SDL_Renderer *renderer;
} GameState;

void loadGame(GameState *game) {  
  game->player.x = 320;
  game->player.y = 240;
  game->player.dir = 5;
  game->apple.x = random()%640;
  game->apple.y = random()%480;
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
        } break;
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym) {
          case SDLK_UP:
            game->player.dir = 0;
          break;
          case SDLK_DOWN:
            game->player.dir = 1;
          break;
          case SDLK_LEFT:
            game->player.dir = 2;
          break;
          case SDLK_RIGHT:
            game->player.dir = 3;
          break;
        } break;
      case SDL_QUIT:
        done = 1;
      break;
    }
  }
  return done;
}

void doRender(SDL_Renderer *renderer, GameState *game) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_Rect snake = { game->player.x, game->player.y, 4, 4 };
  SDL_RenderFillRect(renderer, &snake);
  SDL_Rect fruit = { game->apple.x, game->apple.y, 4, 4};
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(renderer, &fruit);
  SDL_RenderPresent(renderer);
}

void movement(GameState *game) {
  printf("%i", game->player.dir);
  if (game->player.dir == 0)
    game->player.y -= 1;
  else if (game->player.dir == 1)
    game->player.y += 1;
  else if (game->player.dir == 2)
    game->player.x -= 1;
  else if (game->player.dir == 3)
    game->player.x += 1;
}

void gameOver(GameState *game) {
  game->player.dir = 5;
  game->player.x = 320;
  game->player.y = 240;
}

void collision(GameState *game) {
  if (game->player.x < 0 || game->player.x > 640 || game->player.y < 0 || game->player.y > 480)
    gameOver(game);
}

int main(int argc, char *argv[]) {
  GameState gameState;
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Init(SDL_INIT_VIDEO);
  srandom((int)time(NULL));
  window = SDL_CreateWindow("Game Window",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      640,
      480,
      0
      );
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  gameState.renderer = renderer;

  loadGame(&gameState);
  int done = 0;
  while(!done) {
    done = processEvents(window, &gameState);
    collision(&gameState);
    movement(&gameState);
    doRender(renderer, &gameState);
  }
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  return 0;
}

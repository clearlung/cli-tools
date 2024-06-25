#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include <time.h>
#define GRAVITY 0.24f

typedef struct {
  float x, y;
} Player;

typedef struct {
  int x, y;
} Balloon;

typedef struct {
  Player player;
  SDL_Renderer *renderer;
} GameState;

void loadGame(GameState *game) {  
  game->player.x = 320;
  game->player.y = 240;
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
          case SDLK_ESCAPE:
            done = 1;
          break;
        } break;
      case SDL_QUIT:
        done = 1;
      break;
    }
  }
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_UP]) {
    game->player.y -= 0.5;
  }
  else if(state[SDL_SCANCODE_DOWN]) {
    game->player.y += 0.5;
  }
  return done;
}

void doRender(SDL_Renderer *renderer, GameState *game) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  
  SDL_Rect rect = { game->player.x, game->player.y, 48, 48 };
  SDL_RenderFillRect(renderer, &rect);
  //SDL_RenderCopyEx(renderer, game->playerFrames[0], NULL, &rect, 0, NULL, 0);
  SDL_RenderPresent(renderer);
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
    doRender(renderer, &gameState);
  }
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  return 0;
}

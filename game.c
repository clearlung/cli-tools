#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>

typedef struct {
  int x, y;
} Player;

typedef struct {
  int x, y;
} Star;

typedef struct {
  Player player;
  SDL_Texture *star;
  SDL_Renderer *renderer;
} GameState;

void loadGame(GameState *game) {
/*  for(int i = 0; i < 5; i++) {
    game->cats[i].x = i*64;
    game->cats[i].y = i*64;
  }
  */
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
    game->player.y--;
  }
  if(state[SDL_SCANCODE_DOWN]) {
    game->player.y++;
  }
  if(state[SDL_SCANCODE_LEFT]) {
    game->player.x--;
  }
  if(state[SDL_SCANCODE_RIGHT]) {
    game->player.x++;
  }
 
  return done;
}

void doRender(SDL_Renderer *renderer, GameState *game) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  
  SDL_Rect rect = { game->player.x, game->player.y, 200, 200 };
  SDL_RenderFillRect(renderer, &rect);
/*  for(int i = 0; i <100; i++) {
    SDL_Rect catRect = { game->cats[i].x, game->cats[i].y, 64, 64 };
    SDL_RenderCopy(renderer, game->cat, NULL, &catRect);
    } */
  SDL_Rect starRect = { 50, 50, 64, 64 };
  SDL_RenderCopy(renderer, game->star, NULL, &starRect);
  SDL_RenderPresent(renderer);
}
 

int main(int argc, char *argv[]) {
  GameState gameState;
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Surface *starSurface = NULL;
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Game Window",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      640,
      480,
      0
      );
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  starSurface = IMG_Load("star.png");
  if(starSurface == NULL) {
    printf("Image not on disk\n");
    SDL_Quit();
    return 1;
  }

  gameState.star = SDL_CreateTextureFromSurface(renderer, starSurface);
  SDL_FreeSurface(starSurface);

  gameState.renderer = renderer;

  loadGame(&gameState);
  int done = 0;
  while(!done) {
    done = processEvents(window, &gameState);
    doRender(renderer, &gameState);
    //SDL_Delay(10);
  }
  SDL_DestroyTexture(gameState.star);
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  return 0;
}

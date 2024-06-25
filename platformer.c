#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include <time.h>
#define GRAVITY 0.24f

typedef struct {
  float x, y, dx, dy;
  int onLedge;
} Player;

typedef struct {
  int x, y;
} Balloon;

typedef struct {
  int x, y, w, h;
} Tile;

typedef struct {
  Player player;
  Balloon balloons[100];
  Tile tiles[100];
  SDL_Texture *balloon;
  SDL_Texture *playerFrames[1];
  SDL_Texture *brick;
  SDL_Renderer *renderer;
} GameState;

void loadGame(GameState *game) {
  SDL_Surface *surface = NULL;
  surface = IMG_Load("assets/balloon.png");
  if(surface == NULL) {
    printf("Image not on disk\n");
    SDL_Quit();
    exit(1);
  }
  
  game->balloon = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);  

  surface = IMG_Load("assets/player_idle.png");
  if(surface == NULL) {
    printf("Image not on disk\n");
    SDL_Quit();
    exit(1);
  }
  game->playerFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);

  surface = IMG_Load("assets/player_walk.png");
  if(surface == NULL) {
    printf("Image not on disk\n");
    SDL_Quit();
    exit(1);
  }
  game->playerFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
  
  surface = IMG_Load("assets/tile.png");
  game->brick = SDL_CreateTextureFromSurface(game->renderer, surface);

  game->player.x = 320;
  game->player.y = 240;
  game->player.dy = 0;
  game->player.dx = 0;
  game->player.onLedge = 0;
/*  for(int i=0; i<100; i++) {
    game->balloons[i].x = random()%640;
    game->balloons[i].y = random()%480;
  }*/

  for(int i = 0; i < 100; i++) {
    game->tiles[i].w = 64;
    game->tiles[i].h = 64;
    game->tiles[i].x = i*64;
    game->tiles[i].y = 400;
  }
  game->tiles[99].x = 350;
  game->tiles[99].y = 200;
} 

void process(GameState *game) {
  Player *player = &game->player;
  player->x += player->dx;
  player->y += player->dy;
  player->dy += GRAVITY;
}

void collisionDetect(GameState *game) {
  for(int i=0;i<100;i++) {
    float mw = 48, mh = 48;
    float mx = game->player.x, my = game->player.y;
    float bx = game->tiles[i].x, by = game->tiles[i].y, bw = game->tiles[i].w, bh = game->tiles[i].h;
    if(mx+mw/2 > bx && mx+mw/2 < bx+bw) {
      if(my < by+bh && my > by && game->player.dy < 0) {
        game->player.y = by+bh;
        my = by+bh;
        game->player.dy = 0;
      } 
    } 
    if(mx+mw > bx && mx < bx + bw) {
      if(my+mh > by && my < by && game->player.dy > 0) {
        game->player.y = by-mh;
        my = by-mh;
        game->player.dy = 0;
        game->player.onLedge = 1;
      }
    }
    if(my+mh > by && my < by+bh) {
      if(mx < bx+bw && mx+mw > bx+bw && game->player.dx < 0) {
        game->player.x = bx + bw;
        mx = bx + bw;
        game->player.dx = 0;
      }
      else if(mx+mw > bx && mx < bx && game->player.dx > 0) {
        game->player.x = bx - mw;
        mx = bx - mw;
        game->player.dx = 0;
      }
    }
  }
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
          case SDLK_UP:
            if(game->player.onLedge) {
              game->player.dy = -8;
              game->player.onLedge = 0;
            } break;
        } break;
      case SDL_QUIT:
        done = 1;
      break;
    }
  }
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_LEFT]) {
    game->player.dx -= 0.5;
    if(game->player.dx < -6) {
      game->player.dx = -6;
    }
  }
  else if(state[SDL_SCANCODE_RIGHT]) {
    game->player.dx += 0.5;
    if(game->player.dx > 6) {
      game->player.dx = 6;
    }
  }
  else {
    game->player.dx *= 0.8f;
    if(fabsf(game->player.dx) < 0.1f) {
      game->player.dx = 0;
    }
  }
  return done;
}

void doRender(SDL_Renderer *renderer, GameState *game) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  
  SDL_Rect rect = { game->player.x, game->player.y, 48, 48 };
  SDL_RenderCopyEx(renderer, game->playerFrames[0], NULL, &rect, 0, NULL, 0);
  for(int i=0;i<100;i++) {
    SDL_Rect tileRect = { game->tiles[i].x, game->tiles[i].y, game->tiles[i].w, game->tiles[i].h };
    SDL_RenderCopy(renderer, game->brick, NULL, &tileRect);
  }
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
    process(&gameState);
    collisionDetect(&gameState);
    doRender(renderer, &gameState);
  }
  SDL_DestroyTexture(gameState.balloon);
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  return 0;
}

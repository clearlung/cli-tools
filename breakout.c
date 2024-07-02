#include "SDL2/SDL.h"
#include <stdio.h>
#define WINDOW_WIDTH 392
#define WINDOW_HEIGHT 600

typedef struct {
  int x, y, w, h;
} Paddle;

typedef struct {
  int x, y, w, h, exists;
} Tile;

typedef struct {
  int x, y, dx, dy, enabled;
} Ball;

typedef struct {
  Paddle paddle;
  Tile tiles[36];
  Ball ball;
  SDL_Renderer *renderer;
} GameState;

void loadGame(GameState *game) {
  game->paddle.x = WINDOW_WIDTH/2;
  game->paddle.y = WINDOW_HEIGHT - 20;
  game->paddle.w = 48;
  game->paddle.h = 4;
  game->ball.x = game->paddle.x;
  game->ball.y = game->paddle.y - game->paddle.h;
  game->ball.dx = 1;
  game->ball.dy = 0;
  game->ball.enabled = 1;

  for(int i=0;i<36;i++) {
    game->tiles[i].w = 24;
    game->tiles[i].h = 8;
    game->tiles[i].exists = 1;
  } for(int j=0;j<12;j++) {
      game->tiles[j].x = 8 + j*32;
      game->tiles[j].y = 4;
  } for(int l=12;l<24;l++) {
      game->tiles[l].x = 8 + 32*(l-12);
      game->tiles[l].y = 20;
  } for(int m=24;m<36;m++) {
    game->tiles[m].x = 8 + 32*(m-24);
    game->tiles[m].y = 36;
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
        case SDLK_q:
          done = 1;
        break;
        case SDLK_SPACE:
          game->ball.enabled = 0;
          game->ball.dy = -3;
        break;
        case SDLK_f:
          if(SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
            SDL_SetWindowFullscreen(window, 0);
          } else {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        } break;
      } break; 
    }
  }
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_LEFT] && game->paddle.x > 0) {
    game->paddle.x -= 5;
  }
  else if(state[SDL_SCANCODE_RIGHT] && game->paddle.x < WINDOW_WIDTH - game->paddle.w) {
    game->paddle.x += 5;
  }
  return done;
}

void movement(GameState *game) {
  game->ball.x += game->ball.dx;
  game->ball.y += game->ball.dy;
}

void collision(GameState *game) {
  if(game->ball.enabled == 0) {
    for(int i=0;i<36;i++) {
      int bx = game->tiles[i].x, by = game->tiles[i].y, bw = game->tiles[i].w, bh = game->tiles[i].h;
      if(game->ball.x >= bx && game->ball.x <= bx + bw && game->tiles[i].exists == 1 && game->ball.y >= by && game->ball.y <= by + bh) {
        if(game->ball.y >= by + (bh/2) || game->ball.y <= by + (bh/2)) {
          game->ball.dy *= -1;
          game->tiles[i].exists = 0;
        } else if(game->ball.x < bx || game->ball.x > bx) {
          game->ball.dx *= -1;
          game->tiles[i].exists = 0;
        }
      }
    } 
    if(game->ball.x < 0 || game->ball.x >= WINDOW_WIDTH){
      game->ball.dx *= -1;
    } else if(game->ball.y < 0) {
      game->ball.dy *= -1;
    } else if(game->ball.x >= game->paddle.x && game->ball.x <= game->paddle.x + game->paddle.w && game->ball.y <= game->paddle.y && game->ball.y >= game->paddle.y - game->paddle.h) {
    game->ball.dx = (game->ball.x - (game->paddle.x + (game->paddle.w/2)))/7;
    game->ball.dy *= -1;
    } else if(game->ball.y > WINDOW_HEIGHT) {
      game->ball.enabled = 1;
    }
  } else if(game->ball.enabled == 1) {
    game->ball.dx = 0;
    game->ball.dy = 0;
    game->ball.x = game->paddle.x + game->paddle.w/2;
    game->ball.y = game->paddle.y - game->paddle.h;
  }
}

void doRender(SDL_Renderer *renderer, GameState *game) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
  SDL_Rect border = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  SDL_RenderDrawRect(renderer, &border);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_Rect paddle = { game->paddle.x, game->paddle.y, game->paddle.w, game->paddle.h };
  SDL_RenderFillRect(renderer, &paddle);
  SDL_Rect ball = { game->ball.x - 2, game->ball.y, 4, 4};
  SDL_RenderFillRect(renderer, &ball);
  for(int i=0;i<36;i++) {
    if(game->tiles[i].exists == 1) {
      SDL_Rect tile = { game->tiles[i].x, game->tiles[i].y, game->tiles[i].w, game->tiles[i].h };
      SDL_RenderFillRect(renderer, &tile);
    }
  }
  SDL_RenderPresent(renderer);
}

int main(void) {
  GameState gameState;
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
  renderer = (SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
  gameState.renderer = renderer;
  SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
  loadGame(&gameState);
  int done = 0;
  while(!done) {
    done = processEvents(window, &gameState);
    movement(&gameState);
    collision(&gameState);
    doRender(renderer, &gameState);
  }
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  return 0;
}

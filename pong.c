#include "SDL2/SDL.h"
#include <stdio.h>
#include <time.h>
#define WINDOW_WIDTH  (640)
#define WINDOW_HEIGHT (480)

typedef struct {
  float y;
} Player;

typedef struct {
  float x, y, dx, dy;
} Ball;

typedef struct {
  int p1, p2;
} Points;

typedef struct {
  Player player;
  Player cpu;
  Ball ball;
  Points points;
  SDL_Renderer *renderer;
} GameState;

void loadGame(GameState *game) {  
  game->player.y = 240;
  game->cpu.y = 240;
  game->ball.x = 640/2;
  game->ball.y = 480/2;
  game->ball.dx = 0;
  game->ball.dy = 0;
  game->points.p1 = 0;
  game->points.p2 = 0;
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
          case SDLK_SPACE:
            srandom((int)time(NULL));
            int rnd = random();
            if(game->ball.dx == 0 && game->ball.dy == 0) {
              game->ball.dx = (rnd > RAND_MAX/2) ? 3 : -3;
              game->ball.dy = (rnd > RAND_MAX/2) ? 3 : -3;
            }
          break;
          case SDLK_f:
            if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
              SDL_SetWindowFullscreen(window, 0);
            } else {
              SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
            }
        } break;
      case SDL_QUIT:
        done = 1;
      break;
    }
  }

  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_UP] && game->player.y > 0) {
    game->player.y -= 5;
  }
  else if(state[SDL_SCANCODE_DOWN] && game->player.y < 480 -48) {
    game->player.y += 5;
  }
  return done;
}

void doRender(SDL_Renderer *renderer, GameState *game) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  
  SDL_Rect playerPaddle = { 0 + 20, game->player.y, 4, 48 };
  SDL_RenderFillRect(renderer, &playerPaddle);
  SDL_Rect CPUPaddle = { WINDOW_WIDTH - 20, game->cpu.y, 4, 48 };
  SDL_RenderFillRect(renderer, &CPUPaddle);
  SDL_Rect ball = { game->ball.x, game->ball.y, 4, 4};
  SDL_RenderFillRect(renderer, &ball);
  SDL_RenderPresent(renderer);
}

void CPUmovement(GameState *game) {
  while(game->cpu.y + 24 < game->ball.y && game->cpu.y < 480 - 48) {
      game->cpu.y += 1;
    }  
  while(game->cpu.y + 24 > game->ball.y && game->cpu.y > 0) {
      game->cpu.y -= 1;
  } 
}

void reset(GameState *game) {
  game->ball.x = WINDOW_WIDTH/2;
  game->ball.y = WINDOW_HEIGHT/2;
  game->ball.dx = 0;
  game->ball.dy = 0;
  printf("p1: %i\np2: %i\n", game->points.p1, game->points.p2);
}

void collision(GameState *game) {
  Ball *ball = &game->ball;
  Player *player = &game->player;
  Player *cpu = &game->cpu;
  ball->x += ball->dx;
  if(ball->x <= 0) {
    game->points.p2 += 1;
    reset(game);
  } else if(ball->x >= WINDOW_WIDTH - 4) {
    game->points.p1 += 1;
    reset(game);
  } else if(ball->x >= WINDOW_WIDTH - 20 && ball->x <= WINDOW_WIDTH+4 && ball->y >= cpu->y && ball->y <= cpu->y + 48) {
    ball->dx *= -1;
  } else if(ball->x <= 20 + 4 && ball->x >= 20 && ball->y >= player->y && ball->y <= player->y + 48) {
    ball->dx *= -1;
  } 
  ball->y += ball->dy;
  if(ball->y < 0 || ball->y > 480) {
    ball->dy *= -1;
  }
}

int main(void) {
  GameState gameState;
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("pong",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WINDOW_WIDTH,
      WINDOW_HEIGHT,
      SDL_WINDOW_RESIZABLE
      );
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  gameState.renderer = renderer;
  SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
  loadGame(&gameState);
  int done = 0;
  while(!done) {
    done = processEvents(window, &gameState);
    CPUmovement(&gameState);
    collision(&gameState);
    doRender(renderer, &gameState);
  }
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <main.h>
#include <load.h>
#include <movement.h>
#include <collision.h>
#include <render.h>
#include <misc.h>

int main(void) {
  GameState game;
  load(&game);
  
  while (1) {   
    movement(&game);
    collision(&game);
    render(&game);
    usleep(10000); 
  }
  
  return 0;
}

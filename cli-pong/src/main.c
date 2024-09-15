#include <stdio.h>
#include <unistd.h>
#include <main.h>
#include <load.h>
#include <movement.h>
#include <collision.h>
#include <render.h>
#include <misc.h>
#include <processInput.h>

int main(void) {
  GameState game;
  load(&game);
  set_conio_mode(1);

  int done = 0;
  while (!done) {
    done = processInput(&game);
    movement(&game);
    collision(&game);
    render(&game);
    usleep(50000); 
  }

  set_conio_mode(0);
  return 0;
}

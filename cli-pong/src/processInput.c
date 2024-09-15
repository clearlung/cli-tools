//llm generated
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <main.h>

int processInput(GameState *game) {
  fd_set read_fds;
  struct timeval timeout;
  int retval;
  FD_ZERO(&read_fds);
  FD_SET(STDIN_FILENO, &read_fds);
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  retval = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout);

  int done = 0;
  
  if (retval) {
    int c = getchar();
    switch (c) {
    case 'q':
      done = 1;
      break;
    case '1':
      if (game->paddles[0].size.y > 0)
        game->paddles[0].size.y -= 1;
      break;
    case '2':
      if (game->paddles[0].pos.y + game->paddles[0].size.y < HEIGHT+1)
        game->paddles[0].size.y += 1;
      break;
    case '3':
      game->ball.size.x += 1;
      break;
    case '4':
      game->ball.size.x -= 1;
      break;
    case '5':
      game->ball.size.y += 1;
      break;
    case '6':
      game->ball.size.y -= 1;
      break;
    }
  }
  return done;
}

void set_conio_mode(int enable) {
  static struct termios oldt, newt; 
  if (enable) {
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  } 
  else {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  }
}

#include <ncurses.h>
#define MAX_LENGTH 256
#include <stdlib.h>
#include <time.h>

typedef struct {
  int x, y;
} Segment;

Segment snake[MAX_LENGTH];
int length = 3;

// main principal
int main() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);

  int ch;

  int dir = KEY_RIGHT;

  snake[0].x = 10;
  snake[0].y = 10;
  snake[1].x = 9;
  snake[1].y = 10;
  snake[2].x = 8;
  snake[2].y = 10;
  // comida
  srand(time(NULL));

  int food_x = rand() % (COLS - 2) + 1;
  int food_y = rand() % (LINES - 2) + 1;
  // loop principal
  while (1) {
    ch = getch();

    clear();
    // movimiento
    if (ch == 'q')
      break;
    if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)
      dir = ch;

    // mover el cuerpo de atras hacia adelante
    for (int i = length - 1; i > 0; i--) {
      snake[i] = snake[i - 1];
    }

    // mover la cabeza
    if (dir == KEY_UP)
      snake[0].y--;
    if (dir == KEY_DOWN)
      snake[0].y++;
    if (dir == KEY_LEFT)
      snake[0].x--;
    if (dir == KEY_RIGHT)
      snake[0].x++;
    // colisiones
    if (snake[0].x >= COLS)
      snake[0].x = 0;
    if (snake[0].x < 0)
      snake[0].x = COLS - 1;
    if (snake[0].y >= LINES)
      snake[0].y = 0;
    if (snake[0].y < 0)
      snake[0].y = LINES - 1;

    // colision comida
    if (snake[0].x == food_x && snake[0].y == food_y) {
      length++;
      food_x = rand() % (COLS - 2) + 1;
      food_y = rand() % (LINES - 2) + 1;
    }
    // dibujar
    for (int i = 0; i < length; i++) {
      if (i == 0)
        mvprintw(snake[i].y, snake[i].x, "@");
      else
        mvprintw(snake[i].y, snake[i].x, "+");
    }
    mvprintw(food_y, food_x, "pene");
    refresh();
    napms(100);
  }
  endwin();
  return 0;
}

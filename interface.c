#include <ncurses.h>
#include "interface.h"

void initScreen() {
	initscr();
  	noecho();
  	nodelay(stdscr, TRUE);
  	keypad(stdscr, TRUE);
  	curs_set(0);
}

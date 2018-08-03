#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "engine.h"

int main(void) {
	initScreen();

	int r = 20, c = 30, key;
    board b;
	snake s;
	food f;
    game g = {&s, &b, &f};

    initGame(&g, r, c);

	refresh();
	while(1) {
		clear();
		updateBoard(&g);
		displayBoard(&g);
		refresh();
		key = getch();
		if(moveSnake(&g, key) == 0) break;
		usleep(300000);
	}
	nodelay(stdscr, FALSE);
	printw("GAME OVER"); 
	refresh();
	getch();
	endwin();
    return 0;
}
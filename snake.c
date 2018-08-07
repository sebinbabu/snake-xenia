#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "engine.h"
#include "interface.h"

int main(void) {
//	mainMenu();
	initScreen();
	int r = 10, c = 15, key, status = -1;
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
		if(status != -1)
			pauseGame(&g);
		key = getch();
		status = moveSnake(&g, key);
		if(status == 0)
			break;
	}

	nodelay(stdscr, FALSE);
	printw("\nGAME OVER\nPress q to Quit"); 
	refresh();
	
	key = getch();
	while(key != 'q') key = getch();
	endwin();
    return 0;
}
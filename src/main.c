#include <time.h>
#include <unistd.h>
#include <ncurses.h>

#include "game.h"
#include "interface.h"


int main(void) {
	initScreen();
	int r = 15, c = 25, speed = 250000, quantum = 10000, key = 0, status = -1;
    board b;
	snake s;
	food f;
    game g = {&s, &b, &f};

    initGame(&g, r, c, speed, quantum);
    updateBoard(&g);

	refresh();

	while(status != 0 && key != 'q' && key != 'Q') {
		clear();
		
		displayBoard(&g);
		refresh();

		if(status != -1)
			pauseGame(&g);
		key = getch();
		switch(key) {
			case 'S':
			case 's':
						if(saveGame(&g) == 1)
							printw("\nSave success");
						else
							printw("\nSave fail");
						refresh();
						usleep(speed);
						break;
			case 'L':
			case 'l':
						if(loadGame(&g) == 1)
							printw("\nLoad success");
						else
							printw("\nLoad fail");
						refresh();
						usleep(speed);
						break;
			default: 
						status = moveSnake(&g, key);

		}
	}

	nodelay(stdscr, FALSE);
	printw("\nGAME OVER\nPress 'q' to Quit"); 
	refresh();

	key = getch();
	while(key != 'q' && key != 'Q')
		key = getch();
	deleteGame(&g);
	endwin();
    return 0;
}
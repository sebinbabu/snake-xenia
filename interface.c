#include <ncurses.h>
#include "interface.h"

void initScreen() {
	initscr();
    //cbreak();
  	//noecho();
  	nodelay(stdscr, TRUE);
  	keypad(stdscr, TRUE);
  	curs_set(0);
    refresh();
}

void mainMenu() {
	initScreen();
	WINDOW *w;
	char list[5][12] = {
		"New Game",
		"Load Game",
		"Highscores",
		"Quit"
	};
	char item[13];

    int ch, i = 0;

	w = newwin(7, 16, 1, 1); 
	box(w, 0, 0);

	for(i = 0; i < 4; i++) {
        if(i == 0) 
            wattron(w, A_STANDOUT);
        else
            wattroff(w, A_STANDOUT);
        sprintf(item, "%-12s",  list[i]);
        mvwprintw(w, i + 1, 2, "%s", item);
    }
    wrefresh(w); 
 
    i = 0;
    noecho();
    keypad(w, TRUE); 
    curs_set(0); 
     
    while((ch = wgetch(w)) != 'q'){ 
            sprintf(item, "%-12s",  list[i]); 
            mvwprintw(w, i+1, 2, "%s", item); 
            switch(ch) {
                case KEY_UP:
                            i--;
                            i = (i < 0) ? 4 : i;
                            break;
                case KEY_DOWN:
                            i++;
                            i = (i > 4) ? 0 : i;
                            break;
                case KEY_ENTER:
                            if(i == 3) break;            }
            wattron(w, A_STANDOUT);
            sprintf(item, "%-12s",  list[i]);
            mvwprintw(w, i+1, 2, "%s", item);
            wattroff(w, A_STANDOUT);
    }
 
    delwin(w);
    endwin();
}

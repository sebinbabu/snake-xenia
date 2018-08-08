#include <string.h>
#include <ncurses.h>

#include "game.h"
#include "snake.h"
#include "food.h"
#include "obstacle.h"
#include "board.h"
#include "node.h"

void initBoard(board *b, int r, int c) {
	b->r = r;
	b->c = c;
}

void updateBoard(game *g) {
	board *b = g->b;
	snake *s = g->s;
	food *f = g->f;
	obstacle *o = g->o;

	memset((char*) b->b, ' ', 10000);
	
	pasteSnake(b, s);
	pasteFood(b, f);
	while(o != NULL) {
		pasteObstacle(g->b, o);
		o = o->next;
	}
}

void displayBoard(game *g) {
	board *b = g->b;
	int i, j;
	for(i = 0; i < b->c + 2; i++)
		addch('-');
	addch('\n');

	for(i = 0; i < b->r; i++) {
		addch('|');
		for(j = 0; j < b->c; j++) {
			addch(b->b[i][j]);
		}
		addch('|');
		addch('\n');
	}
	for(i = 0; i < b->c + 2; i++) addch('-');
	addch('\n');
	printw("SCORE: %d | LEVEL: %d", g->score, (g->score / 5) + 1);
}

void deleteBoard(board *b) {
	memset((char*) b->b, ' ', 10000);
}
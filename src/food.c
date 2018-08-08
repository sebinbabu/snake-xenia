#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "food.h"

void initFood(food *f, int r, int c) {
	srand(time(0));
	f->x = rand() % r;
	f->y = rand() % c;
	f->f = 'x';
}

void pasteFood(board *b, food *f) {
	b->b[f->x][f->y] = f->f;
}

void setupFood(game *g) {
	while(1) {
		initFood(g->f, g->b->r, g->b->c);
		if(g->b->b[g->f->x][g->f->y] == ' ') 
			break;
	}
	pasteFood(g->b, g->f);
}
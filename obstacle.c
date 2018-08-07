#include <stdlib.h>
#include <time.h>

#include "obstacle.h"
#include "node.h"
#include "board.h"
#include "game.h"

obstacle* createObstacleSquare(int r, int c, char f, obstacle *next) {
	node *t = createNode(r - 1, c + 1, '+', NULL);
	t = createNode(r, c + 1, '+', t);
	t = createNode(r + 1, c + 1, '+', t);
	t = createNode(r + 1, c, '+', t);
	t = createNode(r + 1, c - 1, '+', t);
	t = createNode(r, c - 1, '+', t);
	t = createNode(r - 1, c - 1, '+', t);
	t = createNode(r - 1, c, '+', t);
	t = createNode(r, c, '+', t);

	// + + +
	// +   + creates this obstacle
	// + + +
	
	obstacle *o = (obstacle*) malloc(sizeof(obstacle));
	o->h = t;
	o->next = next;
	return o;
}

void setupObstacleSquare(game *g) {
	int r, c;
	board *b = g->b;
	srand(time(0));
	while(1) {
		r = (rand() % (b->r - 2)) + 1;
		c = (rand() % (b->c - 2)) + 1;
		if(b->b[r][c] == ' ' && b->b[r - 1][c + 1] == ' ' && b->b[r][c + 1] == ' '
			&& b->b[r + 1][c + 1] == ' ' && b->b[r + 1][c] == ' ' && b->b[r + 1][c - 1] == ' '
			 && b->b[r][c - 1] == ' ' && b->b[r - 1][c - 1] == ' ' && b->b[r - 1][c] == ' ')
			break;
	}
	g->o = createObstacleSquare(r, c, '+', g->o);
}

#include <ncurses.h>
#include <stdlib.h>

#include "snake.h"
#include "game.h"
#include "food.h"
#include "board.h"
#include "node.h"
#include "obstacle.h"

void initSnake(snake *s, int r, int c) {
	node *t = createNode(r / 2, (c / 2) + 2, '@', NULL); 
	s->h = t;
	t = createNode(r / 2, (c / 2) + 1, '#', t);
	
	s->last_x = t->x, s->last_y = t->y;

	t = createNode(r / 2,  c / 2, '#', t);
	t = createNode(r / 2, (c / 2) - 1, '#', t);
	t = createNode(r / 2, (c / 2) - 2, 'o', t);
	
	s->t = t;
}

int moveSnake(game *g, int m) {
	snake *s = g->s;
	food *f = g->f;
	board *b = g->b;

	int r = b->r, c = b->c, ox, oy, nx, ny;

	node *h = s->h, *t = s->t;

	switch(m) {
		case KEY_UP: ox = -1, oy = 0; break; //UP
		case KEY_RIGHT: ox = 0, oy = 1; break; //RIGHT
		case KEY_DOWN: ox = 1, oy = 0; break; //DOWN
		case KEY_LEFT: ox = 0, oy = -1; break; //LEFT
		default: ox = h->x - s->last_x, oy = h->y - s->last_y;
	}
	nx = h->x + ox;
	nx = (r + (nx % r)) % r;
	ny = h->y + oy;
	ny = (c + (ny % c)) % c;

	if(s->last_x == nx && s->last_y == ny) return -1;	
	if(b->b[nx][ny] == '#') return 0;
	
	s->last_x = h->x, s->last_y = h->y;
	h->f = '#';
	h->next = createNode(nx, ny, '@', NULL);;
	s->h = h->next;
	if(nx == f->x && ny == f->y) {
		
		g->score++;
		if(g->speed > 55000) 
			g->speed -= 10000; 

		while(1) {
			initFood(f, r, c);
			if(b->b[f->x][f->y] == ' ') 
				break;
		}
		setupObstacleSquare(g);
		
	}
	else {
		s->t = t->next;
		s->t->f = 'o';
		free(t);
	}
	return 1;
}
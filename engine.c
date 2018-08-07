#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include "engine.h"

node* createNode(int r, int c, char f, node *next) {
	node *t = (node*) malloc(sizeof(node));
	t->x = r, t->y = c, t->f = f, t->next = next;
	return t;
}

void initBoard(board *b, int r, int c) {
	b->r = r;
	b->c = c;
}

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

void initFood(food *f, int r, int c) {
	srand(time(0));
	f->x = rand() % r;
	f->y = rand() % c;
	f->f = 'x';
}

void initGame(game *g, int r, int c) {
	initSnake(g->s, r, c);
	initBoard(g->b, r, c);
	// while(1) {
	// 	initFood(f, r, c);
	// 	if(b->b[f->x][f->y] == ' ')
	// 		break;
	// }
	initFood(g->f, r, c);
	g->score = 0;
	g->speed = 250000;
}


void updateBoard(game *g) {
	board *b = g->b;
	snake *s = g->s;
	food *f = g->f;

	memset((char*) b->b, ' ', 10000);
	
	node *t = s->t;
	while(t != NULL) {
		b->b[t->x][t->y] = t->f;
		t = t->next;
	}

	b->b[f->x][f->y] = f->f;
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
	printw("SCORE: %d", g->score);
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
		if(g->speed > 60000 && g->score / 5 > (g->score - 1) / 5) 
			g->speed -= 50000; 

		while(1) {
			initFood(f, r, c);
			if(b->b[f->x][f->y] == ' ') 
				break;
		}
	}
	else {
		s->t = t->next;
		s->t->f = 'o';
		free(t);
	}
	return 1;
}

void pauseGame(game *g) {
	usleep(g->speed);
}


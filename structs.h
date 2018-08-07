#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct NODE {
	int x, y;
	char f;
	struct NODE *next;
} node;

typedef struct BOARD {
	int r, c;
	char b[100][100];
} board;

typedef struct OBSTACLE {
	node *h;
	struct OBSTACLE *next;
} obstacle;

typedef struct FOOD {
	int x, y;
	char f;
} food;

typedef struct SNAKE {
	node *h, *t;
	int last_x, last_y;
} snake;

typedef struct GAME {
	snake *s;
	board *b;
	food *f;
	obstacle *o;
	int speed;
	int score;
} game;

#endif
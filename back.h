#ifndef BACK_H
#define BACK_H

typedef struct NODE {
	int x, y;
	char f;
	struct NODE *next;
} node;

typedef struct SNAKE {
	node *h, *t;
	int last_x, last_y;
} snake;

typedef struct FOOD {
	int x, y;
	char f;
} food;

typedef struct BOARD {
	int r, c;
	char b[100][100];
} board;

typedef struct GAME {
	snake *s;
	board *b;
	food *f;
} game;

node* createNode(int r, int c, char f, node *next);
void initBoard(board *b, int r, int c);
void initSnake(snake *s, int r, int c);
void initFood(food *f, int r, int c);
void initGame(game *g, int r, int c);
void initScreen();
void updateBoard(game *g);
void displayBoard(game *g);
int moveSnake(game *g, int m);

#endif
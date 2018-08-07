#include <unistd.h>

#include "game.h"
#include "snake.h"
#include "board.h"
#include "food.h"

void initGame(game *g, int r, int c, int speed) {
	initSnake(g->s, r, c);
	initBoard(g->b, r, c);
	// while(1) {
	// 	initFood(f, r, c);
	// 	if(b->b[f->x][f->y] == ' ')
	// 		break;
	// }
	initFood(g->f, r, c);
	g->score = 0;
	g->speed = speed;
	g->o = NULL;
}

void pauseGame(game *g) {
	usleep(g->speed);
}
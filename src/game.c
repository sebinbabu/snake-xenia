#include <unistd.h>

#include "game.h"
#include "snake.h"
#include "board.h"
#include "save.h"
#include "food.h"
#include "obstacle.h"

void initGame(game *g, int r, int c, int speed, int quantum) {
	initSnake(g->s, r, c);
	initBoard(g->b, r, c);
	initFood(g->f, (r / 2) - 1, c);
	g->score = 0;
	g->speed = speed;
	g->quantum = quantum;
	g->o = NULL;
}

void pauseGame(game *g) {
	usleep(g->speed);
}

int saveGame(game *g) {
	return initSave(g);
}

int loadGame(game *g) {
	return initLoad(g);
}

void deleteGame(game *g) {
	deleteSnake(g->s);
	deleteObstacle(g->o);
	deleteBoard(g->b);
}
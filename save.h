#ifndef SAVE_H
#define SAVE_H

#include "game.h"

typedef struct METASAVE {
	int score;
	int speed;
	int quantum;
} metasave;

typedef struct SAVENODE {
	int x, y;
	char f;
} savenode;

void initSave(game *g);		

#endif
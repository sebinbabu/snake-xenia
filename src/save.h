#ifndef SAVE_H
#define SAVE_H

#include "game.h"

typedef struct METASAVE {
	int score;
	int speed;
	int quantum;
	int last_x, last_y;
	int r, c;
} metasave;

typedef struct SAVENODE {
	int x, y;
	char f;
} savenode;

int initSave(game *g);		
int initLoad(game *g);

savenode createSaveNode(node *n);

#endif
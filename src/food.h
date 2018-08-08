#ifndef FOOD_H
#define FOOD_H

#include "structs.h"

void initFood(food *f, int r, int c);
void pasteFood(board *b, food *f);
void setupFood(game *g);

#endif
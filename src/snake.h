#ifndef SNAKE_H
#define SNAKE_H

#include "structs.h"

void initSnake(snake *s, int r, int c);
int moveSnake(game *g, int m);
void pasteSnake(board *b, snake *s);
void deleteSnake(snake *s);

#endif
#ifndef GAME_H
#define GAME_H

#include "structs.h"
#include "board.h"
#include "snake.h"

void initGame(game *g, int r, int c, int speed);
void pauseGame(game *g);

#endif
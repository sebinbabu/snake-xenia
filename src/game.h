#ifndef GAME_H
#define GAME_H

#include "structs.h"
#include "board.h"
#include "snake.h"

void initGame(game *g, int r, int c, int speed, int quantum);
void pauseGame(game *g);
int saveGame(game *g);
int loadGame(game *g);
void deleteGame(game *g);

#endif
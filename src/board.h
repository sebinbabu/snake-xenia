#ifndef BOARD_H
#define BOARD_H

#include "structs.h"

void initBoard(board *b, int r, int c);
void updateBoard(game *g);
void displayBoard(game *g);
void deleteBoard(board *g);

#endif
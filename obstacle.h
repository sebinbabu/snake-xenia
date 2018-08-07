#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "structs.h"

obstacle* createObstacleSquare(int r, int c, char f, obstacle *next);
void setupObstacleSquare(game *g);
void pasteObstacle(board *b, obstacle *o);

#endif
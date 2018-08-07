#include <time.h>
#include <unistd.h>

#include "food.h"

void initFood(food *f, int r, int c) {
	srand(time(0));
	f->x = rand() % r;
	f->y = rand() % c;
	f->f = 'x';
}
#include <malloc.h>
#include "node.h"

node* createNode(int r, int c, char f, node *next) {
	node *t = (node*) malloc(sizeof(node));
	t->x = r, t->y = c, t->f = f, t->next = next;
	return t;
}
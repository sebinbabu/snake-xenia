#include <stdio.h>
#include <ncurses.h>

#include "save.h"
#include "structs.h"

savenode createSaveNode(node *n) {
	savenode s = {n->x, n->y, n->f};
	return s;
}

void initSave(game *g) {
	node del = {-1, -1, -1, NULL};
	metasave m = {g->score, g->speed, g->quantum};
	savenode sav[100];
	int i = 0, max = 100;
	node *t;	
	FILE *out;

	out = fopen("SAVEFILE", "wb");
	if(out == NULL) {
		printw("ERROR WRITING FILE");
		return;
	}

	fwrite(&m, sizeof(metasave), 1, out);

	t = g->s->t;
	while(t != NULL) {
		if(i < max)
			sav[i++] = createSaveNode(t);
		else {
			fwrite(sav, sizeof(metasave), i, out);
			i = 0;
			sav[i++] = createSaveNode(t);
		}
		t = t->next;
	}

	sav[i++] = createSaveNode(&del);

	obstacle *o = g->o;
	while(o != NULL) {
		t = o->h;
		while(t != NULL) {
			if(i < max)
				sav[i++] = createSaveNode(t);
			else {
				fwrite(sav, sizeof(metasave), i, out);
				i = 0;
				sav[i++] = createSaveNode(t);
			}
			t = t->next;
		}
	}


}


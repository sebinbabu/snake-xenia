#include <stdio.h>
#include <ncurses.h>

#include "save.h"
#include "structs.h"

savenode createSaveNode(node *n) {
	savenode s = {n->x, n->y, n->f};
	return s;
}

int initSave(game *g) {
	node del = {-1, -1, -1, NULL}, f = {g->f->x, g->f->y, g->f->f};
	metasave m = {g->score, g->speed, g->quantum, g->s->last_x, g->s->last_y, g->b->r, g->b->c};
	savenode sav[100];
	int i = 0, max = 100;
	node *t;	
	FILE *out;

	out = fopen("SAVEFILE", "wb");
	if(out == NULL)
		return 0;

	if(fwrite(&m, sizeof(metasave), 1, out) != 1) {
		fclose(out);
		return 0;
	}

	sav[i++] = createSaveNode(&f);

	t = g->s->t;
	while(t != NULL) {
		if(i < max)
			sav[i++] = createSaveNode(t);
		else {
			if(fwrite(sav, sizeof(savenode), i, out) != i) {
				fclose(out);
				return 0;
			}
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
				if(fwrite(sav, sizeof(savenode), i, out) != i) {
					fclose(out);
					return 0;
				}
				i = 0;
				sav[i++] = createSaveNode(t);
			}
			t = t->next;
		}
		sav[i++] = createSaveNode(&del);
		o = o->next;
	}
	if(i > 0) {
		if(fwrite(sav, sizeof(savenode), i, out) != i) {
			fclose(out);
			return 0;
		}
	}
	fclose(out);
	return 1;
}

int initLoad(game *g) {
	//TODO : write load code here
	return 0;
}


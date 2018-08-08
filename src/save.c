#include <stdio.h>
#include <ncurses.h>

#include "save.h"
#include "structs.h"
#include "node.h"

savenode createSaveNode(node *n) {
	savenode s = {n->x, n->y, n->f};
	return s;
}

int isDelemiter(savenode *n) {
	return n->x == -1
			&& n->y == -1 
			&& n->f == -1;
}

int initSave(game *g) {
	node del = {-1, -1, -1, NULL}, f = {g->f->x, g->f->y, g->f->f};
	metasave m = {g->score, g->speed, g->quantum, g->s->last_x, g->s->last_y, g->b->r, g->b->c, 0};
	savenode sav[100];
	int i = 0, records = 0, max = 100;
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
			records += i;
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
				records += i;
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
		records += i;
	}
	
	m.records = records;
	fseek(out, SEEK_SET, 0);
	if(fwrite(&m, sizeof(metasave), 1, out) != 1) {
		fclose(out);
		return 0;
	}

	fclose(out);
	return 1;
}

int initLoad(game *g) {
	// deleteGame(g);
	metasave m;
	int i = 0;
//	long int size;
	node *t;
	FILE *in;
	in = fopen("SAVEFILE", "rb");

	if(in == NULL)
		return 0;

	if(fread(&m, sizeof(metasave), 1, in) != 1) {
		fclose(in);
		return 0;
	}
	savenode s[m.records];
	if(fread(s, sizeof(savenode), m.records, in) != m.records) {
		fclose(in);
		return 0;
	}


	g->speed = m.speed;
	g->score = m.score;
	g->quantum = m.quantum;

	g->f->x = s[0].x;
	g->f->y = s[0].y;
	g->f->f = s[0].f;
    
    i = 1;
    t = createNode(s[1].x, s[1].y, s[1].f, NULL);
    g->s->t = t;
	while(!isDelemiter(s + i) && i < m.records) {
	    t->next = createNode(s[i].x, s[i].y, s[i].f, NULL);
	    t = t->next;
	    i++;
	}
	g->s->h = t;
	g->s->last_x = m.last_x;
	g->s->last_y = m.last_y;

	g->b->r = m.r;
	g->b->c = m.c;

	return 1;
}


// #include "save.h"
// #include "structs.h"

// void initSave(game *g) {
// 	metasave m = {g->score, g->speed, g->quantum};
// 	int s = 0, max = 100;
// 	node *t;	
// 	FILE *out;
// 	out = fopen("SAVEFILE", "w");
// 	if(out == NULL) {
// 		printw("ERROR WRITING FILE");
// 		return;
// 	}
// 	savenode sav[100];

// 	fwrite(&m, sizeof(metasave), 1, out);
// 	t = g->s->t;
// 	while(t != NULL) {
		
// 	}
// }


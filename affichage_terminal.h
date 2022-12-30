#ifndef _AFFICHAGE_TERMINAL
#define _AFFICHAGE_TERMINAL 0

typedef struct _grid grid;
typedef struct _game game;

void print_grid_terminal(grid *g);
int round_human_terminal(void);

#endif
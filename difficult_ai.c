#include "difficult_ai.h"

#include <stdio.h>
#include <stdlib.h>

extern error;
int has_winning_move(grid* g) { return 0; }

int find_winning_move(grid* g) { return 0; }

int get_number_aligns(grid* g) { return 0; }

int find_longest_align(grid* g) { return 0; }

int find_best_move(grid* g) { return 0; }

// Idée :
// Parcourir la grille, pour chaque pion de couleur c, vérifier les 3 case a
// gauche, au dessus, en dessous, a droite, et dans les diagonales.
void parcourt(grid* g) {
  if (!g) {
    error = NO_GRID_ERROR;
    return;
  }
  int i, j, k;
  for (i = 0; i < NB_COL; i++) {
    for (j = 0; j < NB_LINES; j++) {
    }
  }
}
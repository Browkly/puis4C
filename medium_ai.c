#include "medium_ai.h"

#include <stdio.h>
#include <stdlib.h>

extern error;

// param p => le joueur précédent l'ia
int get_vertical_align(grid* g, player* p) {
  // Gestion des erreurs à implémenter
  int x = p->last_x;
  int y = p->last_y;
  int color = p->number_player;
  int length = 0;

  while (y >= 0) {
    if (color == g->g[x][y]) {
      length++;
      y++;
    } else {
      return length;
    }
  }
  return length;
}

int get_horizontal_align(grid* g, player* p) {
  // Gestion des erreurs à implémenter
  int x = p->last_x;
  int y = p->last_y;
  int color = p->number_player;
  int length = 0;
  int align = 1;
  // Gérer les cas où on dépasse les limites de la grille
  // On part du x du dernier coup
  // Parcourt à gauche du dernier coup
  while (x >= 0 && align == 1) {
    if (color == g->g[x][y]) {
      length++;
      x++;
    } else {
      align = 0;
    }
  }
  // Gérer les cas où on dépasse les limites de la grille
  // On se place à droite du x du dernier coup
  // Parcourt à droite du dernier coup:
  x = p->last_x + 1;
  while (x <= NB_COL) {
    if (color == g->g[x][y]) {
      length++;
      x++;
    } else {
      return length;
    }
  }
  return length;
}

int get_left_diagonal_align(grid* g, player* p) {
  // Gestion des erreurs à implémenter
  int x = p->last_x;
  int y = p->last_y;
  int color = p->number_player;
  int length = 0;
  int align = 1;
  // Parcourt à gauche au dessus
  while (x >= 0 && y >= 0 && align == 1) {
    if (color == g->g[x][y]) {
      length++;
      x--;
      y--;
    } else {
      align = 0;
    }
  }
  x = p->last_x + 1;
  y = p->last_y + 1;
  // Parcourt à droite en dessous
  while (x < NB_COL && y < NB_LINES && align == 1) {
    if (color == g->g[x][y]) {
      length++;
      x++;
      y++;
    } else {
      return length;
    }
  }
  return 0;
}

int get_right_diagonal_align(grid* g, player* p) {
  // Gestion des erreurs à implémenter
  int x = p->last_x;
  int y = p->last_y;
  int color = p->number_player;
  int length = 0;
  int align = 1;
  // Parcourt à gauche au dessous
  while (x >= 0 && y < NB_LINES && align == 1) {
    if (color == g->g[x][y]) {
      length++;
      x--;
      y++;
    } else {
      align = 0;
    }
  }
  x = p->last_x + 1;
  y = p->last_y - 1;
  // Parcourt à droite au dessus
  while (x < NB_COL && y >= 0 && align == 1) {
    if (color == g->g[x][y]) {
      length++;
      x++;
      y--;
    } else {
      return length;
    }
  }
  return 0;
}

// Return 0 if no align
// Return 1 if vertical align
// Return 2 if horizontal align
// Returns 3 if left diagonal align
// Returns 4 if right diagonal align
int find_biggest_align(grid* g, player* p) { return 0; }

// Return 1 if the choice is valid for the ai to play a move
int is_valid(grid* g, player* p, int x, int y) { return 0; }

int is_reachable(grid* g, int x, int y) { return 0; }

int is_left_border_horizontal_align_reachable(grid* g, player* p) { return 0; }

int is_right_border_horizontal_align_reachable(grid* g, player* p) { return 0; }

int is_left_left_diagonal_align_reachable(grid* g, player* p) { return 0; }

int is_right_left_horizontal_align_reachable(grid* g, player* p) { return 0; }

int is_left_right_diagonal_align_reachable(grid* g, player* p) { return 0; }

int is_right_right_horizontal_align_reachable(grid* g, player* p) { return 0; }
#include "medium_ai.h"

#include <stdio.h>
#include <stdlib.h>

#include "easy_ai.h"

int extern error;

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
// Returns the direction of the biggest align created by enemy player's last
// move
// Returns 0 if no align
// Returns 1 if vertical align
// Returns 2 if horizontal align
// Returns 3 if left diagonal align
// Returns 4 if right diagonal align
int find_biggest_align(grid* g, player* p) {
  int l1, l2, l3, l4;
  l1 = get_vertical_align(g, p);
  l2 = get_horizontal_align(g, p);
  l3 = get_left_diagonal_align(g, p);
  l4 = get_right_diagonal_align(g, p);
  if (l1 == 0 && l2 == 0 && l3 == 0 && l4 == 0) {
    return 0;
  }
  if (l1 >= l2 && l1 >= l3 && l1 >= l4) {
    return 1;
  }
  if (l2 >= l3 && l2 >= l4) {
    return 2;
  }
  if (l3 >= l4) {
    return 3;
  }
  return 4;
}

// Return 1 if the choice is valid for the ai to play a move
int is_valid(grid* g, player* p, int x) {
  if (0 <= x && x < NB_COL && g->g[x][NB_LINES - 1] == 0) {
    return 1;
  }
  return 0;
}

// Returns 1 if the tile is reachable, 0 else.
int is_reachable(grid* g, player* p, int x, int y) {
  if (y == 0 || g->g[x][y - 1] != 0 && is_valid(g, p, x)) {
    return 1;
  }
  return 0;
}

// Return if the tile adjacent to the align is reachable or not so the ai should
// or not defend
int is_left_border_horizontal_align_reachable(grid* g, player* p) {
  // Gérer les erreurs possibles
  int x = p->last_x;
  while (x > 0 && g->g[x][p->last_y] == p->number_player) {
    // Tant que la case a gauche est du meme joueur et sup a 0 => on décale a
    // gauche
    x--;
  }
  return is_reachable(g, p, x, p->last_y);
}

// Return if the tile adjacent to the align is reachable or not so the ai should
// or not defend
int is_right_border_horizontal_align_reachable(grid* g, player* p) {
  // Gérer les erreurs possibles
  int x = p->last_x;
  while (x < NB_COL && g->g[x][p->last_y] == p->number_player) {
    // Tant que la case a gauche est du meme joueur et sup a 0 => on décale a
    // gauche
    x++;
  }
  return is_reachable(g, p, x, p->last_y);
}

// Return if the tile adjacent to the align is reachable or not so the ai should
// or not defend
int is_left_left_diagonal_align_reachable(grid* g, player* p) {
  // Gérer les erreurs possibles
  int x = p->last_x;
  int y = p->last_y;
  // Tant que x > 0 et y
  while (x > 0 && y > 0 && g->g[x][y] == p->number_player) {
    x--;
    y--;
  }
  return is_reachable(g, p, x, y);
}

// Return if the tile adjacent to the align is reachable or not so the ai should
// or not defend
int is_right_left_horizontal_align_reachable(grid* g, player* p) {
  // Gérer les erreurs possibles
  int x = p->last_x;
  int y = p->last_y;
  while (x < NB_COL && y < NB_LINES && g->g[x][y] == p->number_player) {
    x++;
    y++;
  }
  return is_reachable(g, p, x, y);
}

// Return if the tile adjacent to the align is reachable or not so the ai should
// or not defend
int is_left_right_diagonal_align_reachable(grid* g, player* p) {
  // Gérer les erreurs possibles
  int x = p->last_x;
  int y = p->last_y;
  // Tant que x > 0 et y
  while (x > 0 && y < NB_LINES && g->g[x][y] == p->number_player) {
    x--;
    y++;
  }
  return is_reachable(g, p, x, y);
}

// Return if the tile adjacent to the align is reachable or not so the ai should
// or not defend
int is_right_right_horizontal_align_reachable(grid* g, player* p) {
  // Gérer les erreurs possibles
  int x = p->last_x;
  int y = p->last_y;
  // Tant que x > 0 et y
  while (x < NB_COL && y > 0 && g->g[x][y] == p->number_player) {
    x++;
    y--;
  }
  return is_reachable(g, p, x, y);
}

// Returns the left border of the align if it is reachable, else, returns -1
int get_left_border_horizontal_align(grid* g, player* p) {
  int x = p->last_x;
  int y = p->last_y;
  if (is_left_border_horizontal_align_reachable(g, p) == 1) {
    while (x > 0 && g->g[x][y] == p->number_player) {
      x--;
    }
    if (is_reachable(g, p, x, y) == 1) {
      return x;
    } else {
      return -1;
    }
  }
  return -1;
}

// Returns the right border of the align if it is reachable, else, returns -1
int get_right_border_horizontal_align(grid* g, player* p) {
  int x = p->last_x;
  int y = p->last_y;
  if (is_left_border_horizontal_align_reachable(g, p) == 1) {
    while (x < NB_COL && g->g[x][y] == p->number_player) {
      x++;
    }
    if (is_reachable(g, p, x, y) == 1) {
      return x;
    } else {
      return -1;
    }
  }
  return -1;
}

// Returns the left border of the align if it is reachable, else, returns -1
int get_left_border_left_diagonal(grid* g, player* p) {
  int x = p->last_x;
  int y = p->last_y;
  if (is_left_border_horizontal_align_reachable(g, p) == 1) {
    while (x > 0 && y > 0 && g->g[x][y] == p->number_player) {
      x--;
      y--;
    }
    if (is_reachable(g, p, x, y) == 1) {
      return x;
    } else {
      return -1;
    }
  }
  return -1;
}

// Returns the right border of the align if it is reachable, else, returns -1
int get_right_border_left_diagonal(grid* g, player* p) {
  int x = p->last_x;
  int y = p->last_y;
  if (is_left_border_horizontal_align_reachable(g, p) == 1) {
    while (x < NB_COL && y < NB_LINES && g->g[x][y] == p->number_player) {
      x++;
      y++;
    }
    if (is_reachable(g, p, x, y) == 1) {
      return x;
    } else {
      return -1;
    }
  }
  return -1;
}

// Returns the left border of the align if it is reachable, else, returns -1
int get_left_border_right_diagonal(grid* g, player* p) {
  int x = p->last_x;
  int y = p->last_y;
  if (is_left_border_horizontal_align_reachable(g, p) == 1) {
    while (x > 0 && y < NB_LINES && g->g[x][y] == p->number_player) {
      x--;
      y++;
    }
    if (is_reachable(g, p, x, y) == 1) {
      return x;
    } else {
      return -1;
    }
  }
  return -1;
}

// Returns the right border of the align if it is reachable, else, returns -1
int get_right_border_right_diagonal(grid* g, player* p) {
  int x = p->last_x;
  int y = p->last_y;
  if (is_left_border_horizontal_align_reachable(g, p) == 1) {
    while (x < NB_COL && y > 0 && g->g[x][y] == p->number_player) {
      x++;
      y--;
    }
    if (is_reachable(g, p, x, y) == 1) {
      return x;
    } else {
      return -1;
    }
  }
  return -1;
}

// Returns the column of the move selected by the medium difficulty ai, if the
// ai doesn't find any optimal move (with its definitions), a random one is
// selected
int get_medium_ai_move(grid* g, player* last_p) {
  int x = -1;
  // Gérer les erreurs possibles
  if (find_biggest_align(g, last_p) == 1) {
    // Cas d'alignement vertical
    if (is_column_full(g, last_p->last_x) == 0) {
      x = last_p->last_x;
    }
  } else if (find_biggest_align(g, last_p) == 2) {
    // Cas d'alignement horizontal
    if (is_left_border_horizontal_align_reachable(g, last_p) == 1) {
      // Placement d'un token à gauche de l'alignement si possible
      x = get_left_border_horizontal_align(g, last_p);
    }
    // Placement d'un token à droite de l'alignement si possible et si
    // l'alignement gauche est impossible
    else if (is_right_border_horizontal_align_reachable(g, last_p) == 1) {
      x = get_right_border_horizontal_align(g, last_p);
    }
  }
  // Cas d'alignement en diagonale gauche
  else if (find_biggest_align(g, last_p) == 3) {
    if (is_left_left_diagonal_align_reachable(g, last_p) == 1) {
      x = get_left_border_left_diagonal(g, last_p);
    } else if (is_right_left_horizontal_align_reachable(g, last_p) == 1) {
      x = get_right_border_left_diagonal(g, last_p);
    }
  }
  // Cas d'alignement en diagonale droite
  else if (find_biggest_align(g, last_p) == 4) {
    if (is_left_right_diagonal_align_reachable(g, last_p) == 1) {
      x = get_left_border_right_diagonal(g, last_p);
    } else if (is_right_right_horizontal_align_reachable(g, last_p) == 1) {
      x = get_right_border_right_diagonal(g, last_p);
    }
  }

  if (x == -1) {
    // return random move
    x = random_choice(g);
  }
  return x;
}
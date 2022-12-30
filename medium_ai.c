#include "medium_ai.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "easy_ai.h"
int extern error;

/**
 * @brief Return 1 if a vertical align with the color of the player in parameter
 * is found, 0 else
 * @param grid * g, player * p
 * @return int
 */
int get_vertical_align(grid* g, player* p) {
  // Gestion des erreurs à implémenter
  assert(g);
  assert(p);
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

/**
 * @brief Return 1 if a horizontal align with the color of the player in
 * parameter is found, 0 else
 * @param grid * g, player * p
 * @return int
 */
int get_horizontal_align(grid* g, player* p) {
  // Gestion des erreurs à implémenter
  assert(g);
  assert(p);
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

/**
 * @brief Return 1 if a left diagonal align with the color of the player in
 * parameter is found, 0 else
 * @param grid * g, player * p
 * @return int
 */
int get_left_diagonal_align(grid* g, player* p) {
  // Gestion des erreurs à implémenter
  assert(g);
  assert(p);
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

/**
 * @brief Return 1 if a right diagonal align with the color of the player in
 * parameter is found, 0 else
 * @param grid * g, player * p
 * @return int
 */
int get_right_diagonal_align(grid* g, player* p) {
  // Gestion des erreurs à implémenter
  assert(g);
  assert(p);
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

/**
 * @brief Returns the max between 4 ints, or 0 if they are all equal to each
 * other
 * @param int a, int b, int c, int d
 * @return int
 */
int get_max(int a, int b, int c, int d) {
  if (a == 0 && b == 0 && c == 0 && d == 0) {
    return 0;
  }
  if (a >= b && a >= c && a >= d) {
    return a;
  }
  if (b >= c && b >= d) {
    return b;
  }
  if (c >= d) {
    return c;
  }
  return d;
}

/**
 * @brief Return an int based of the direction of the biggest align, and if it
 * belongs to p1 or p2, return 0 if there is no align
 * @param grid * g, player * p, player * ai
 * @return int
 */
int find_biggest_align(grid* g, player* p, player* ai) {
  assert(g);
  assert(p);
  assert(ai);
  int p1, p2, p3, p4;
  int player_align = 0;
  int ai_align = 0;
  int ai1, ai2, ai3, ai4;
  // Alignements du joueur
  p1 = get_vertical_align(g, p);
  p2 = get_horizontal_align(g, p);
  p3 = get_left_diagonal_align(g, p);
  p4 = get_right_diagonal_align(g, p);
  // Alignemetns de l'ia
  ai1 = get_horizontal_align(g, ai);
  ai2 = get_vertical_align(g, ai);
  ai3 = get_left_diagonal_align(g, ai);
  ai4 = get_right_diagonal_align(g, ai);
  // Taking the biggest align of each player
  player_align = get_max(p1, p2, p3, p4);
  ai_align = get_max(ai1, ai2, ai3, ai4);
  if (player_align > ai_align) {
    return player_align;
  } else {
    return -1 * ai_align;
  }
}

/**
 * @brief Return 1 if the move at column x is valid, else return 0.
 * @param grid * g, player * p, int x
 * @return int
 */
int is_valid(grid* g, player* p, int x) {
  assert(g);
  assert(p);
  if (0 <= x && x < NB_COL && g->g[x][NB_LINES - 1] == 0) {
    return 1;
  }
  return 0;
}

/**
 * @brief Return 1 if the tile at coordinates (x, y) is reachable, else return
 * 0.
 * @param grid * g, player * p, int x, int y
 * @return int
 */
int is_reachable(grid* g, player* p, int x, int y) {
  assert(g);
  assert(p);
  if (y == 0 || g->g[x][y - 1] != 0 && is_valid(g, p, x)) {
    return 1;
  }
  return 0;
}

/**
 * @brief Return 1 if the column to the left of horizontal align is
 * reachable
 * @param grid * g, player * p
 * @return int
 */
int is_left_border_horizontal_align_reachable(grid* g, player* p) {
  assert(g);
  assert(p);
  // Gérer les erreurs possibles
  int x = p->last_x;
  while (x > 0 && g->g[x][p->last_y] == p->number_player) {
    // Tant que la case a gauche est du meme joueur et sup a 0 => on décale a
    // gauche
    x--;
  }
  return is_reachable(g, p, x, p->last_y);
}

/**
 * @brief Return 1 if the column to the right of horizontal align is
 * reachable
 * @param grid * g, player * p
 * @return int
 */
int is_right_border_horizontal_align_reachable(grid* g, player* p) {
  // Gérer les erreurs possibles
  assert(g);
  assert(p);
  int x = p->last_x;
  while (x < NB_COL && g->g[x][p->last_y] == p->number_player) {
    // Tant que la case a gauche est du meme joueur et sup a 0 => on décale a
    // gauche
    x++;
  }
  return is_reachable(g, p, x, p->last_y);
}

/**
 * @brief Return 1 if the column to the left of diagonal align is
 * reachable
 * @param grid * g, player * p
 * @return int
 */
int is_left_left_diagonal_align_reachable(grid* g, player* p) {
  // Gérer les erreurs possibles
  assert(g);
  assert(p);
  int x = p->last_x;
  int y = p->last_y;
  // Tant que x > 0 et y
  while (x > 0 && y > 0 && g->g[x][y] == p->number_player) {
    x--;
    y--;
  }
  return is_reachable(g, p, x, y);
}

/**
 * @brief Return 1 if the column to the right of diagonal align is
 * reachable
 * @param grid * g, player * p
 * @return int
 */
int is_right_left_horizontal_align_reachable(grid* g, player* p) {
  // Gérer les erreurs possibles
  assert(g);
  assert(p);
  int x = p->last_x;
  int y = p->last_y;
  while (x < NB_COL && y < NB_LINES && g->g[x][y] == p->number_player) {
    x++;
    y++;
  }
  return is_reachable(g, p, x, y);
}

/**
 * @brief Return 1 if the column to the left of diagonal align is
 * reachable
 * @param grid * g, player * p
 * @return int
 */
int is_left_right_diagonal_align_reachable(grid* g, player* p) {
  // Gérer les erreurs possibles
  assert(g);
  assert(p);
  int x = p->last_x;
  int y = p->last_y;
  // Tant que x > 0 et y
  while (x > 0 && y < NB_LINES && g->g[x][y] == p->number_player) {
    x--;
    y++;
  }
  return is_reachable(g, p, x, y);
}

/**
 * @brief Return 1 if the column to the right of diagonal align is
 * reachable
 * @param grid * g, player * p
 * @return int
 */
int is_right_right_horizontal_align_reachable(grid* g, player* p) {
  // Gérer les erreurs possibles
  assert(g);
  assert(p);
  int x = p->last_x;
  int y = p->last_y;
  // Tant que x > 0 et y
  while (x < NB_COL && y > 0 && g->g[x][y] == p->number_player) {
    x++;
    y--;
  }
  return is_reachable(g, p, x, y);
}

/**
 * @brief Returns the column of the left border of an horizontal align, or -1 is
 * unreachable
 * @param grid * g, player * p
 * @return int
 */
int get_left_border_horizontal_align(grid* g, player* p) {
  assert(g);
  assert(p);
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

/**
 * @brief Returns the column of the right border of an horizontal align, or -1
 * is unreachable
 * @param grid * g, player * p
 * @return int
 */
int get_right_border_horizontal_align(grid* g, player* p) {
  assert(g);
  assert(p);
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

/**
 * @brief Returns the column of the left border of a diagonal align, or -1 is
 * unreachable
 * @param grid * g, player * p
 * @return int
 */
int get_left_border_left_diagonal(grid* g, player* p) {
  assert(g);
  assert(p);
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

/**
 * @brief Returns the column of the right border of a diagonal align, or -1 is
 * unreachable
 * @param grid * g, player * p
 * @return int
 */
int get_right_border_left_diagonal(grid* g, player* p) {
  assert(g);
  assert(p);
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

/**
 * @brief Returns the column of the left border of a diagonal align, or -1 is
 * unreachable
 * @param grid * g, player * p
 * @return int
 */
int get_left_border_right_diagonal(grid* g, player* p) {
  assert(g);
  assert(p);
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

/**
 * @brief Returns the column of the right border of a diagonal align, or -1 is
 * unreachable
 * @param grid * g, player * p
 * @return int
 */
int get_right_border_right_diagonal(grid* g, player* p) {
  assert(g);
  assert(p);
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

/**
 * @brief Returns the column of the move selected by the medium difficulty ai,
 * if the ai doesn't find any optimal move (with its definitions), a random one
 * is selected
 * @param grid * g, player * last_p, player * ai
 * @return int
 */
int get_medium_ai_move(grid* g, player* last_p, player* ai) {
  assert(g);
  assert(p);
  assert(ai);
  int x = -1;
  // Gérer les erreurs possibles
  if (find_biggest_align(g, last_p, ai) == 0) {
    return random_choice(g);  // Coup aléatoire
  }
  if (find_biggest_align(g, last_p, ai) == 1) {
    // Cas d'alignement vertical du joueur
    if (is_column_full(g, last_p->last_x) == 0) {
      x = last_p->last_x;
    }
  } else if (find_biggest_align(g, last_p, ai) == 2) {
    // Cas d'alignement horizontal du joueur
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
  // Cas d'alignement en diagonale gauche du joueur
  else if (find_biggest_align(g, last_p, ai) == 3) {
    if (is_left_left_diagonal_align_reachable(g, last_p) == 1) {
      x = get_left_border_left_diagonal(g, last_p);
    } else if (is_right_left_horizontal_align_reachable(g, last_p) == 1) {
      x = get_right_border_left_diagonal(g, last_p);
    }
  }
  // Cas d'alignement en diagonale droite du joueur
  else if (find_biggest_align(g, last_p, ai) == 4) {
    if (is_left_right_diagonal_align_reachable(g, last_p) == 1) {
      x = get_left_border_right_diagonal(g, last_p);
    } else if (is_right_right_horizontal_align_reachable(g, last_p) == 1) {
      x = get_right_border_right_diagonal(g, last_p);
    }
  }
  // Implémenter les cas ou l ia possède l'alignement le plus grand:
  if (find_biggest_align(g, last_p, ai) == -1) {
    // Cas d'alignement vertical AI
    if (is_column_full(g, ai->last_x) == 0) {
      x = ai->last_x;
    }
  } else if (find_biggest_align(g, last_p, ai) == -2) {
    // Cas d'alignement horizontal AI
    if (is_left_border_horizontal_align_reachable(g, ai) == 1) {
      x = get_left_border_horizontal_align(g, ai);
    }
    // Placement d'un token à droite de l'alignement si possible
    else if (is_right_border_horizontal_align_reachable(g, ai) == 1) {
      x = get_right_border_horizontal_align(g, ai);
    }
  }
  // Cas d'alignement en diagonale gauche AI
  else if (find_biggest_align(g, last_p, ai) == -3) {
    if (is_left_left_diagonal_align_reachable(g, ai) == 1) {
      x = get_left_border_left_diagonal(g, ai);
    } else if (is_right_left_horizontal_align_reachable(g, ai) == 1) {
      x = get_right_border_left_diagonal(g, ai);
    }
  }
  // Cas d'alignement en diagonale droite AI
  else if (find_biggest_align(g, last_p, ai) == -4) {
    if (is_left_right_diagonal_align_reachable(g, ai) == 1) {
      x = get_left_border_right_diagonal(g, ai);
    } else if (is_right_right_horizontal_align_reachable(g, ai) == 1) {
      x = get_right_border_right_diagonal(g, ai);
    }
  }
  return x;
}
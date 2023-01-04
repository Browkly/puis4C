#include "difficult_ai.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "jeu.h"

/**
 * @brief Returns the column of the best move possible with the current game
 * state, for the ally player.
 * @param grid * g, player * ally, player * enemy
 * @return int
 */
int difficult_ai_move(grid* g, player* ally, player* enemy) {
  int best_score = -1000;
  int best_move = 0;
  int i, j;
  for (i = 0; i < NB_COL; i++) {
    for (j = 0; j < NB_LINES; j++) {
      if (g->g[j][i] == 0 && (j > 0 || g->g[j - 1][i] != 0)) {
        // Case vide n'ayant pas une case vide en dessous d'elle : coup possible
        g->g[j][i] = ally->number_player;
        int score = minimax(g, 0, ally, enemy);
        g->g[j][i] = 0;
        if (score > best_score) {
          best_score = score;
          best_move = i;
        }
      }
    }
  }
  return i;
}

/**
 * @brief This function uses the minimax algorithm to look for the best move
 * playable by the ai. It finds the best move by increasing and decreasing a
 * score, regarding the consequences of a given move.
 * @param grid * g, int is_maximizing, player * ally, player * enemy
 * @return int
 */
int minimax(grid* g, int is_maximizing, player* ally, player* enemy) {
  // check if the AI can win:
  if (check_win(g, ally) == 1) {
    return 100;
  }

  // if the enemy of the AI can win
  if (check_win(g, enemy) == 1) {
    return -100;
  }
  // If draw
  if (g->full_case == 42 && check_win(g, ally) == 0 &&
      check_win(g, enemy) == 0) {
    return 0;
  }

  if (is_maximizing == 1) {
    // If maximizing (Best possible move for the ai)
    int best_score = -1000;
    for (int i = 0; i < NB_COL; i++) {
      for (int j = 0; j < NB_LINES; j++) {
        if (g->g[j][i] == 0 && (j > 0 || g->g[j - 1][i] != 0)) {
          // Case vide n'ayant pas une case vide en dessous d'elle : coup
          // possible
          g->g[j][i] = ally->number_player;
          int score = minimax(g, 0, ally, enemy);
          g->g[j][i] = 0;
          if (score > best_score) {
            best_score = score;
          }
        }
      }
    }
    return best_score;
  }
  if (is_maximizing == 0) {
    // If minimizing (finding Best possible move for the enemy of the ai)
    int best_score = 900;
    for (int i = 0; i < NB_COL; i++) {
      for (int j = 0; j < NB_LINES; j++) {
        if (g->g[j][i] == 0 && (j > 0 || g->g[j - 1][i] != 0)) {
          g->g[j][i] = enemy->number_player;
          int score = minimax(g, 1, ally, enemy);
          g->g[j][i] = 0;
          if (score < best_score) {
            best_score = score;
          }
        }
      }
    }
    return best_score;
  }
}

/**
 * @brief Returns 1 if the player has a vertical align at given coordinates, 0
 * else
 * @param grid * g, player * p, int x, int y
 * @return int
 */
int vertical_align(grid* g, player* p, int x, int y) {
  if ((y + 3) < NB_LINES && g->g[y][x] == p->number_player && g->g[y + 1][x] &&
      g->g[y + 2][x] == p->number_player &&
      g->g[y + 3][x] == p->number_player) {
    return 1;
  }
  return 0;
}

/**
 * @brief Returns 1 if the player has a horizontal align at given coordinates, 0
 * else
 * @param grid * g, player * p, int x, int y
 * @return int
 */
int horizontal_align(grid* g, player* p, int x, int y) {
  if ((x + 3) < NB_COL && g->g[y][x] == p->number_player &&
      g->g[y][x + 1] == p->number_player &&
      g->g[y][x + 2] == p->number_player &&
      g->g[y][x + 3] == p->number_player) {
    return 1;
  }
  return 0;
}

/**
 * @brief Returns 1 if the player has a left diagonal align at given
 * coordinates, 0 else
 * @param grid * g, player * p, int x, int y
 * @return int
 */
int left_diagonal_align(grid* g, player* p, int x, int y) {
  if ((x + 3) < NB_COL && (y - 3) >= 0 && g->g[x][y] == p->number_player &&
      g->g[x + 1][y - 1] == p->number_player &&
      g->g[x + 2][y - 2] == p->number_player &&
      g->g[x + 3][y - 3] == p->number_player) {
    return 1;
  }
  return 0;
}

/**
 * @brief Returns 1 if the player has a right diagonal align at given
 * coordinates, 0 else
 * @param grid * g, player * p, int x, int y
 * @return int
 */
int right_diagonal_align(grid* g, player* p, int x, int y) {
  if ((x - 3) >= 0 && (y - 3 >= 0) && g->g[x][y] == p->number_player &&
      g->g[x - 1][y - 1] == p->number_player &&
      g->g[x - 2][y - 2] == p->number_player &&
      g->g[x - 3][y - 3] == p->number_player) {
    return 1;
  }
  return 0;
}

/**
 * @brief Returns 1 if the player has a win, else, return 0
 * @param grid * g, player * p
 * @return int
 */
int check_win(grid* g, player* p) {
  for (int i = 0; i < NB_COL; i++) {
    for (int j = 0; j < NB_LINES; j++) {
      if (vertical_align(g, p, i, j) == 1 ||
          horizontal_align(g, p, i, j) == 1 ||
          left_diagonal_align(g, p, i, j) == 1 ||
          right_diagonal_align(g, p, i, j) == 1) {
        return 1;
      }
    }
  }
  return 0;
}
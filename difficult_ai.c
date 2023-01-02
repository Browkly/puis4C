#include "difficult_ai.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "jeu.h"

// Retourne la colonne ou le meilleur coup peut être joué
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

// TODO : win check functions
int check_win(grid* g, player* player) { return 0; }
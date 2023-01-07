#include "difficult_ai.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int vertical_align_dif(grid* g, player* p, int x, int y) {
  if ((y + 3) < NB_LINES && g->g[y][x] == p->number_player && g->g[y + 1][x] &&
      g->g[y + 2][x] == p->number_player &&
      g->g[y + 3][x] == p->number_player) {
    return 1;
  }
  return 0;
}

int horizontal_align(grid* g, player* p, int x, int y) {
  if (x < 4 && y >= 0 && y < NB_LINES && g->g[y][x] == p->number_player &&
      g->g[y][x + 1] == p->number_player &&
      g->g[y][x + 2] == p->number_player &&
      g->g[y][x + 3] == p->number_player) {
    return 1;
  }
  return 0;
}

int left_diagonal_align_dif(grid* g, player* p, int x, int y) {
  if ((x + 3) < NB_COL && (y - 3) >= 0 && g->g[x][y] == p->number_player &&
      g->g[x + 1][y - 1] == p->number_player &&
      g->g[x + 2][y - 2] == p->number_player &&
      g->g[x + 3][y - 3] == p->number_player) {
    return 1;
  }
  return 0;
}

int right_diagonal_align_dif(grid* g, player* p, int x, int y) {
  if ((x - 3) >= 0 && (y - 3 >= 0) && g->g[x][y] == p->number_player &&
      g->g[x - 1][y - 1] == p->number_player &&
      g->g[x - 2][y - 2] == p->number_player &&
      g->g[x - 3][y - 3] == p->number_player) {
    return 1;
  }
  return 0;
}

int check_win(grid* g, player* ally, player* enemy) {
  for (int i = 0; i < NB_COL; i++) {
    for (int j = 0; j < NB_LINES; j++) {
      if (vertical_align_dif(g, ally, i, j) == 1 ||
          horizontal_align(g, ally, i, j) == 1 ||
          left_diagonal_align_dif(g, ally, i, j) == 1 ||
          right_diagonal_align_dif(g, ally, i, j) == 1) {
        return 1;
      } else if (vertical_align_dif(g, enemy, i, j) == 1 ||
                 horizontal_align(g, enemy, i, j) == 1 ||
                 left_diagonal_align_dif(g, enemy, i, j) == 1 ||
                 right_diagonal_align_dif(g, enemy, i, j) == 1) {
        return -1;
      }
    }
  }
  return 0;
}

int count_align_horizontal(grid* g, player* p, int x, int y) {
  int count = 0;
  int l = y;
  int c = x;
  while (l < NB_LINES && c < NB_COL && l >= 0 && c >= 0 &&
         g->g[x][y] == g->g[c][l]) {
    if (g->g[x][y] == g->g[c][l]) {
      c++;
      count++;
    }
    if (c == NB_COL || g->g[c][l] != 0 || g->g[c][l] != p->number_player) {
      return 0;  // Case of locked align, by edges of the grid or enemy player
    }
  }
  if (count == 1) {
    return 1;
  }
  if (count == 2) {
    return 50;
  }
  if (count == 3) {
    return 200;
  }
  return 0;
}

int count_align_vertical(grid* g, player* p, int x, int y) {
  int count = 0;
  int l = y;
  int c = x;
  while (l < NB_LINES && c < NB_COL && l >= 0 && c >= 0 &&
         g->g[x][y] == g->g[c][l]) {
    if (g->g[x][y] == g->g[c][l]) {
      l++;
      count++;
    }
    if (y - 1 >= 0 && g->g[x][y - 1] == g->g[x][y]) {
      return 0;
    }
    if (l == NB_LINES || g->g[c][l] != 0 || g->g[c][l] != p->number_player) {
      return 0;  // Case of locked align, by edges of the grid or enemy player
    }
  }
  if (count == 1) {
    return 1;
  }
  if (count == 2) {
    return 50;
  }
  if (count == 3) {
    return 200;
  }
  return 0;
}

int count_align_left_diagonal(grid* g, player* p, int x, int y) {
  int count = 0;
  int l = y;
  int c = x;
  while (l < NB_LINES && c < NB_COL && l >= 0 && c >= 0 &&
         g->g[x][y] == g->g[c][l]) {
    if (g->g[x][y] == g->g[c][l]) {
      c++;
      l--;
      count++;
    }
    if (x - 1 >= 0 && y + 1 < NB_LINES && g->g[x - 1][y + 1] == g->g[x][y]) {
      return 0;
    }
    if (c == NB_COL || l == NB_LINES || g->g[c][l] != 0 ||
        g->g[c][l] != p->number_player) {
      return 0;  // Case of locked align, by edges of the grid or enemy player
    }
  }
  if (count == 1) {
    return 1;
  }
  if (count == 2) {
    return 50;
  }
  if (count == 3) {
    return 200;
  }
  return 0;
}

int count_align_right_diagonal(grid* g, player* p, int x, int y) {
  int count = 0;
  int l = y;
  int c = x;
  while (l < NB_LINES && c < NB_COL && l >= 0 && c >= 0 &&
         g->g[x][y] == g->g[c][l]) {
    if (g->g[x][y] == g->g[c][l]) {
      c++;
      l++;
      count++;
    }
    if (y - 1 >= 0 && x - 1 >= 0 && g->g[x - 1][y - 1] == g->g[x][y]) {
      return 0;
    }
    if (c == NB_COL || l == NB_LINES || g->g[c][l] != 0 ||
        g->g[c][l] != p->number_player) {
      return 0;  // Case of locked align, by edges of the grid or enemy player
    }
  }
  if (count == 1) {
    return 1;
  }
  if (count == 2) {
    return 50;
  }
  if (count == 3) {
    return 200;
  }
  return 0;
}

void simulate_move(grid* g, player* p, int col) {
  int i = get_line(g, col);
  g->g[col][i] = p->number_player;
}

int get_line(grid* g, int column) {
  int i;
  for (i = 0; i < NB_LINES; i++) {
    if (g->g[column][i] == 0) {
      return i;
    }
  }
  return -1;
}

int get_score(grid* g, player* ally, player* enemy) {
  int ally_score = 0;
  int enemy_score = 0;
  for (int i = 0; i < NB_COL; i++) {
    for (int j = 0; j < NB_LINES; j++) {
      ally_score += count_align_horizontal(g, ally, i, j);
      ally_score += count_align_vertical(g, ally, i, j);
      ally_score += count_align_left_diagonal(g, ally, i, j);
      ally_score += count_align_right_diagonal(g, ally, i, j);

      enemy_score += count_align_horizontal(g, enemy, i, j);
      enemy_score += count_align_vertical(g, enemy, i, j);
      enemy_score += count_align_left_diagonal(g, enemy, i, j);
      enemy_score += count_align_right_diagonal(g, enemy, i, j);
    }
  }
  return ally_score - enemy_score;
}

int get_best_column(grid* g, player* ally) {
  player enemy;
  if (ally->number_player == 1) {
    enemy.number_player = 2;
  } else {
    enemy.number_player = 1;
  }
  int* scores = (int*)malloc((NB_COL - 1) * sizeof(int));
  int score = -10000000;
  for (int i = 0; i < NB_COL; i++) {
    if (get_line(g, i) != -1) {
      scores[i] = 0;
    } else {
      scores[i] = score;
    }
  }
  for (int i = 0; i < NB_COL; i++) {
    if (get_line(g, i) != -1) {
      grid g_cpy1 = *g;
      simulate_move(&g_cpy1, ally, i);
      if (check_win(&g_cpy1, ally, &enemy) == 1) {
        free(scores);
        return i;  // the ai can win immediately
      } else {
        scores[i] += (get_score(&g_cpy1, ally, &enemy));
      }
      // Check &enemy move
      for (int j = 0; j < NB_COL; j++) {
        if (get_line(&g_cpy1, i) != -1) {
          grid g_cpy2 = g_cpy1;
          simulate_move(&g_cpy2, &enemy, j);
          if (check_win(&g_cpy2, ally, &enemy) == -1) {
            free(scores);
            return i;  // The ai needs to defend
          } else {
            scores[i] -= (get_score(&g_cpy2, ally, &enemy));
          }
          // Check second move of the ai (after &enemy move)
          for (int k = 0; k < NB_COL; k++) {
            if (get_line(&g_cpy2, i) != -1) {
              grid g_cpy3 = g_cpy2;
              simulate_move(&g_cpy3, ally, k);
              scores[i] += get_score(&g_cpy3, ally, &enemy);
            }
          }
        }
      }
    } else {
      scores[i] = -100000000;
    }
  }
  printf("Affichage du tableau des scores :\n");
  for (int i = 0; i < NB_COL; i++) {
    printf("%d |\n", scores[i]);
  }
  printf("Fin affichage tableau de scores\n");
  int best_score = -1000000;
  int best_col = -1;
  for (int i = 0; i < NB_COL; i++) {
    if (scores[i] > best_score) {
      best_score = scores[i];
      best_col = i;
    }
  }
  free(scores);
  return best_col;
}
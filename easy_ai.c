#include "easy_ai.h"

#include <stdio.h>
#include <time.h>

int get_random_column(player* p, grid* grid) {
  int i, sz, r;
  int* free_cols;
  if (grid->full_case == 1) {
    return -1;
  }
  free_cols = get_free_columns(grid);
  sz = sizeof(free_cols) / sizeof(int);
  srand(time(NULL));
  r = (rand() % sz);
  return free_cols[r];
}

int* get_free_columns(grid* grid) {
  int* free_cols;
  int i, n = 0;
  for (i = 0; i < NB_COL; i++) {
    if (is_column_full(grid, i) == 0) {
      free_cols[n] = i;
    }
  }
  return free_cols;
}

int is_column_full(grid* grid, int col) {
  if (grid->g[NB_LINES - 1][col] != 0) {
    return 1;
  }
  return 0;
}

int round_ai(player* p, grid* g) {
  int choice = get_random_column(p, g);
  return choice;
}
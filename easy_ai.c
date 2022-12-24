#include "easy_ai.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jeu.h"

extern int error;

void srand();
int rand();

int get_random_number(int max) {
  int n = 0;
  srand(time(NULL));
  n = rand() % max;
  // printf("Nombre aléatoire généré: %d\n", n);
  return n;
}

int is_column_full(grid* g, int c) {
  if (g->g[c][5] == 0) {
    return 0;  // colonne non pleine
  }
  return 1;  // colonne pleine
}

int get_number_free_col(grid* g) {
  int n = 0;
  for (int i = 0; i < NB_COL; i++) {
    if (is_column_full(g, i) == 0) {
      n++;
    }
  }
  return n;
}

int* init_tab(int size) {
  int* tab = malloc(size * sizeof(int));
  if (tab == NULL) {
    error = MEMORY_ERROR;
  }
  return tab;
}

int* get_columns_index(grid* g) {
  int k = 0;
  int n = get_number_free_col(g);
  int* cols = init_tab(n);
  for (int i = 0; i < NB_COL; i++) {
    if (is_column_full(g, i) == 0) {
      cols[k] = i;
      k++;
    }
  }
  return cols;
}

int random_choice(grid* g) {
  int n = get_number_free_col(g);
  int choice = get_random_number(n);
  return choice;
}

void main() {}
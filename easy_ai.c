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
  return n;
}

int random_choice(grid* g) {
  int choice = get_random_number(NB_COL);
  return choice;
}
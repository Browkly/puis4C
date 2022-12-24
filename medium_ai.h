#ifndef MEDIUM_AI_H
#define MEDIUM_AI_H

#include "easy_ai.h"

int get_vertical_align(grid *, player *);
int get_horizontal_align(grid *, player *);
int get_diagonal_align(grid *, player *);
int find_biggest_align(grid *, player *);
int is_valid(grid *, player *, int, int);
int is_reachable(grid *, int, int);
#endif
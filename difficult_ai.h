#ifndef DIFFICULT_AI_H
#define DIFFICULT_AI_H
#include "easy_ai.h"
#include "jeu.h"
#define NB_COL 7
#define NB_LINES 8

int difficult_ai_move(grid *, player *, player *);
int minimax(grid *, player *, player *, int, int, int, int);
int check_win(grid *, player *, player *);
int vertical_align(grid *, player *, int, int);
int horizontal_align(grid *, player *, int, int);
int left_diagonal_align(grid *, player *, int, int);
int right_diagonal_align(grid *, player *, int, int);
int count_align_horizontal(grid *, player *, int, int);
int count_align_vertical(grid *, player *, int, int);
int count_align_left_diagonal(grid *, player *, int, int);
int count_align_right_diagonal(grid *, player *, int, int);
void simulate_move(grid *, player *, int);
int get_line(grid *, int);
int get_score(grid *, player *, player *);
int get_best_column(grid *, player *, player *);
#endif
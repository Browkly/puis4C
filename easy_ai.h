#ifndef EASY_AI_H
#define EASY_AI_H

#define NB_LINES 6

#define NB_COL 7

// Temporary
typedef struct _player {
  int number_player;
  int difficulty;  // 0 : Human ; 1 : Easy ; 2 : Normal ; 3 : Hard
  int last_x;
  int last_y;
} player;

typedef struct _grid {
  int full_case;  // Number of full cases (those which are != 0)
  int g[6][7];
} grid;

/**
 * @brief Return a randomly choosen column for the given ai to play a move.
 */
int get_random_column(player *, grid *);
/**
 * @brief Return all the non-full columns int the current grid.
 */
int *get_free_columns(grid *);

/**
 * @brief Checks if the given column of the grid is full.
 */
int is_column_full(grid *, int);

/**
 * @brief Function which allow the easy level ai to play a move
 */
int round_easy_ai(player *, grid *);

#endif
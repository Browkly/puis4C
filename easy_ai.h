#ifndef EASY_AI_H
#define EASY_AI_H

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
 * @brief Returns the columns the easy ai has chosen to play.
 */
int round_easy_ai(player *, grid *);

#endif
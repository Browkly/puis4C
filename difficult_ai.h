#ifndef DIFFICULT_AI_H
#define DIFFICULT_AI_H
#include "jeu.h"
#define NB_COL 7
#define NB_LINES 6

/**
 * @brief Returns 1 if the player has a vertical align at given coordinates, 0
 * else
 * @param g the game grid
 * @param p the player we want to test the align
 * @param x the column
 * @param y the line
 * @return 1 if there is an align, 0 else
 */
int vertical_align_dif(grid *, player *, int, int);

/**
 * @brief Returns 1 if the player has a horizontal align at given coordinates, 0
 * else
 * @param g the game grid
 * @param p the player we want to test the align
 * @param x the column
 * @param y the line
 * @return 1 if there is an align, 0 else
 */
int horizontal_align(grid *, player *, int, int);

/**
 * @brief Returns 1 if the player has a left diagonal align at given
 * coordinates, 0 else
 * @param g the game grid
 * @param p the player we want to test the align
 * @param x the column
 * @param y the line
 * @return 1 if there is an align, 0 else
 */
int left_diagonal_align_dif(grid *, player *, int, int);

/**
 * @brief Returns 1 if the player has a right diagonal align at given
 * coordinates, 0 else
 * @param g the game grid
 * @param p the player we want to test the align
 * @param x the column
 * @param y the line
 * @return 1 if there is an align, 0 else
 */
int right_diagonal_align_dif(grid *, player *, int, int);

/**
 * @brief Returns 1 if the player has a win, else, return 0
 * @param g the game grid
 * @param p the player we want to check the win.
 * @return 1 if the player has a win, 0 else.
 */
int check_win(grid *, player *, player *);

/**
 * @brief Return a score based on the length of the align beginning at the
 * coordinates (x, y), returns 0 if no align or only locked ones
 * @param g the game grid
 * @param p the player we want to check the align
 * @param x the starting column of  the align
 * @param y the starting line of the align
 * @return 1 if the align has a length of 1, 50 if it has a length if 2, 200 if
 * a length of 3, 0 else
 */
int count_align_horizontal(grid *, player *, int, int);

/**
 * @brief Return a score based on the length of the align beginning at the
 * coordinates (x, y), returns 0 if no align or only locked ones
 * @param g the game grid
 * @param p the player we want to check the align
 * @param x the starting column of  the align
 * @param y the starting line of the align
 * @return 1 if the align has a length of 1, 50 if it has a length if 2, 200 if
 * a length of 3, 0 else
 */
int count_align_vertical(grid *, player *, int, int);

/**
 * @brief Return a score based on the length of the align beginning at the
 * coordinates (x, y), returns 0 if no align or only locked ones
 * @param g the game grid
 * @param p the player we want to check the align
 * @param x the starting column of  the align
 * @param y the starting line of the align
 * @return 1 if the align has a length of 1, 50 if it has a length if 2, 200 if
 * a length of 3, 0 else
 */
int count_align_left_diagonal(grid *, player *, int, int);

/**
 * @brief Return a score based on the length of the align beginning at the
 * coordinates (x, y), returns 0 if no align or only locked ones
 * @param g the game grid
 * @param p the player we want to check the align
 * @param x the starting column of  the align
 * @param y the starting line of the align
 * @return 1 if the align has a length of 1, 50 if it has a length if 2, 200 if
 * a length of 3, 0 else
 */
int count_align_right_diagonal(grid *, player *, int, int);

/**
 * @brief Add a pawn of the given player to the given column, this function is
 * only used by the algorithm with a copy of the grid in order to find the best
 * move.
 * @param g the game grid
 * @param p the player we want to simulate a move from
 * @param c the column where we want to simulate the move
 * @return Nothing
 */
void simulate_move(grid *, player *, int);

/**
 * @brief Returns the lowest free tile of a given column of the grid
 * @param g the game grid
 * @param c the column
 * @return lowest free line or -1 if the column is full
 */
int get_line(grid *, int);

/**
 * @brief Calculates the score of the current state of the grid
 * @param g the game grid
 * @param ally the ally player
 * @param enemy the enemy player
 * @return the score of the current state of the grid the score is added to the
 * global score and the enemy's score is subtracted to the global score
 */
int get_score(grid *, player *, player *);

/**
 * @brief Gives the best column based on an algorithm wich update a score based
 * on the aligns in each possible configuration of the grid for the 3 next
 * moves.
 * @param g the game grid
 * @param ally the ally player
 * @return the column where the algorithm thinks it is best to put a pawn for
 * the ally player
 */
int get_best_column(grid *, player *);

#endif
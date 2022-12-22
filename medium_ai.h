#ifndef MEDIUM_AI_H
#define MEDIUM_AI_H

/**
 * @brief Return the column of the winning move if the move is about to be
 * reached by one of the players
 */
void find_winning_move();

/**
 * @brief Return a list which contains every align in the grid
 */
void find_every_aligns();

/**
 * @brief Find the longes align, if the align is made of enemy pawns, the ai
 * will play with a defensive style, else, it will try to win.
 */
void find_longest_align();

/**
 * @brief returns 0 if the next winning move is not reachable currently, return
 * 1 if it is reachable so the ai can place the pawn there
 */
void is_reachable();
#endif
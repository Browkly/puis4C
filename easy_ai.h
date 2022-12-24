#ifndef EASY_AI_H
#define EASY_AI_H
#define NB_COL 7
#define NB_LINES 8

#include "jeu.h"

/**
 * @brief Return an int which represents the position of the column the ai
 * choosed to play
 * @param grid * g
 * @return (int choice)
 */
int random_choice(grid *);

#endif
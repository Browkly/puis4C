#ifndef MEDIUM_AI_H
#define MEDIUM_AI_H

#include "easy_ai.h"

// Returns the length of the vertical align at the player's last move's
// coordinates
int get_vertical_align(grid *, player *);  // done
// Returns the length of the horizontal align at the player's last move's
// coordinates
int get_horizontal_align(grid *, player *);  // done
// Returns the length of the left diagonal align at the player's last move's
// coordinates
int get_left_diagonal_align(grid *, player *);  // done
// Returns the length of the right diagonal align at the player's last move's
// coordinates
int get_right_diagonal_align(grid *, player *);  // done
// Returns an int based on the direction of the longest align, 0 if no align,
// etc
int find_biggest_align(grid *, player *, player *);  // done
// Returns 1 if the hit at given column is valid, else return 0
int is_valid(grid *, player *, int);  // done
// Returns 1 if the point at given coordinates is reachable, else return 0
int is_reachable(grid *, player *, int, int);  // done

// Returns 0 or 1 depending the adjacent tile to the gi en align is or not
// reachable
int is_left_border_horizontal_align_reachable(grid *, player *);   // done
int is_right_border_horizontal_align_reachable(grid *, player *);  // done
int is_left_left_diagonal_align_reachable(grid *, player *);       // done
int is_right_left_horizontal_align_reachable(grid *, player *);    // done
int is_left_right_diagonal_align_reachable(grid *, player *);      // done
int is_right_right_horizontal_align_reachable(grid *, player *);   // done

// Get coordinates of the free tile for the ai to increase size of the align or
// block it depending of the color
// for Horizontal aligns
int get_left_border_horizontal_align(grid *, player *);       // done
int get_right_border_horizontal_align(grid *, player *);      // done
int get_left_border_left_diagonal_align(grid *, player *);    // done
int get_right_border_left_diagonal_align(grid *, player *);   // done
int get_left_border_right_diagonal_align(grid *, player *);   // done
int get_right_border_right_diagonal_align(grid *, player *);  // done

// Move selecting function
int get_medium_ai_move(grid *, player *, player *);
#endif
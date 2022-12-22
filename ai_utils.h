
#ifndef AI_UTILS_H
#define AI_UTILS_H
#define NB_LINES 6
#define NB_COL 7

// Temporaire
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

#endif
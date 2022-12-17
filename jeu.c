#include "jeu.h"

#include <stdio.h>
#include <stdlib.h>

ERROR error;

grid *init_grid(void) {
  error = NO_ERROR;
  grid *g;
  int i, j;
  g = (grid *)malloc(sizeof(grid));
  if (!g) {
    error = MEMORY_ERROR;
    return NULL;
  }
  for (i = 0; i < 6; i++) {
    for (j = 0; j < 7; j++) {
      (g->g)[i][j] = 0;
    }
  }
  g->full_case = 0;
  return g;
}

player *init_player(int number, int difficulty) {
  error = NO_ERROR;
  player *p;
  p = (player *)malloc(sizeof(player));
  if (!p) {
    error = MEMORY_ERROR;
    return;
  }
  p->difficulty = difficulty;
  p->number_player = number;
  p->last_x = -1;
  p->last_y = -1;
  return p;
}

game *init_game(int player_1, int player_2) {
  error = NO_ERROR;
  game *g;
  g = (game *)malloc(sizeof(game));
  if (!g) {
    error = MEMORY_ERROR;
    return NULL;
  }
  if (player_1 >= 0 && player_1 <= 3) {
    g->player_1 = init_player(1, player_1);
    if (!g->player_1) {
      error_management(error);
      clear_game_memory(&g);
    }
  } else {
    error = DIFFICULTY_ERROR;
    error_management(error);
    clear_game_memory(&g);
  }
  if (player_2 >= 0 && player_2 <= 3) {
    g->player_2 = init_player(2, player_2);
    if (!g->player_2) {
      error_management(error);
      clear_game_memory(&g);
    }
  } else {
    error = DIFFICULTY_ERROR;
    error_management(error);
    clear_game_memory(&g);
  }
  g->g = init_grid();
  if (!g) {
    error_management(error);
    clear_game_memory(&g);
  }
  return g;
}

int alignment(player *p, grid *g) {
  error = NO_ERROR;
  int i, j, min_i, min_j;
  if (!p) {
    error = NO_PLAYER_ERROR;
    return -1;
  }
  if (!g) {
    error = NO_GRID_ERROR;
    return -1;
  }
  if (p->last_x < 0 || p->last_x > 6 || p->last_y < 0 || p->last_y > 5) {
    error = COOR_ERROR;
    return -1;
  }
  // Check line
  for (i = 0; i < 4; i++) {
    if ((g->g)[p->last_y][i] == p->number_player) {
      if (((g->g)[p->last_y][i + 1] == p->number_player) &&
          ((g->g)[p->last_y][i + 2] == p->number_player) &&
          ((g->g)[p->last_y][i + 3] == p->number_player)) {
        return 1;
      }
    }
  }
  // Check column
  for (j = 0; j < 3; j++) {
    if ((g->g)[j][p->last_x] == p->number_player) {
      if ((g->g)[j + 1][p->last_x] == p->number_player &&
          (g->g)[j + 2][p->last_x] == p->number_player &&
          (g->g)[j + 3][p->last_x] == p->number_player) {
        return 1;
      }
    }
  }
  // Check left diagonal
  min_i = p->last_x;
  min_j = p->last_y;
  while (min_i > 0 && min_j < 6) {
    min_i--;
    min_j++;
  }
  while (min_i + 3 < 7 && min_j - 3 > 0) {
    if ((g->g)[min_j][min_i] == p->number_player) {
      if ((g->g)[min_j - 1][min_i + 1] == p->number_player &&
          (g->g)[min_j - 2][min_i + 2] == p->number_player &&
          (g->g)[min_j - 3][min_i + 3] == p->number_player) {
        return 1;
      }
    }
    min_i++;
    min_j--;
  }
  // Check right diagonal
  min_i = p->last_x;
  min_j = p->last_y;
  while (min_i > 0 && min_j > 0) {
    min_i--;
    min_j--;
  }
  while (min_i + 3 < 7 && min_j + 3 < 6) {
    if ((g->g)[min_j][min_i] == p->number_player) {
      if ((g->g)[min_j + 1][min_i + 1] == p->number_player &&
          (g->g)[min_j + 2][min_i + 2] == p->number_player &&
          (g->g)[min_j + 3][min_i + 3] == p->number_player) {
        return 1;
      }
    }
    min_i++;
    min_j++;
  }
  return 0;
}

int add_coin(player *p, grid *g, int column) {
  error = NO_ERROR;
  int j;
  if (!g) {
    error = NO_GRID_ERROR;
    return -1;
  }
  if (!p) {
    error = NO_PLAYER_ERROR;
    return -1;
  }
  for (j = 0; j < 6; j++) {
    if ((g->g)[j][column] == 0) {
      (g->g)[j][column] = p->number_player;
      p->last_x = column;
      p->last_y = j;
      g->full_case += 1;
      return 1;
    }
  }
  return 0;
}

int round_player(player *p, grid *g) {
  error = NO_ERROR;
  int choice = -1;
  if (!g) {
    error = NO_GRID_ERROR;
    return;
  }
  if (!p) {
    error = NO_PLAYER_ERROR;
    return;
  }
  switch (p->difficulty) {
    case 0:
      choice = round_human(p, g);
      break;
    case (1 || 2 || 3):
      choice = round_AI(p, g);
      break;
    default:
      error = CHOICE_ERROR;
  }
  return choice;
}

ERROR getError(void) { return error; }
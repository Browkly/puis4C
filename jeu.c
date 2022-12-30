#include "jeu.h"

#include <stdio.h>
#include <stdlib.h>

#include "affichage_terminal.h"
#include "graphical_display.h"

ERROR error;

void getError(void) {
  switch (error) {
    case NO_ERROR:
      printf("No error\n");
      break;
    case MEMORY_ERROR:
      printf("Memory error\n");
      break;
    case GRAPHICAL_WINDOW_ERROR:
      printf("Graphical window error\n");
      break;
    default:
      return;
  }
}

void clear_game_memory(game **g) {
  if (!(*g)) {
    return;
  }
  if ((*g)->g) {
    free((*g)->g);
  }
  if ((*g)->player_1) {
    free((*g)->player_1);
  }
  if ((*g)->player_2) {
    free((*g)->player_2);
  }
  destroy_game_window(&((*g)->gw));
  free(*g);
}

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
    return NULL;
  }
  p->difficulty = difficulty;
  p->number_player = number;
  p->last_x = -1;
  p->last_y = -1;
  return p;
}

game *init_game(int player_1, int player_2, int display) {
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
      getError();
      clear_game_memory(&g);
    }
  } else {
    error = DIFFICULTY_ERROR;
    getError();
    clear_game_memory(&g);
  }
  if (player_2 >= 0 && player_2 <= 3) {
    g->player_2 = init_player(2, player_2);
    if (!g->player_2) {
      getError();
      clear_game_memory(&g);
    }
  } else {
    error = DIFFICULTY_ERROR;
    getError();
    clear_game_memory(&g);
  }
  g->g = init_grid();
  if (!g) {
    getError();
    clear_game_memory(&g);
  }
  g->display = display;
  g->gw = NULL;
  if (display == 1) {
    if (!init_game_window(&(g->gw), "Power of 4", 1022, 768)) {
      error = GRAPHICAL_WINDOW_ERROR;
      clear_game_memory(&g);
    }
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
  while (min_i < 7 && min_j > 0) {
    min_i++;
    min_j--;
  }
  while (min_i - 3 > 0 && min_j + 3 < 6) {
    if ((g->g)[min_j][min_i] == p->number_player) {
      if ((g->g)[min_j + 1][min_i - 1] == p->number_player &&
          (g->g)[min_j + 2][min_i - 2] == p->number_player &&
          (g->g)[min_j + 3][min_i - 3] == p->number_player) {
        return 1;
      }
    }
    min_i--;
    min_j++;
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
  if (column >= 0 && column <= 6) {
    for (j = 0; j < 6; j++) {
      if ((g->g)[j][column] == 0) {
        (g->g)[j][column] = p->number_player;
        p->last_x = column;
        p->last_y = j;
        g->full_case += 1;
        return 1;
      }
    }
  }
  return 0;
}

int round_human(int display, game_window *gw) {
  int choice = -1;
  if (display == 0) {
    choice = round_human_terminal();
  } else {
    choice = round_human_graphical(gw);
  }
  return choice;
}

int round_AI(player *p, grid *g) {
  return -1;
}  // temporaire, va être défini dans ai.h

int round_player(player *p, grid *g, int display, game_window *gw) {
  error = NO_ERROR;
  int choice = -1;
  if (!g) {
    error = NO_GRID_ERROR;
    return choice;
  }
  if (!p) {
    error = NO_PLAYER_ERROR;
    return choice;
  }
  switch (p->difficulty) {
    case 0:
      choice = round_human(display, gw) -
               1;  // Because the first column for the human is at the index 0
      break;
    case (1 || 2 || 3):
      choice = round_AI(p, g);
      break;
    default:
      error = CHOICE_ERROR;
  }
  return choice;
}

void print_game(int display, grid *g, game_window *gw, player *last_player) {
  if (!display) {
    print_grid_terminal(g);
  } else {
    if (last_player->number_player == 1) {
      draw_coin(gw, RED, (gw->parts)[last_player->last_y][last_player->last_x]);
    } else {
      draw_coin(gw, YELLOW,
                (gw->parts)[last_player->last_y][last_player->last_x]);
    }
  }
}

void drain_buffer(void) {
  int buffer_drainer;
  do {
    buffer_drainer = getchar();
  } while (buffer_drainer != '\n' && buffer_drainer != EOF);
}

void launch_game(void) {
  game *g;
  int game_over = 0, p1_difficulty, p2_difficulty, display, winner = 0,
      validated_move;
  printf(
      "Welcome to the power of 4 game. The rules are simple :\n-Two players "
      "(human or AI)\n-Turn-based game\n-Grid of 6x7\n-Goal : align 4 coins\n");
  do {
    printf(
        "Is the first player a human (0) or an AI (1 for easy, 2 for normal, 3 "
        "for difficult) ?\n");
    p1_difficulty = getchar();
    p1_difficulty -=
        48;  // Because getchar() gives us the ASCII code (ASCII code of 1 = 49)
    drain_buffer();
  } while (p1_difficulty < 0 || p1_difficulty > 3);
  do {
    printf(
        "Is the second player a human (0) or an AI (1 for easy, 2 for normal, "
        "3 "
        "for difficult) ?\n");
    p2_difficulty = getchar();
    p2_difficulty -=
        48;  // Because getchar() gives us the ASCII code (ASCII code of 1 = 49)
    drain_buffer();
  } while (p2_difficulty < 0 || p2_difficulty > 3);
  do {
    printf("Terminal mode (0) or graphical mode (1) ?\n");
    display = getchar();
    display -=
        48;  // Because getchar() gives us the ASCII code (ASCII code of 1 = 49)
    drain_buffer();
  } while (display != 0 && display != 1);
  printf("Enjoy the game !\n");
  g = init_game(p1_difficulty, p2_difficulty, display);
  if (!g) {
    exit(EXIT_FAILURE);
  }
  while (!game_over) {
    printf("Player 1 turn.\n");
    do {
      validated_move =
          add_coin(g->player_1, g->g,
                   round_player(g->player_1, g->g, g->display, g->gw));
    } while (!validated_move);
    print_game(g->display, g->g, g->gw, g->player_1);
    if (alignment(g->player_1, g->g)) {
      winner = 1;
      game_over = 1;
      goto end;
    }

    printf("Player 2 turn.\n");
    do {
      validated_move =
          add_coin(g->player_2, g->g,
                   round_player(g->player_2, g->g, g->display, g->gw));
    } while (!validated_move);
    print_game(g->display, g->g, g->gw, g->player_2);
    if (alignment(g->player_2, g->g)) {
      winner = 2;
      game_over = 1;
      goto end;
    }

    if (g->g->full_case == 42) {  // If all the cases are full
      game_over = 1;
    }
  end:
  }
  if (!winner) {
    printf("No winner ... well played to both players !\n");
  } else {
    printf("Player number %d won, congrats to him !\n", winner);
  }
  clear_game_memory(&g);
}
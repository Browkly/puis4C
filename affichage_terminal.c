#include "affichage_terminal.h"

#include <stdio.h>
#include <stdlib.h>

#include "jeu.h"

void print_grid_terminal(grid *g) {
  int i, j;
  if (!g) {
    return;
  }
  for (i = 5; i >= 0; i--) {
    printf("|");
    for (j = 0; j < 7; j++) {
      switch ((g->g)[i][j]) {
        case 0:
          printf("   |");
          break;
        case 1:
          printf(" x |");
          break;
        case 2:
          printf(" o |");
          break;
        default:
          break;
      }
    }
    printf("\n");
  }
}

int round_human_terminal(void) {
  int choice = -1;
  int buffer_drainer;
  do {
    printf("Make your column choice (between 1 and 7):\n");
    choice = getchar();
    choice -=
        48;  // Because getchar() gives us the ASCII code (ASCII code of 1 = 49)
    do {
      buffer_drainer = getchar();
    } while (buffer_drainer != '\n' &&
             buffer_drainer != EOF);  // We drain the buffer
  } while (choice < 1 || choice > 7);
  return choice;
}
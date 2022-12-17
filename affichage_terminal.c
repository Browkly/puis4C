#include <stdio.h>
#include <stdlib.h>

#include "affichage_terminal.h"
#include "jeu.h"

void print_grid_terminal(grid *g)
{
    int i, j;
    if (!g)
    {
        return;
    }
    for (i = 5; i >= 0; i--)
    {
        printf("|");
        for (j = 0; j < 7; j++)
        {
            printf(" %d  |", (g->g)[i][j]);
        }
        printf("\n");
    }
}
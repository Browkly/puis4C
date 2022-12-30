#include "round_ai.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
int round_ai(grid* g, player* p, player* ai) {
  assert(g);
  assert(p);
  assert(ai);

  switch (ai->difficulty) {
    case 1:
      return random_choice(g);
      break;
    case 2:
      return get_medium_ai_move(g, p, ai);
      break;
    case 3:
      // à implémenter
      // return get_difficult_ai_move(g, p, ai);
      break;
  }

  return -1;
}
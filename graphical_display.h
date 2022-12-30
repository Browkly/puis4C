#ifndef _GRAPHICAL_DISPLAY_H
#define _GRAPHICAL_DISPLAY_H 0

#include "SDL2/SDL.h"

typedef struct _game_window {
  SDL_Window *window;
  SDL_Renderer *renderer;

  SDL_Rect parts[6][7];  // The parts of the window corresponding to the framing
                         // of the coins

  int height;
  int width;
} game_window;

typedef struct {
  unsigned r : 8;
  unsigned g : 8;
  unsigned b : 8;
  unsigned a : 8;
} color;

#define WHITE ((color){255, 255, 255, 255})
#define RED ((color){255, 0, 0, 255})
#define YELLOW ((color){255, 255, 0, 255})

/**
 * @brief Initialise the game window
 * @return 0 if a problem occurs, >0 otherwise
 */
int init_game_window(game_window **gw, char *title, int width, int height);
/**
 * @brief Frees the allocated memory used for the game window
 */
void destroy_game_window(game_window **gw);
/**
 * @brief Draws the coin at the SDL_rec specified, with the color specified, on
 * the game window
 */
int draw_coin(game_window *gw, color c, SDL_Rect rec);
/**
 * @brief Give the column choice of the human player by clicking on it
 * @return the column choice of the human-player if the event was a left-button
 * mouse click on the game window (between 1 and 7), 0 otherwise
 */
int round_human_graphical(game_window *gw);

#endif
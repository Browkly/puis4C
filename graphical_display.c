#include "graphical_display.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "jeu.h"

static int counter = 0;

void set_parts(game_window *gw) {
  int i, i_tmp, j;  // 0,0 corresponding to the upper left corner, we
                    // assign the lowest rectangle to the highest height
  for (i = 0, i_tmp = 5; i < 6; i++, i_tmp--) {
    for (j = 0; j < 7; j++) {
      (gw->parts)[i][j] =
          (SDL_Rect){j * (gw->width / 7), i_tmp * (gw->height / 6),
                     gw->width / 7, gw->height / 6};
    }
  }
}

int in_circle(int x, int y, int center_x, int center_y, int radius) {
  return ((int)sqrt(pow(x - center_x, 2) + pow(y - center_y, 2)) <= radius);
}

int draw_coin(game_window *gw, color c, SDL_Rect rec) {
  int i, j, pitch, rec_center_x, rec_center_y;
  void *tmp;
  Uint32 *pixels;
  SDL_Texture *texture;
  SDL_PixelFormat *format;
  texture =
      SDL_CreateTexture(gw->renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_STREAMING, gw->width, gw->height);
  if (!texture) {
    return -1;
  }
  format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
  if (!format) {
    SDL_DestroyTexture(texture);
    return -1;
  }

  SDL_LockTexture(texture, NULL, &tmp, &pitch);
  pixels = tmp;

  rec_center_x = rec.x + (rec.w / 2);
  rec_center_y = rec.y + (rec.h / 2);

  for (i = 0; i < gw->height; i++) {
    for (j = 0; j < gw->width; j++) {
      if (in_circle(j, i, rec_center_x, rec_center_y, rec.h / 3)) {
        pixels[i * gw->width + j] = SDL_MapRGBA(format, c.r, c.g, c.b, c.a);
      } else {
        pixels[i * gw->width + j] = SDL_MapRGBA(format, 0, 0, 255, 255);
      }
    }
  }

  SDL_UnlockTexture(texture);
  SDL_RenderCopy(gw->renderer, texture, &rec, &rec);
  SDL_RenderPresent(gw->renderer);

  SDL_FreeFormat(format);
  SDL_DestroyTexture(texture);

  return 0;
}

int init_game_window(game_window **gw, char *title, int width, int height) {
  int i, j;
  if (!*gw) {
    *gw = (game_window *)malloc(sizeof(game_window));
    if (!*gw) {
      return 0;
    }
  }

  if (!counter) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      return 0;
    }
  }

  counter++;

  (*gw)->window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_SHOWN);
  if (!(*gw)->window) {
    return 0;
  }
  (*gw)->renderer =
      SDL_CreateRenderer((*gw)->window, -1, SDL_RENDERER_ACCELERATED);
  if (!(*gw)->renderer) {
    return 0;
  }
  (*gw)->width = width;
  (*gw)->height = height;

  set_parts(*gw);

  for (i = 0; i < 6; i++) {
    for (j = 0; j < 7; j++) {
      draw_coin(*gw, WHITE, ((*gw)->parts)[i][j]);
    }
  }
  return 1;
}

void destroy_game_window(game_window **gw) {
  if (!*gw) {
    return;
  }

  if ((*gw)->renderer) {
    SDL_DestroyRenderer((*gw)->renderer);
  }

  if ((*gw)->window) {
    SDL_DestroyWindow((*gw)->window);
  }

  free(*gw);

  counter--;
  if (!counter) {
    SDL_Quit();
  }
}

int round_human_graphical(game_window *gw) {
  SDL_Event event;
  while (SDL_WaitEvent(&event) > 0) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
      if (event.button.button == SDL_BUTTON_LEFT &&
          event.button.windowID == SDL_GetWindowID(gw->window)) {
        // Récupérer les x pour retourner le x auquel la case appartient
        if (event.button.x < gw->width / 7) {
          return 1;
        } else if (event.button.x >= gw->width / 7 &&
                   event.button.x < 2 * gw->width / 7) {
          return 2;
        } else if (event.button.x >= 2 * gw->width / 7 &&
                   event.button.x < 3 * gw->width / 7) {
          return 3;
        } else if (event.button.x >= 3 * gw->width / 7 &&
                   event.button.x < 4 * gw->width / 7) {
          return 4;
        } else if (event.button.x >= 4 * gw->width / 7 &&
                   event.button.x < 5 * gw->width / 7) {
          return 5;
        } else if (event.button.x >= 5 * gw->width / 7 &&
                   event.button.x < 6 * gw->width / 7) {
          return 6;
        } else if (event.button.x >= 6 * gw->width / 7) {
          return 7;
        }
      }
    }
  }

  return 0;
}
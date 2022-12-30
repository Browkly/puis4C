#ifndef _JEU_H
#define _JEU_H 0

typedef struct _game_window game_window;

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

typedef struct _game {
  player *player_1;
  player *player_2;
  grid *g;
  int display;  // 0 for the terminal display ; 1 for the graphical display
  game_window *gw;
} game;

typedef enum _ERROR {
  NO_ERROR,
  MEMORY_ERROR,
  DIFFICULTY_ERROR,
  NO_PLAYER_ERROR,
  NO_GRID_ERROR,
  COOR_ERROR,
  CHOICE_ERROR,
  GRAPHICAL_WINDOW_ERROR
} ERROR;

/**
 * @brief Tell to the user the error that occured
 */
void getError(void);

/**
 * @brief Free all the game's elements allocated
 *
 * @param game
 */
void clear_game_memory(game **g);

grid *init_grid(void);

player *init_player(int number, int difficulty);

/**
 * @brief Initialize the game depending on the player 1 and 2 parameters (if ==
 * 0 human ; if == 1 easy AI ; if == 2 normal AI ; if == 2 difficult AI), and
 * the display (if == 0 terminal display ; if == 1 graphical display)
 *
 * @param player_1
 * @param player_2
 * @param display
 * @return game*
 */
game *init_game(int player_1, int player_2, int display);

/**
 * @brief Return if the player has scored an alignment
 *
 * @param player
 * @param grid
 * @return 0 if no line ; 1 if line ; -1 if error
 */
int alignment(player *p, grid *g);

/**
 * @brief Add a coin of the player on a column in the grid
 *
 * @param player
 * @param grid
 * @param column
 * @return 0 if it is not possible ; 1 if the adding has been done ; -1 if error
 */
int add_coin(player *p, grid *g, int column);

/**
 * @brief Interact with the human player to ask him his choice (if display == 0
 * terminal interaction ; if display == 1 graphical interaction )
 * @return the column choice of the human
 */
int round_human(int display, game_window *gw);

/**
 * @brief Interact either with the human or with the AI to know his/its choice
 *
 * @param player
 * @param grid
 * @param display
 * @return The choice of either ; -1 if an error occured
 */
int round_player(player *p, grid *g, int display, game_window *gw);

void print_game(int display, grid *g, game_window *gw, player *last_player);

void launch_game(void);

#endif
#ifndef INTERFACE_HEADERS
#define INTERFACE_HEADERS

#include <ncurses.h>

#include "../../game/headers/tetris_defines.h"
#include "../../game/headers/tetris_headers.h"
#include "../../game/headers/tetris_objects.h"
#include "interface_defines.h"
#include "interface_objects.h"

/* utils functions */
void init_colors();
interf_t init_interf();
void reset_timeout(interf_t *interf, const game_t *game);
void use_effects(interf_t *interf, const game_t *game);

/* raw_input processing functions */
input_t preprocess_ch(int ch, interf_t *interf, const game_t *game);
bool reset_flag_mv_key(int ch, interf_t *interf, const game_t *game);
bool is_mv_key(int ch, state_t state);
int prevent_sticking(int ch, interf_t *interf, const game_t *game);
int check_sticking_count(int ch, int *count);
int handle_d(interf_t *interf);
void handle_resize(subwins_t *subwins);
input_t translate_ch(int ch);

/* frontend functions */
void create_subwins(subwins_t *subwins);
void delete_subwins(subwins_t *subwins);
void render(GameInfo_t game_info, game_t *game, interf_t *interf);

/* debug functions */
char *show_ch(int ch);
char *show_signal(signal_t signal);
char *show_state(state_t state);

#endif

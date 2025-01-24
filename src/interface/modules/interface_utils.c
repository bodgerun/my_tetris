#include "../headers/interface_headers.h"

void init_colors() {
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_BLUE);  /* BLOCK */
  init_pair(2, COLOR_BLACK, COLOR_WHITE); /* GROUND */
  init_pair(3, COLOR_GREEN, COLOR_BLACK); /* VOID_GREEN */
  init_pair(4, COLOR_BLACK, COLOR_GREEN); /* GROUND_GREEN || GROUND_FULL_ROW */
  init_pair(5, COLOR_RED, COLOR_BLACK);   /* VOID_RED */
  init_pair(6, COLOR_BLACK, COLOR_RED);   /* GROUND_RED */
}

interf_t init_interf() {
  interf_t interf;

  interf.iter_count = 0;
  interf.ch_count = 0;
  interf.cur_ch = ERR;
  interf.flags.f_debug = false;
  interf.flags.f_silent = false;
  interf.flags.f_stop = false;
  interf.flags.f_resumed = false;
  interf.flags.f_mv_key = false;

  create_subwins(&interf.subwins);

  return interf;
}

void reset_timeout(interf_t *interf, const game_t *game) {
  if (game->state == ST_SPAWN) {
    timeout(game->speed);
  } else if (game->pause) {
    timeout(-1);
    interf->flags.f_resumed = true;
  } else if (interf->flags.f_resumed) {
    timeout(game->speed);
    interf->flags.f_resumed = false;
  }
}

void use_effects(interf_t *interf, const game_t *game) {
  if (!interf->flags.f_silent) {
    if (game->state == ST_MOVE && interf->flags.f_mv_key) {
      beep();
    } else if (game->state == ST_COLLAPSE) {
      flash();
    }
  }
}

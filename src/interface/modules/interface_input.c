#include "../headers/interface_headers.h"

input_t preprocess_ch(int ch, interf_t *interf, const game_t *game) {
  interf->flags.f_mv_key = reset_flag_mv_key(ch, interf, game);
  interf->cur_ch = prevent_sticking(ch, interf, game);

  if (!interf->flags.f_mv_key) {
    switch (interf->cur_ch) {
      case 's':
        interf->flags.f_silent = !interf->flags.f_silent;
        break;
      case 'd':
        interf->flags.f_debug = handle_d(interf);
        break;
      case KEY_RESIZE:
        handle_resize(&interf->subwins);
    }
  }

  return translate_ch(interf->cur_ch);
}

bool reset_flag_mv_key(int ch, interf_t *interf, const game_t *game) {
  bool f_mv_key = is_mv_key(ch, game->state);

  if (interf->flags.f_mv_key != f_mv_key) {
    interf->ch_count = 0;
  }

  return f_mv_key;
}

bool is_mv_key(int ch, state_t state) {
  bool res = false;

  if (state == ST_MOVE) {
    switch (ch) {
      case KEY_UP:
      case KEY_LEFT:
      case KEY_RIGHT:
      case KEY_ENTER:
      case ENTER:
        res = true;
    }
  }

  return res;
}

int prevent_sticking(int ch, interf_t *interf, const game_t *game) {
  int res;

  if (game->state == ST_START || game->state == ST_SUSPEND) {
    res = ch;
  } else if (interf->flags.f_mv_key || (ch != ERR && ch == interf->cur_ch)) {
    res = check_sticking_count(ch, &interf->ch_count);
  } else {
    res = ch;
  }

  return res;
}

int check_sticking_count(int ch, int *count) {
  int res = ch;

  (*count)++;

  if (*count >= STICK) {
    res = ERR;
    *count = 0;
  }

  return res;
}

int handle_d(interf_t *interf) {
  if (interf->flags.f_debug) {
    werase(interf->subwins.w_debug);
    wrefresh(interf->subwins.w_debug);
  }

  return !interf->flags.f_debug;
}

void handle_resize(subwins_t *subwins) {
  delete_subwins(subwins);
  create_subwins(subwins);
}

input_t translate_ch(int ch) {
  input_t input;

  switch (ch) {
    case WHITESPACE:
    case ENTER:
    case KEY_ENTER:
      input.action = Pause;
      input.hold = true;
      break;
    case ESCAPE:
      input.action = Terminate;
      input.hold = true;
      break;
    case KEY_LEFT:
      input.action = Left;
      input.hold = true;
      break;
    case KEY_RIGHT:
      input.action = Right;
      input.hold = true;
      break;
    case KEY_DOWN:
      input.action = Down;
      input.hold = true;
      break;
    case KEY_UP:
      input.action = Action;
      input.hold = true;
      break;
    case ERR:
      input.action = Down;
      input.hold = false;
      break;
    default:
      input.action = Start;
      input.hold = false;
  }

  return input;
}

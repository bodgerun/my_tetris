#include "../headers/tetris_headers.h"

/* TYPES */

typedef void (*fsm_func_t)(game_t *game);
typedef piece_t (*mv_func_t)(piece_t);

/* HEADERS OF STATIC FUNCTIONS */

/* function that translates user input */
static signal_t translate_user_input(UserAction_t action, bool hold);

/* functions that return functions */
static fsm_func_t get_fsm_func(int signal, int state);
static mv_func_t get_mv_func(int dir);

/* first-level fsm functions */
static void start(game_t *game);
static void stop(game_t *game);
static void suspend(game_t *game);
static void resume(game_t *game);
static void spawn(game_t *game);
static void rotate(game_t *game);
static void left(game_t *game);
static void right(game_t *game);
static void drop(game_t *game);
static void shift(game_t *game);
static void attach(game_t *game);
static void check(game_t *game);
static void collapse(game_t *game);

/* second-level fsm functions */
static void count_score(int lines_filled, game_t *game);
static void victory(game_t *game);
static void defeat(game_t *game);
static void renew_record(game_t *game);
static void renew_params(game_t *game);
static void spawn_new_piece(game_t *game);
static bool move_piece(game_t *game, int dir);
static void drop_piece(game_t *game);

/* STATIC FSM MATRIX */

static const fsm_func_t fsm_table[8][8] = {
    {NULL, start, stop, NULL, NULL, NULL, NULL, NULL},
    {spawn, suspend, stop, spawn, spawn, spawn, spawn, spawn},
    {NULL, suspend, stop, rotate, left, right, drop, shift},
    {attach, suspend, stop, attach, attach, attach, attach, attach},
    {check, suspend, stop, check, check, check, check, check},
    {collapse, suspend, stop, collapse, collapse, collapse, collapse, collapse},
    {NULL, resume, stop, resume, resume, resume, resume, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}};

/* LIBRARY FUNCTIONS */

game_t *get_params() {
  static game_t game;
  return &game;
}

GameInfo_t get_info(game_t *game) {
  GameInfo_t game_info;
  game_info.field = game->field;
  game_info.next = game->next;
  game_info.score = game->score;
  game_info.high_score = game->high_score;
  game_info.level = game->level;
  game_info.speed = game->speed;
  game_info.pause = game->pause;

  return game_info;
}

void userInput(UserAction_t action, bool hold) {
  game_t *game = get_params();
  game->signal = translate_user_input(action, hold);
}

GameInfo_t updateCurrentState() {
  game_t *game = get_params();

  fsm_func_t func = get_fsm_func(game->signal, game->state);

  if (func) {
    func(game);
  }

  return get_info(game);
}

/* STATIC FUNCTIONS */

/* function that translates user input */

static signal_t translate_user_input(UserAction_t action, bool hold) {
  signal_t signal;

  if (hold) {
    switch (action) {
      case Pause:
        signal = SIG_SWITCH;
        break;
      case Terminate:
        signal = SIG_TERM;
        break;
      case Left:
        signal = SIG_LEFT;
        break;
      case Right:
        signal = SIG_RIGHT;
        break;
      case Down:
        signal = SIG_DOWN;
        break;
      case Action:
        signal = SIG_ACT;
        break;
      default:
        signal = SIG_NOSIG;
    }
  } else if (action == Down) {
    signal = SIG_SHIFT;
  } else {
    signal = SIG_NOSIG;
  }

  return signal;
}

/* functions that return functions */

static fsm_func_t get_fsm_func(int signal, int state) {
  return fsm_table[state][signal];
}

static mv_func_t get_mv_func(int dir) {
  mv_func_t mv_func = NULL;

  switch (dir) {
    case ROTATE:
      mv_func = rot_piece;
      break;
    case LEFT:
      mv_func = mv_piece_left;
      break;
    case RIGHT:
      mv_func = mv_piece_right;
      break;
    case DOWN:
      mv_func = mv_piece_down;
  }

  return mv_func;
}

/* first-level fsm functions */

static void start(game_t *game) {
  renew_params(game);
  game->state = ST_SPAWN;
}

static void stop(game_t *game) {
  renew_record(game);
  game->state = ST_STOP;
}

static void suspend(game_t *game) {
  game->pause = true;
  game->state_prev = game->state;
  game->state = ST_SUSPEND;
}

static void resume(game_t *game) {
  game->pause = false;
  game->state = game->state_prev;
  game->state_prev = -1;
}

static void spawn(game_t *game) {
  if (first_row_is_clear(game->field)) {
    spawn_new_piece(game);
    game->state = ST_MOVE;
  } else {
    defeat(game);
    game->state = ST_START;
  }
}

static void rotate(game_t *game) {
  move_piece(game, ROTATE);
  game->state = ST_MOVE;
}

static void left(game_t *game) {
  move_piece(game, LEFT);
  game->state = ST_MOVE;
}

static void right(game_t *game) {
  move_piece(game, RIGHT);
  game->state = ST_MOVE;
}

static void drop(game_t *game) {
  drop_piece(game);
  game->state = ST_ATTACH;
}

static void shift(game_t *game) {
  if (move_piece(game, DOWN)) {
    game->state = ST_MOVE;
  } else {
    game->state = ST_ATTACH;
  }
}

static void attach(game_t *game) {
  convert_piece_cells(game->piece_pos, GROUND, game->field);
  game->state = ST_CHECK;
}

static void check(game_t *game) {
  if (find_full_rows(game->field)) {
    game->state = ST_COLLAPSE;
  } else {
    game->state = ST_SPAWN;
  }
}

static void collapse(game_t *game) {
  int lines_filled = collapse_ground(game->field);
  count_score(lines_filled, game);

  if (game->level > 9) {
    victory(game);
    game->state = ST_START;
  } else {
    game->state = ST_SPAWN;
  }
}

/* second-level fsm functions */

static void count_score(int lines_filled, game_t *game) {
  int points = 0;

  switch (lines_filled) {
    case 1:
      points = ONE_ROW_FULL;
      break;
    case 2:
      points = TWO_ROWS_FULL;
      break;
    case 3:
      points = THREE_ROWS_FULL;
      break;
    case 4:
      points = FOUR_ROWS_FULL;
  }

  game->score += points;
  game->fresh_score += points;

  if (!game->new_record && game->score > game->high_score) {
    game->new_record = true;
  }

  if (game->new_record) {
    game->high_score = game->score;
  }

  if (game->fresh_score >= FRESH_SCORE_LIMIT) {
    game->fresh_score -= FRESH_SCORE_LIMIT;
    game->level++;
    game->speed -= SPEED_CHANGE;
  }
}

static void victory(game_t *game) {
  decorate_field(VICTORY, game->field);
  clean_next(game->next);
  renew_record(game);
  game->level = MAX_LEVEL;
  game->speed += SPEED_CHANGE;
  game->pause = true;
}

static void defeat(game_t *game) {
  decorate_field(DEFEAT, game->field);
  clean_next(game->next);
  renew_record(game);
  game->pause = true;
}

static void renew_record(game_t *game) {
  if (game->new_record) {
    write_record(game->score);
    game->new_record = false;
  }
}

static void renew_params(game_t *game) {
  clean_field(game->field);
  game->next_piece.type = get_next_piece_type();
  game->level = 1;
  game->speed = INIT_SPEED;
  game->score = 0;
  game->fresh_score = 0;
  game->pause = false;
}

static void spawn_new_piece(game_t *game) {
  game->piece = gen_new_piece(game->next_piece.type);
  game->piece_pos = calc_pos(game->piece);
  game->next_piece.type = get_next_piece_type();
  show_next_piece(game->next_piece.type, game->next);
}

static bool move_piece(game_t *game, int dir) {
  int res_code = false;
  mv_func_t mv_func = get_mv_func(dir);
  piece_t new_piece = mv_func(game->piece);
  piece_pos_t new_piece_pos = calc_pos(new_piece);

  if (piece_fits(new_piece_pos, game->field)) {
    redraw_piece(game->piece_pos, new_piece_pos, game->field);
    game->piece = new_piece;
    game->piece_pos = new_piece_pos;
    res_code = true;
  }

  return res_code;
}

static void drop_piece(game_t *game) {
  piece_pos_t old_piece_pos = game->piece_pos;

  while (!ground_is_reached(game->piece_pos, game->field)) {
    piece_t new_piece = mv_piece_down(game->piece);
    piece_pos_t new_piece_pos = calc_pos(new_piece);
    game->piece = new_piece;
    game->piece_pos = new_piece_pos;
  }

  redraw_piece(old_piece_pos, game->piece_pos, game->field);
}

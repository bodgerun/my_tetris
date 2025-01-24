#include "../headers/interface_headers.h"

/* headers of static functions */

static start_pos_t get_start_pos();
static subwins_t get_subwins(start_pos_t start_pos);
static void render_debug_info(interf_t *interf, game_t *game);
static void render_game_info(subwins_t *subwins, GameInfo_t game_info);
static void render_message(WINDOW *w_message);
static void print_overlay(WINDOW *w_board);
static void print_rectangle(WINDOW *w, int y_0, int y_1, int x_0, int x_1);
static void render_field(WINDOW *w_field, int **field, int pause);
static void render_next(WINDOW *w_next, int **next);
static void render_level(WINDOW *w_level, int level);
static void render_score(WINDOW *w_score, int score);
static void render_record(WINDOW *w_record, int record);

/* functions */

void create_subwins(subwins_t *subwins) {
  start_pos_t start_pos = get_start_pos();
  *subwins = get_subwins(start_pos);
  refresh();
}

void delete_subwins(subwins_t *subwins) {
  clear();
  delwin(subwins->w_message);
  delwin(subwins->w_field);
  delwin(subwins->w_next);
  delwin(subwins->w_level);
  delwin(subwins->w_score);
  delwin(subwins->w_record);
  delwin(subwins->w_board);
  delwin(subwins->w_debug);
}

void render(GameInfo_t game_info, game_t *game, interf_t *interf) {
  if (interf->flags.f_debug) {
    render_debug_info(interf, game);
  }

  render_game_info(&interf->subwins, game_info);

  if (game->state == ST_START) {
    render_message(interf->subwins.w_message);
  }
}

/* static functions */

static start_pos_t get_start_pos() {
  start_pos_t start_pos;
  int start_y, start_x;
  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);
  start_y = (max_y - R0_MAX_Y - 1) / 2;
  start_x = (max_x - R0_MAX_X - 1) / 2;
  start_pos.start_y = start_y > 0 ? start_y : 0;
  start_pos.start_x = start_x > 0 ? start_x : 0;
  return start_pos;
}

static subwins_t get_subwins(start_pos_t start_pos) {
  subwins_t subwins;
  subwins.w_debug = newwin(W7_H, W7_W, W7_MIN_Y, W7_MIN_X);
  subwins.w_board = newwin(W0_H, W0_W, start_pos.start_y, start_pos.start_x);
  subwins.w_field = derwin(subwins.w_board, W1_H, W1_W, W1_MIN_Y, W1_MIN_X);
  subwins.w_next = derwin(subwins.w_board, W2_H, W2_W, W2_MIN_Y, W2_MIN_X);
  subwins.w_level = derwin(subwins.w_board, W3_H, W3_W, W3_MIN_Y, W3_MIN_X);
  subwins.w_score = derwin(subwins.w_board, W4_H, W4_W, W4_MIN_Y, W4_MIN_X);
  subwins.w_record = derwin(subwins.w_board, W5_H, W5_W, W5_MIN_Y, W5_MIN_X);
  subwins.w_message = derwin(subwins.w_field, W6_H, W6_W, W6_MIN_Y, W6_MIN_X);

  return subwins;
}

static void render_debug_info(interf_t *interf, game_t *game) {
  WINDOW *win = interf->subwins.w_debug;
  wattron(win, COLOR_PAIR(5));
  mvwprintw(win, 0, 0, "DEBUG MODE");
  mvwprintw(win, 1, 0, "----------");
  mvwprintw(win, 2, 0, "iter_count:  %d", interf->iter_count);
  mvwprintw(win, 3, 0, "ch_count:    %d", interf->ch_count);
  mvwprintw(win, 4, 0, "input_0:     %-15s", show_ch(interf->cur_ch));
  mvwprintw(win, 5, 0, "input_1:     %-15s", show_signal(game->signal));
  mvwprintw(win, 6, 0, "state:       %-15s", show_state(game->state));
  mvwprintw(win, 7, 0, "state_prev:  %-15s", show_state(game->state_prev));
  mvwprintw(win, 8, 0, "level:       %-15d", game->level);
  mvwprintw(win, 9, 0, "speed:       %-15d", game->speed);
  mvwprintw(win, 10, 0, "score:       %-15d", game->score);
  mvwprintw(win, 11, 0, "fresh_score: %-15d", game->fresh_score);
  mvwprintw(win, 12, 0, "new_record:  %s", game->new_record ? YES : NO);
  mvwprintw(win, 13, 0, "pause:       %s", game->pause ? YES : NO);
  mvwprintw(win, 14, 0, "f_resumed:   %s", interf->flags.f_resumed ? YES : NO);
  mvwprintw(win, 15, 0, "sound:       %s", interf->flags.f_silent ? OFF : ON);
  wattroff(win, COLOR_PAIR(5));
  wrefresh(win);
}

static void render_game_info(subwins_t *subwins, GameInfo_t game_info) {
  print_overlay(subwins->w_board);
  render_field(subwins->w_field, game_info.field, game_info.pause);
  render_next(subwins->w_next, game_info.next);
  render_level(subwins->w_level, game_info.level);
  render_score(subwins->w_score, game_info.score);
  render_record(subwins->w_record, game_info.high_score);
}

static void render_message(WINDOW *w_message) {
  mvwprintw(w_message, 0, 0, "                ");
  mvwprintw(w_message, 1, 0, "   To start     ");
  mvwprintw(w_message, 2, 0, "  a new game,   ");
  mvwprintw(w_message, 3, 0, "  press ENTER   ");
  mvwprintw(w_message, 4, 0, " or WHITESPACE  ");
  mvwprintw(w_message, 5, 0, "                ");
  mvwprintw(w_message, 6, 0, " (ESC to exit)  ");
  mvwprintw(w_message, 7, 0, "                ");
  wrefresh(w_message);
}

static void print_overlay(WINDOW *w_board) {
  print_rectangle(w_board, R0_MIN_Y, R0_MAX_Y, R0_MIN_X, R0_MAX_X);
  print_rectangle(w_board, R1_MIN_Y, R1_MAX_Y, R1_MIN_X, R1_MAX_X);
  print_rectangle(w_board, R2_MIN_Y, R2_MAX_Y, R2_MIN_X, R2_MAX_X);
  print_rectangle(w_board, R3_MIN_Y, R3_MAX_Y, R3_MIN_X, R3_MAX_X);
  print_rectangle(w_board, R4_MIN_Y, R4_MAX_Y, R4_MIN_X, R4_MAX_X);
  print_rectangle(w_board, R5_MIN_Y, R5_MAX_Y, R5_MIN_X, R5_MAX_X);

  mvwprintw(w_board, I0_Y, I0_X, I0); /* Tetris by bodgerun, v1.1 */
  mvwprintw(w_board, I1_Y, I1_X, I1); /* Next */
  mvwprintw(w_board, I2_Y, I2_X, I2); /* Level */
  mvwprintw(w_board, I3_Y, I3_X, I3); /* Score */
  mvwprintw(w_board, I4_Y, I4_X, I4); /* Record */

  wrefresh(w_board);
}

static void print_rectangle(WINDOW *w, int y_0, int y_1, int x_0, int x_1) {
  int j;

  mvwaddch(w, y_0, x_0, ACS_ULCORNER);
  j = x_0 + 1;
  for (; j < x_1; j++) {
    mvwaddch(w, y_0, j, ACS_HLINE);
  }
  mvwaddch(w, y_0, j, ACS_URCORNER);

  for (int i = y_0 + 1; i < y_1; i++) {
    mvwaddch(w, i, x_0, ACS_VLINE);
    mvwaddch(w, i, x_1, ACS_VLINE);
  }

  mvwaddch(w, y_1, x_0, ACS_LLCORNER);
  j = x_0 + 1;
  for (; j < x_1; j++) {
    mvwaddch(w, y_1, j, ACS_HLINE);
  }
  mvwaddch(w, y_1, j, ACS_LRCORNER);
}

static void render_field(WINDOW *w_field, int **field, int pause) {
  for (int i = 0; i < FIELD_ROWS; i++) {
    for (int j = 0; j < FIELD_COLS; j++) {
      if (field[i][j] == BLOCK) {
        wattron(w_field, COLOR_PAIR(1));
      } else if (field[i][j] == GROUND) {
        wattron(w_field, COLOR_PAIR(2));
      } else if (field[i][j] == VOID_GREEN) {
        wattron(w_field, COLOR_PAIR(3));
      } else if (field[i][j] == GROUND_FULL_ROW ||
                 field[i][j] == GROUND_GREEN) {
        wattron(w_field, COLOR_PAIR(4));
      } else if (field[i][j] == VOID_RED) {
        wattron(w_field, COLOR_PAIR(5));
      } else if (field[i][j] == GROUND_RED) {
        wattron(w_field, COLOR_PAIR(6));
      }

      if (pause) {
        wattron(w_field, A_BLINK);
      }

      mvwaddstr(w_field, i, j * 2, ". ");

      wattroff(w_field, COLOR_PAIR(1));
      wattroff(w_field, COLOR_PAIR(2));
      wattroff(w_field, COLOR_PAIR(3));
      wattroff(w_field, COLOR_PAIR(4));
      wattroff(w_field, COLOR_PAIR(5));
      wattroff(w_field, COLOR_PAIR(6));
      wattroff(w_field, A_BLINK);
    }
  }

  wrefresh(w_field);
}

static void render_next(WINDOW *w_next, int **next) {
  for (int i = 0; i < NEXT_ROWS; i++) {
    for (int j = 0; j < NEXT_COLS; j++) {
      if (next[i][j] == BLOCK) {
        wattron(w_next, COLOR_PAIR(1));
      }
      mvwaddstr(w_next, i, j * 2, ". ");
      wattroff(w_next, COLOR_PAIR(1));
    }
  }

  wrefresh(w_next);
}

static void render_level(WINDOW *w_level, int level) {
  mvwprintw(w_level, 0, 0, "%1d", level);
  wrefresh(w_level);
}

static void render_score(WINDOW *w_score, int score) {
  mvwprintw(w_score, 0, 0, "%8d", score);
  wrefresh(w_score);
}

static void render_record(WINDOW *w_record, int record) {
  mvwprintw(w_record, 0, 0, "%8d", record);
  wrefresh(w_record);
}

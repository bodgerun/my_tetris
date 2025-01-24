#include "../headers/tetris_headers.h"

/* headers of static functions */

static bool check_row(int target, int y, int **field);
static bool cell_is_free(int y, int x, int **field);
static bool cell_is_ground(int y, int x, int **field);

/* library functions */

bool first_row_is_clear(int **field) {
  bool res;

  if (check_row(VOID, 0, field)) {
    res = true;
  } else {
    res = false;
  }

  return res;
}

bool row_is_full(int y, int **field) {
  bool res;

  if (check_row(GROUND, y, field)) {
    res = true;
  } else {
    res = false;
  }

  return res;
}

bool piece_fits(piece_pos_t piece_pos, int **field) {
  bool res_code = cell_is_free(piece_pos.y_0, piece_pos.x_0, field);

  if (res_code) {
    res_code = cell_is_free(piece_pos.y_1, piece_pos.x_1, field);
  }

  if (res_code) {
    res_code = cell_is_free(piece_pos.y_2, piece_pos.x_2, field);
  }

  if (res_code) {
    res_code = cell_is_free(piece_pos.y_3, piece_pos.x_3, field);
  }

  return res_code;
}

bool ground_is_reached(piece_pos_t piece_pos, int **field) {
  bool res_code = cell_is_ground(piece_pos.y_0 + 1, piece_pos.x_0, field);

  if (!res_code) {
    res_code = cell_is_ground(piece_pos.y_1 + 1, piece_pos.x_1, field);
  }

  if (!res_code) {
    res_code = cell_is_ground(piece_pos.y_2 + 1, piece_pos.x_2, field);
  }

  if (!res_code) {
    res_code = cell_is_ground(piece_pos.y_3 + 1, piece_pos.x_3, field);
  }

  return res_code;
}

bool cell_in_field(int y, int x) {
  bool res;

  if (y >= 0 && y < FIELD_ROWS && x >= 0 && x < FIELD_COLS) {
    res = true;
  } else {
    res = false;
  }

  return res;
}

/* static functions */

static bool check_row(int target, int y, int **field) {
  bool res = true;

  for (int j = 0; res && j < FIELD_COLS; j++) {
    if (field[y][j] != target) {
      res = false;
    }
  }

  return res;
}

static bool cell_is_free(int y, int x, int **field) {
  bool res;

  if (cell_in_field(y, x) && field[y][x] != GROUND) {
    res = true;
  } else if (y < 0 && x >= 0 && x < FIELD_COLS) {
    res = true;
  } else {
    res = false;
  }

  return res;
}

static bool cell_is_ground(int y, int x, int **field) {
  bool res;

  if (cell_in_field(y, x) && field[y][x] == GROUND) {
    res = true;
  } else if (y >= FIELD_ROWS) {
    res = true;
  } else {
    res = false;
  }

  return res;
}

#include "../headers/tetris_headers.h"

/* headers of static functions */

static void mark_full_row(int y, int **field);
static void collapse_row(int y, int depth, int **field);

/* library functions */

void redraw_piece(piece_pos_t src, piece_pos_t dest, int **field) {
  convert_piece_cells(src, VOID, field);
  convert_piece_cells(dest, BLOCK, field);
}

void convert_piece_cells(piece_pos_t piece_pos, int target, int **field) {
  if (cell_in_field(piece_pos.y_0, piece_pos.x_0)) {
    field[piece_pos.y_0][piece_pos.x_0] = target;
  }

  if (cell_in_field(piece_pos.y_1, piece_pos.x_1)) {
    field[piece_pos.y_1][piece_pos.x_1] = target;
  }

  if (cell_in_field(piece_pos.y_2, piece_pos.x_2)) {
    field[piece_pos.y_2][piece_pos.x_2] = target;
  }

  if (cell_in_field(piece_pos.y_3, piece_pos.x_3)) {
    field[piece_pos.y_3][piece_pos.x_3] = target;
  }
}

bool find_full_rows(int **field) {
  bool full_rows = false;

  for (int i = FIELD_ROWS - 1; i >= 0; i--) {
    if (row_is_full(i, field)) {
      mark_full_row(i, field);
      full_rows = true;
    }
  }

  return full_rows;
}

int collapse_ground(int **field) {
  int depth = 0;

  for (int i = FIELD_ROWS - 1; i >= 0; i--) {
    if (field[i][0] == GROUND_FULL_ROW) {
      depth++;
    } else if (depth) {
      collapse_row(i, depth, field);
    }
  }

  return depth;
}

void decorate_field(int reason, int **field) {
  for (int i = 0; i < FIELD_ROWS; i++) {
    for (int j = 0; j < FIELD_COLS; j++) {
      if (field[i][j] == VOID) {
        field[i][j] = reason == DEFEAT ? VOID_RED : VOID_GREEN;
      } else if (field[i][j] == GROUND) {
        field[i][j] = reason == DEFEAT ? GROUND_RED : GROUND_GREEN;
      }
    }
  }
}

void clean_field(int **field) {
  for (int i = 0; i < FIELD_ROWS; i++) {
    for (int j = 0; j < FIELD_COLS; j++) {
      field[i][j] = VOID;
    }
  }
}

/* static functions */

static void mark_full_row(int y, int **field) {
  for (int j = 0; j < FIELD_COLS; j++) {
    field[y][j] = GROUND_FULL_ROW;
  }
}

static void collapse_row(int y, int depth, int **field) {
  for (int j = 0; j < FIELD_COLS; j++) {
    field[y + depth][j] = field[y][j];
    field[y][j] = VOID;
  }
}

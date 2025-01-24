
#include "../headers/tetris_headers.h"

/* types */

typedef piece_pos_t (*calc_t)(int y, int x);

/* headers of static functions */

static int get_start_x_pos(int type);
static calc_t get_calc(int type);
static piece_pos_t calc_piece_001_00(int y, int x);
static piece_pos_t calc_piece_001_01(int y, int x);
static piece_pos_t calc_piece_010_00(int y, int x);
static piece_pos_t calc_piece_010_01(int y, int x);
static piece_pos_t calc_piece_010_10(int y, int x);
static piece_pos_t calc_piece_010_11(int y, int x);
static piece_pos_t calc_piece_011_00(int y, int x);
static piece_pos_t calc_piece_011_01(int y, int x);
static piece_pos_t calc_piece_011_10(int y, int x);
static piece_pos_t calc_piece_011_11(int y, int x);
static piece_pos_t calc_piece_100_00(int y, int x);
static piece_pos_t calc_piece_101_00(int y, int x);
static piece_pos_t calc_piece_101_01(int y, int x);
static piece_pos_t calc_piece_110_00(int y, int x);
static piece_pos_t calc_piece_110_01(int y, int x);
static piece_pos_t calc_piece_110_10(int y, int x);
static piece_pos_t calc_piece_110_11(int y, int x);
static piece_pos_t calc_piece_111_00(int y, int x);
static piece_pos_t calc_piece_111_01(int y, int x);

/* library functions */

int get_next_piece_type() {
  int type = PIECE_100_00;

  switch (1 + arc4random() % PIECE_RANGE) {
    case 1:
      type = PIECE_001_00;
      break;
    case 2:
      type = PIECE_010_00;
      break;
    case 3:
      type = PIECE_011_00;
      break;
    case 4:
      type = PIECE_100_00;
      break;
    case 5:
      type = PIECE_101_00;
      break;
    case 6:
      type = PIECE_110_00;
      break;
    case 7:
      type = PIECE_111_00;
  }

  return type;
}

piece_t gen_new_piece(int type) {
  piece_t new_piece;
  new_piece.y = -2;
  new_piece.x = get_start_x_pos(type);
  new_piece.type = type;

  return new_piece;
}

piece_t rot_piece(piece_t piece) {
  piece_t new_piece;
  new_piece.type = piece.type;
  new_piece.y = piece.y;
  new_piece.x = piece.x;

  switch (piece.type) {
    case PIECE_001_00:
      new_piece.type = PIECE_001_01;
      break;
    case PIECE_001_01:
      new_piece.type = PIECE_001_00;
      break;
    case PIECE_010_00:
      new_piece.type = PIECE_010_01;
      break;
    case PIECE_010_01:
      new_piece.type = PIECE_010_10;
      break;
    case PIECE_010_10:
      new_piece.type = PIECE_010_11;
      break;
    case PIECE_010_11:
      new_piece.type = PIECE_010_00;
      break;
    case PIECE_011_00:
      new_piece.type = PIECE_011_01;
      break;
    case PIECE_011_01:
      new_piece.type = PIECE_011_10;
      break;
    case PIECE_011_10:
      new_piece.type = PIECE_011_11;
      break;
    case PIECE_011_11:
      new_piece.type = PIECE_011_00;
      break;
    case PIECE_100_00:
      new_piece.type = PIECE_100_00;
      break;
    case PIECE_101_00:
      new_piece.type = PIECE_101_01;
      break;
    case PIECE_101_01:
      new_piece.type = PIECE_101_00;
      break;
    case PIECE_110_00:
      new_piece.type = PIECE_110_01;
      break;
    case PIECE_110_01:
      new_piece.type = PIECE_110_10;
      break;
    case PIECE_110_10:
      new_piece.type = PIECE_110_11;
      break;
    case PIECE_110_11:
      new_piece.type = PIECE_110_00;
      break;
    case PIECE_111_00:
      new_piece.type = PIECE_111_01;
      break;
    case PIECE_111_01:
      new_piece.type = PIECE_111_00;
  }

  return new_piece;
}

piece_t mv_piece_left(piece_t piece) {
  piece_t new_piece;
  new_piece.type = piece.type;
  new_piece.y = piece.y;
  new_piece.x = piece.x - 1;

  return new_piece;
}

piece_t mv_piece_right(piece_t piece) {
  piece_t new_piece;
  new_piece.type = piece.type;
  new_piece.y = piece.y;
  new_piece.x = piece.x + 1;

  return new_piece;
}

piece_t mv_piece_down(piece_t piece) {
  piece_t new_piece;
  new_piece.type = piece.type;
  new_piece.y = piece.y + 1;
  new_piece.x = piece.x;

  return new_piece;
}

piece_pos_t calc_pos(piece_t piece) {
  calc_t calc = get_calc(piece.type);

  piece_pos_t piece_pos = calc(piece.y, piece.x);

  return piece_pos;
}

/* static functions */

static int get_start_x_pos(int type) {
  int x_pos = type == PIECE_001_00 ? 3 : 4;

  return x_pos;
}

static calc_t get_calc(int type) {
  calc_t calc = NULL;

  switch (type) {
    case PIECE_001_00:
      calc = calc_piece_001_00;
      break;
    case PIECE_001_01:
      calc = calc_piece_001_01;
      break;
    case PIECE_010_00:
      calc = calc_piece_010_00;
      break;
    case PIECE_010_01:
      calc = calc_piece_010_01;
      break;
    case PIECE_010_10:
      calc = calc_piece_010_10;
      break;
    case PIECE_010_11:
      calc = calc_piece_010_11;
      break;
    case PIECE_011_00:
      calc = calc_piece_011_00;
      break;
    case PIECE_011_01:
      calc = calc_piece_011_01;
      break;
    case PIECE_011_10:
      calc = calc_piece_011_10;
      break;
    case PIECE_011_11:
      calc = calc_piece_011_11;
      break;
    case PIECE_100_00:
      calc = calc_piece_100_00;
      break;
    case PIECE_101_00:
      calc = calc_piece_101_00;
      break;
    case PIECE_101_01:
      calc = calc_piece_101_01;
      break;
    case PIECE_110_00:
      calc = calc_piece_110_00;
      break;
    case PIECE_110_01:
      calc = calc_piece_110_01;
      break;
    case PIECE_110_10:
      calc = calc_piece_110_10;
      break;
    case PIECE_110_11:
      calc = calc_piece_110_11;
      break;
    case PIECE_111_00:
      calc = calc_piece_111_00;
      break;
    case PIECE_111_01:
      calc = calc_piece_111_01;
  }

  return calc;
}

static piece_pos_t calc_piece_001_00(int y, int x) {
  /*   .         */
  /*   X X X X   */
  /*             */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 1;
  piece_pos.x_0 = x + 0;
  piece_pos.y_1 = y + 1;
  piece_pos.x_1 = x + 1;
  piece_pos.y_2 = y + 1;
  piece_pos.x_2 = x + 2;
  piece_pos.y_3 = y + 1;
  piece_pos.x_3 = x + 3;
  return piece_pos;
}

static piece_pos_t calc_piece_001_01(int y, int x) {
  /*   . X       */
  /*     X       */
  /*     X       */
  /*     X       */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 1;
  piece_pos.y_1 = y + 1;
  piece_pos.x_1 = x + 1;
  piece_pos.y_2 = y + 2;
  piece_pos.x_2 = x + 1;
  piece_pos.y_3 = y + 3;
  piece_pos.x_3 = x + 1;
  return piece_pos;
}

static piece_pos_t calc_piece_010_00(int y, int x) {
  /*   X         */
  /*   X X X     */
  /*             */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 0;
  piece_pos.y_1 = y + 1;
  piece_pos.x_1 = x + 0;
  piece_pos.y_2 = y + 1;
  piece_pos.x_2 = x + 1;
  piece_pos.y_3 = y + 1;
  piece_pos.x_3 = x + 2;
  return piece_pos;
}

static piece_pos_t calc_piece_010_01(int y, int x) {
  /*   . X       */
  /*     X       */
  /*   X X       */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 1;
  piece_pos.y_1 = y + 1;
  piece_pos.x_1 = x + 1;
  piece_pos.y_2 = y + 2;
  piece_pos.x_2 = x + 0;
  piece_pos.y_3 = y + 2;
  piece_pos.x_3 = x + 1;
  return piece_pos;
}

static piece_pos_t calc_piece_010_10(int y, int x) {
  /*   X X X     */
  /*       X     */
  /*             */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 0;
  piece_pos.y_1 = y + 0;
  piece_pos.x_1 = x + 1;
  piece_pos.y_2 = y + 0;
  piece_pos.x_2 = x + 2;
  piece_pos.y_3 = y + 1;
  piece_pos.x_3 = x + 2;
  return piece_pos;
}

static piece_pos_t calc_piece_010_11(int y, int x) {
  /*   X X       */
  /*   X         */
  /*   X         */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 0;
  piece_pos.y_1 = y + 0;
  piece_pos.x_1 = x + 1;
  piece_pos.y_2 = y + 1;
  piece_pos.x_2 = x + 0;
  piece_pos.y_3 = y + 2;
  piece_pos.x_3 = x + 0;
  return piece_pos;
}

static piece_pos_t calc_piece_011_00(int y, int x) {
  /*   .   X     */
  /*   X X X     */
  /*             */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 2;
  piece_pos.y_1 = y + 1;
  piece_pos.x_1 = x + 0;
  piece_pos.y_2 = y + 1;
  piece_pos.x_2 = x + 1;
  piece_pos.y_3 = y + 1;
  piece_pos.x_3 = x + 2;
  return piece_pos;
}

static piece_pos_t calc_piece_011_01(int y, int x) {
  /*   X X       */
  /*     X       */
  /*     X       */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 0;
  piece_pos.y_1 = y + 0;
  piece_pos.x_1 = x + 1;
  piece_pos.y_2 = y + 1;
  piece_pos.x_2 = x + 1;
  piece_pos.y_3 = y + 2;
  piece_pos.x_3 = x + 1;
  return piece_pos;
}

static piece_pos_t calc_piece_011_10(int y, int x) {
  /*   X X X     */
  /*   X         */
  /*             */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 0;
  piece_pos.y_1 = y + 0;
  piece_pos.x_1 = x + 1;
  piece_pos.y_2 = y + 0;
  piece_pos.x_2 = x + 2;
  piece_pos.y_3 = y + 1;
  piece_pos.x_3 = x + 0;
  return piece_pos;
}

static piece_pos_t calc_piece_011_11(int y, int x) {
  /*   X         */
  /*   X         */
  /*   X X       */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 0;
  piece_pos.y_1 = y + 1;
  piece_pos.x_1 = x + 0;
  piece_pos.y_2 = y + 2;
  piece_pos.x_2 = x + 0;
  piece_pos.y_3 = y + 2;
  piece_pos.x_3 = x + 1;
  return piece_pos;
}

static piece_pos_t calc_piece_100_00(int y, int x) {
  /*   X X       */
  /*   X X       */
  /*             */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 0;
  piece_pos.y_1 = y + 0;
  piece_pos.x_1 = x + 1;
  piece_pos.y_2 = y + 1;
  piece_pos.x_2 = x + 0;
  piece_pos.y_3 = y + 1;
  piece_pos.x_3 = x + 1;
  return piece_pos;
}

static piece_pos_t calc_piece_101_00(int y, int x) {
  /*   . X X     */
  /*   X X       */
  /*             */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 1;
  piece_pos.y_1 = y + 0;
  piece_pos.x_1 = x + 2;
  piece_pos.y_2 = y + 1;
  piece_pos.x_2 = x + 0;
  piece_pos.y_3 = y + 1;
  piece_pos.x_3 = x + 1;
  return piece_pos;
}

static piece_pos_t calc_piece_101_01(int y, int x) {
  /*   X         */
  /*   X X       */
  /*     X       */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 0;
  piece_pos.y_1 = y + 1;
  piece_pos.x_1 = x + 0;
  piece_pos.y_2 = y + 1;
  piece_pos.x_2 = x + 1;
  piece_pos.y_3 = y + 2;
  piece_pos.x_3 = x + 1;
  return piece_pos;
}

static piece_pos_t calc_piece_110_00(int y, int x) {
  /*   . X       */
  /*   X X X     */
  /*             */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 1;
  piece_pos.y_1 = y + 1;
  piece_pos.x_1 = x + 0;
  piece_pos.y_2 = y + 1;
  piece_pos.x_2 = x + 1;
  piece_pos.y_3 = y + 1;
  piece_pos.x_3 = x + 2;
  return piece_pos;
}

static piece_pos_t calc_piece_110_01(int y, int x) {
  /*   . X       */
  /*   X X       */
  /*     X       */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 1;
  piece_pos.y_1 = y + 1;
  piece_pos.x_1 = x + 0;
  piece_pos.y_2 = y + 1;
  piece_pos.x_2 = x + 1;
  piece_pos.y_3 = y + 2;
  piece_pos.x_3 = x + 1;
  return piece_pos;
}

static piece_pos_t calc_piece_110_10(int y, int x) {
  /*   .         */
  /*   X X X     */
  /*     X       */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 1;
  piece_pos.x_0 = x + 0;
  piece_pos.y_1 = y + 1;
  piece_pos.x_1 = x + 1;
  piece_pos.y_2 = y + 1;
  piece_pos.x_2 = x + 2;
  piece_pos.y_3 = y + 2;
  piece_pos.x_3 = x + 1;
  return piece_pos;
}

static piece_pos_t calc_piece_110_11(int y, int x) {
  /*   . X       */
  /*     X X     */
  /*     X       */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 1;
  piece_pos.y_1 = y + 1;
  piece_pos.x_1 = x + 1;
  piece_pos.y_2 = y + 1;
  piece_pos.x_2 = x + 2;
  piece_pos.y_3 = y + 2;
  piece_pos.x_3 = x + 1;
  return piece_pos;
}

static piece_pos_t calc_piece_111_00(int y, int x) {
  /*   X X       */
  /*     X X     */
  /*             */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 0;
  piece_pos.y_1 = y + 0;
  piece_pos.x_1 = x + 1;
  piece_pos.y_2 = y + 1;
  piece_pos.x_2 = x + 1;
  piece_pos.y_3 = y + 1;
  piece_pos.x_3 = x + 2;
  return piece_pos;
}

static piece_pos_t calc_piece_111_01(int y, int x) {
  /*   . X       */
  /*   X X       */
  /*   X         */
  /*             */
  piece_pos_t piece_pos;
  piece_pos.y_0 = y + 0;
  piece_pos.x_0 = x + 1;
  piece_pos.y_1 = y + 1;
  piece_pos.x_1 = x + 0;
  piece_pos.y_2 = y + 1;
  piece_pos.x_2 = x + 1;
  piece_pos.y_3 = y + 2;
  piece_pos.x_3 = x + 0;
  return piece_pos;
}

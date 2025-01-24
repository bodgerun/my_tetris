#include "../headers/tetris_headers.h"

/* headers of static functions */

static void show_piece_000_00(int **next); /* empty piece */
static void show_piece_001_00(int **next);
static void show_piece_010_00(int **next);
static void show_piece_011_00(int **next);
static void show_piece_100_00(int **next);
static void show_piece_101_00(int **next);
static void show_piece_110_00(int **next);
static void show_piece_111_00(int **next);

/* library function */

void show_next_piece(int type, int **next) {
  switch (type) {
    case PIECE_001_00:
      show_piece_001_00(next);
      break;
    case PIECE_010_00:
      show_piece_010_00(next);
      break;
    case PIECE_011_00:
      show_piece_011_00(next);
      break;
    case PIECE_100_00:
      show_piece_100_00(next);
      break;
    case PIECE_101_00:
      show_piece_101_00(next);
      break;
    case PIECE_110_00:
      show_piece_110_00(next);
      break;
    case PIECE_111_00:
      show_piece_111_00(next);
      break;
    default:
      show_piece_000_00(next);
  }
}

void clean_next(int **next) {
  for (int i = 0; i < NEXT_ROWS; i++) {
    for (int j = 0; j < NEXT_COLS; j++) {
      next[i][j] = VOID;
    }
  }
}

/* static functions */

static void show_piece_000_00(int **next) {
  /*   . . . .   */
  /*   . . . .   */
  next[0][0] = 0;
  next[0][1] = 0;
  next[0][2] = 0;
  next[0][3] = 0;
  next[1][0] = 0;
  next[1][1] = 0;
  next[1][2] = 0;
  next[1][3] = 0;
}

static void show_piece_001_00(int **next) {
  /*   . . . .   */
  /*   X X X X   */
  next[0][0] = 0;
  next[0][1] = 0;
  next[0][2] = 0;
  next[0][3] = 0;
  next[1][0] = 1;
  next[1][1] = 1;
  next[1][2] = 1;
  next[1][3] = 1;
}

static void show_piece_010_00(int **next) {
  /*   X . . .   */
  /*   X X X .   */
  next[0][0] = 1;
  next[0][1] = 0;
  next[0][2] = 0;
  next[0][3] = 0;
  next[1][0] = 1;
  next[1][1] = 1;
  next[1][2] = 1;
  next[1][3] = 0;
}

static void show_piece_011_00(int **next) {
  /*   . . X .   */
  /*   X X X .   */
  next[0][0] = 0;
  next[0][1] = 0;
  next[0][2] = 1;
  next[0][3] = 0;
  next[1][0] = 1;
  next[1][1] = 1;
  next[1][2] = 1;
  next[1][3] = 0;
}

static void show_piece_100_00(int **next) {
  /*   X X . .   */
  /*   X X . .   */
  next[0][0] = 1;
  next[0][1] = 1;
  next[0][2] = 0;
  next[0][3] = 0;
  next[1][0] = 1;
  next[1][1] = 1;
  next[1][2] = 0;
  next[1][3] = 0;
}

static void show_piece_101_00(int **next) {
  /*   . X X .   */
  /*   X X . .   */
  next[0][0] = 0;
  next[0][1] = 1;
  next[0][2] = 1;
  next[0][3] = 0;
  next[1][0] = 1;
  next[1][1] = 1;
  next[1][2] = 0;
  next[1][3] = 0;
}

static void show_piece_110_00(int **next) {
  /*   . X . .   */
  /*   X X X .   */
  next[0][0] = 0;
  next[0][1] = 1;
  next[0][2] = 0;
  next[0][3] = 0;
  next[1][0] = 1;
  next[1][1] = 1;
  next[1][2] = 1;
  next[1][3] = 0;
}

static void show_piece_111_00(int **next) {
  /*   X X . .   */
  /*   . X X .   */
  next[0][0] = 1;
  next[0][1] = 1;
  next[0][2] = 0;
  next[0][3] = 0;
  next[1][0] = 0;
  next[1][1] = 1;
  next[1][2] = 1;
  next[1][3] = 0;
}

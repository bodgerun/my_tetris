#ifndef TETRIS_DEFINES
#define TETRIS_DEFINES

/* res_codes */
#define SUCCESS 0
#define ERROR 1
#define MALLOC_ERROR -1

/* matrix dimensions */
#define FIELD_ROWS 20
#define FIELD_COLS 10
#define NEXT_ROWS 2
#define NEXT_COLS 4

/* matrix data */
#define BLOCK 1
#define VOID 0
#define GROUND -1
#define GROUND_FULL_ROW -2
#define VOID_GREEN -3   /* victory */
#define GROUND_GREEN -4 /* victory */
#define VOID_RED -5     /* defeat */
#define GROUND_RED -6   /* defeat */

/* pieces */
#define PIECE_RANGE 7  /* number of piece types */
#define PIECE_001_00 4 /* line - horisontal */
#define PIECE_001_01 5 /* line - vertical */
#define PIECE_010_00 8
#define PIECE_010_01 9
#define PIECE_010_10 10
#define PIECE_010_11 11
#define PIECE_011_00 12
#define PIECE_011_01 13
#define PIECE_011_10 14
#define PIECE_011_11 15
#define PIECE_100_00 16 /* square */
#define PIECE_101_00 20
#define PIECE_101_01 21
#define PIECE_110_00 24
#define PIECE_110_01 25
#define PIECE_110_10 26
#define PIECE_110_11 27
#define PIECE_111_00 28
#define PIECE_111_01 29

/* move directions */
#define ROTATE 0
#define LEFT 1
#define RIGHT 2
#define DOWN -1

/* game states */
#define PAUSE 0
#define VICTORY 1
#define DEFEAT -1

/* game dynamics */
#define INIT_SPEED 170
#define SPEED_CHANGE 10
#define FRESH_SCORE_LIMIT 600
#define ONE_ROW_FULL 100
#define TWO_ROWS_FULL 300
#define THREE_ROWS_FULL 700
#define FOUR_ROWS_FULL 1500
#define MAX_LEVEL 9

#endif

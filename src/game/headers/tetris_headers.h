#ifndef TETRIS_HEADERS
#define TETRIS_HEADERS

#ifdef __linux__
#undef __APPLE__
#endif

#include <stdbool.h>
#include <stdio.h>

#if defined __APPLE__
#include <stdlib.h>
#elif defined __linux__
#include <bsd/stdlib.h>
#endif

#include "tetris_defines.h"
#include "tetris_objects.h"

/* tetris_environment */
int init_matrices(int ***field, int ***next);
void delete_matrices(int ***field, int ***next);
int allocate_memory(int rows, int cols, int ***matrix);
void deallocate_memory(int rows, int **matrix);
void init_params(int **field, int **next);
int read_record();
void write_record(int record);

/* tetris_fsm */
game_t *get_params();
GameInfo_t get_info(game_t *game);
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

/* tetris_check */
bool first_row_is_clear(int **field);
bool row_is_full(int y, int **field);
bool piece_fits(piece_pos_t piece_pos, int **field);
bool ground_is_reached(piece_pos_t piece_pos, int **field);
bool cell_in_field(int y, int x);

/* tetris_piece */
int get_next_piece_type();
piece_t gen_new_piece(int type);
piece_t rot_piece(piece_t piece);
piece_t mv_piece_left(piece_t piece);
piece_t mv_piece_right(piece_t piece);
piece_t mv_piece_down(piece_t piece);
piece_pos_t calc_pos(piece_t piece);

/* tetris_field */
void redraw_piece(piece_pos_t src, piece_pos_t dest, int **field);
void convert_piece_cells(piece_pos_t piece_pos, int target, int **field);
bool find_full_rows(int **field);
int collapse_ground(int **field);
void decorate_field(int reason, int **field);
void clean_field(int **field);

/* tetris_next */
void show_next_piece(int type, int **next);
void clean_next(int **next);

#endif

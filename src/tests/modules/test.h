#ifndef TETRIS_TEST
#define TETRIS_TEST

#include <check.h>
#include <stdio.h>

#include "../../game/headers/tetris_headers.h"

void run_test(Suite *test);
Suite *tetris_piece_suite();
Suite *tetris_next_suite();
Suite *tetris_field_suite();
Suite *tetris_check_suite();
Suite *tetris_environment_suite();
Suite *tetris_fsm_suite();

#endif

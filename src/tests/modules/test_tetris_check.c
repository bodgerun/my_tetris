#include "test.h"

/* first_row_is_clear(field) --> YES */
START_TEST(tetris_check_test_1) {
  int **field;
  bool res = false;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    field[5][5] = GROUND;
    res = first_row_is_clear(field);
    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(res);
}
END_TEST

/* first_row_is_clear(field) --> NO */
START_TEST(tetris_check_test_2) {
  int **field;
  bool res = true;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    field[0][5] = GROUND;
    res = first_row_is_clear(field);
    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(!res);
}
END_TEST

/* row_is_full(... , field) --> YES */
START_TEST(tetris_check_test_3) {
  int **field;
  bool res = false;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    for (int j = 0; j < FIELD_COLS; j++) {
      field[5][j] = GROUND;
    }

    res = row_is_full(5, field);
    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(res);
}
END_TEST

/* row_is_full(... , field) --> NO */
START_TEST(tetris_check_test_4) {
  int **field;
  bool res = true;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    for (int j = 3; j < FIELD_COLS; j++) {
      field[5][j] = GROUND;
    }

    res = row_is_full(5, field);
    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(!res);
}
END_TEST

/* piece_fits(...) --> YES (in field) */
START_TEST(tetris_check_test_5) {
  int **field;
  bool res = false;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    piece_t piece = {get_next_piece_type(), 5, 5};
    piece_pos_t piece_pos = calc_pos(piece);
    res = piece_fits(piece_pos, field);
    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(res);
}
END_TEST

/* piece_fits(...) --> YES (spawned but not yet in field) */
START_TEST(tetris_check_test_6) {
  int **field;
  bool res = false;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    piece_t piece = gen_new_piece(get_next_piece_type());
    piece_pos_t piece_pos = calc_pos(piece);
    res = piece_fits(piece_pos, field);
    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(res);
}
END_TEST

/* piece_fits(...) --> NO (left border) */
START_TEST(tetris_check_test_7) {
  int **field;
  bool res = true;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    piece_t piece = {get_next_piece_type(), 5, -2};
    piece_pos_t piece_pos = calc_pos(piece);
    res = piece_fits(piece_pos, field);
    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(!res);
}
END_TEST

/* piece_fits(...) --> NO (right border) */
START_TEST(tetris_check_test_8) {
  int **field;
  bool res = true;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    piece_t piece = {get_next_piece_type(), 5, FIELD_COLS};
    piece_pos_t piece_pos = calc_pos(piece);
    res = piece_fits(piece_pos, field);
    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(!res);
}
END_TEST

/* piece_fits(...) --> NO (lower border) */
START_TEST(tetris_check_test_9) {
  int **field;
  bool res = true;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    piece_t piece = {get_next_piece_type(), FIELD_ROWS, 5};
    piece_pos_t piece_pos = calc_pos(piece);
    res = piece_fits(piece_pos, field);
    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(!res);
}
END_TEST

/* piece_fits(...) --> NO (ground) */
START_TEST(tetris_check_test_10) {
  int **field;
  bool res = true;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    piece_t piece = {get_next_piece_type(), 5, 5};
    piece_pos_t piece_pos = calc_pos(piece);

    for (int j = 0; j < FIELD_COLS; j++) {
      field[6][j] = GROUND;
    }

    res = piece_fits(piece_pos, field);
    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(!res);
}
END_TEST

/* ground_is_reached(...) --> YES (ground itself) */
START_TEST(tetris_check_test_11) {
  int **field;
  bool res = false;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    piece_t piece = {PIECE_100_00, 17, 5};
    piece_pos_t piece_pos = calc_pos(piece);

    for (int j = 0; j < FIELD_COLS; j++) {
      field[19][j] = GROUND;
    }

    res = ground_is_reached(piece_pos, field);
    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(res);
}
END_TEST

/* ground_is_reached(...) --> YES (lower board) */
START_TEST(tetris_check_test_12) {
  int **field;
  bool res = false;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    piece_t piece = {PIECE_100_00, 18, 5};
    piece_pos_t piece_pos = calc_pos(piece);
    res = ground_is_reached(piece_pos, field);
    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(res);
}
END_TEST

/* ground_is_reached(...) --> NO */
START_TEST(tetris_check_test_13) {
  int **field;
  bool res = true;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    piece_t piece = {PIECE_100_00, 5, 5};
    piece_pos_t piece_pos = calc_pos(piece);
    res = ground_is_reached(piece_pos, field);
    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(!res);
}
END_TEST

/* cell_in_field(...) --> YES */
START_TEST(tetris_check_test_14) {
  bool res = cell_in_field(5, 5);

  ck_assert(res);
}
END_TEST

/* cell_in_field(...) --> NO */
START_TEST(tetris_check_test_15) {
  bool res = cell_in_field(-1, 5);

  ck_assert(!res);
}
END_TEST

Suite *tetris_check_suite() {
  Suite *s = suite_create("tetris_check");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, tetris_check_test_1);
  tcase_add_test(tc_core, tetris_check_test_2);
  tcase_add_test(tc_core, tetris_check_test_3);
  tcase_add_test(tc_core, tetris_check_test_4);
  tcase_add_test(tc_core, tetris_check_test_5);
  tcase_add_test(tc_core, tetris_check_test_6);
  tcase_add_test(tc_core, tetris_check_test_7);
  tcase_add_test(tc_core, tetris_check_test_8);
  tcase_add_test(tc_core, tetris_check_test_9);
  tcase_add_test(tc_core, tetris_check_test_10);
  tcase_add_test(tc_core, tetris_check_test_11);
  tcase_add_test(tc_core, tetris_check_test_12);
  tcase_add_test(tc_core, tetris_check_test_13);
  tcase_add_test(tc_core, tetris_check_test_14);
  tcase_add_test(tc_core, tetris_check_test_15);
  suite_add_tcase(s, tc_core);
  return s;
}

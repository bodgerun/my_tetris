#include "test.h"

/* show_next_piece(PIECE_001_00, next) */
START_TEST(tetris_next_test_1) {
  int **next;

  int y0_x0 = -1;
  int y0_x1 = -1;
  int y0_x2 = -1;
  int y0_x3 = -1;
  int y1_x0 = -1;
  int y1_x1 = -1;
  int y1_x2 = -1;
  int y1_x3 = -1;

  int res_code = allocate_memory(NEXT_ROWS, NEXT_COLS, &next);

  if (!res_code) {
    show_next_piece(PIECE_001_00, next);

    y0_x0 = next[0][0];
    y0_x1 = next[0][1];
    y0_x2 = next[0][2];
    y0_x3 = next[0][3];
    y1_x0 = next[1][0];
    y1_x1 = next[1][1];
    y1_x2 = next[1][2];
    y1_x3 = next[1][3];

    deallocate_memory(NEXT_ROWS, next);
  }

  ck_assert_int_eq(y0_x0, 0);
  ck_assert_int_eq(y0_x1, 0);
  ck_assert_int_eq(y0_x2, 0);
  ck_assert_int_eq(y0_x3, 0);
  ck_assert_int_eq(y1_x0, 1);
  ck_assert_int_eq(y1_x1, 1);
  ck_assert_int_eq(y1_x2, 1);
  ck_assert_int_eq(y1_x3, 1);
}
END_TEST

/* show_next_piece(PIECE_010_00, next) */
START_TEST(tetris_next_test_2) {
  int **next;

  int y0_x0 = -1;
  int y0_x1 = -1;
  int y0_x2 = -1;
  int y0_x3 = -1;
  int y1_x0 = -1;
  int y1_x1 = -1;
  int y1_x2 = -1;
  int y1_x3 = -1;

  int res_code = allocate_memory(NEXT_ROWS, NEXT_COLS, &next);

  if (!res_code) {
    show_next_piece(PIECE_010_00, next);

    y0_x0 = next[0][0];
    y0_x1 = next[0][1];
    y0_x2 = next[0][2];
    y0_x3 = next[0][3];
    y1_x0 = next[1][0];
    y1_x1 = next[1][1];
    y1_x2 = next[1][2];
    y1_x3 = next[1][3];

    deallocate_memory(NEXT_ROWS, next);
  }

  ck_assert_int_eq(y0_x0, 1);
  ck_assert_int_eq(y0_x1, 0);
  ck_assert_int_eq(y0_x2, 0);
  ck_assert_int_eq(y0_x3, 0);
  ck_assert_int_eq(y1_x0, 1);
  ck_assert_int_eq(y1_x1, 1);
  ck_assert_int_eq(y1_x2, 1);
  ck_assert_int_eq(y1_x3, 0);
}
END_TEST

/* show_next_piece(PIECE_011_00, next) */
START_TEST(tetris_next_test_3) {
  int **next;

  int y0_x0 = -1;
  int y0_x1 = -1;
  int y0_x2 = -1;
  int y0_x3 = -1;
  int y1_x0 = -1;
  int y1_x1 = -1;
  int y1_x2 = -1;
  int y1_x3 = -1;

  int res_code = allocate_memory(NEXT_ROWS, NEXT_COLS, &next);

  if (!res_code) {
    show_next_piece(PIECE_011_00, next);

    y0_x0 = next[0][0];
    y0_x1 = next[0][1];
    y0_x2 = next[0][2];
    y0_x3 = next[0][3];
    y1_x0 = next[1][0];
    y1_x1 = next[1][1];
    y1_x2 = next[1][2];
    y1_x3 = next[1][3];

    deallocate_memory(NEXT_ROWS, next);
  }

  ck_assert_int_eq(y0_x0, 0);
  ck_assert_int_eq(y0_x1, 0);
  ck_assert_int_eq(y0_x2, 1);
  ck_assert_int_eq(y0_x3, 0);
  ck_assert_int_eq(y1_x0, 1);
  ck_assert_int_eq(y1_x1, 1);
  ck_assert_int_eq(y1_x2, 1);
  ck_assert_int_eq(y1_x3, 0);
}
END_TEST

/* show_next_piece(PIECE_100_00, next) */
START_TEST(tetris_next_test_4) {
  int **next;

  int y0_x0 = -1;
  int y0_x1 = -1;
  int y0_x2 = -1;
  int y0_x3 = -1;
  int y1_x0 = -1;
  int y1_x1 = -1;
  int y1_x2 = -1;
  int y1_x3 = -1;

  int res_code = allocate_memory(NEXT_ROWS, NEXT_COLS, &next);

  if (!res_code) {
    show_next_piece(PIECE_100_00, next);

    y0_x0 = next[0][0];
    y0_x1 = next[0][1];
    y0_x2 = next[0][2];
    y0_x3 = next[0][3];
    y1_x0 = next[1][0];
    y1_x1 = next[1][1];
    y1_x2 = next[1][2];
    y1_x3 = next[1][3];

    deallocate_memory(NEXT_ROWS, next);
  }

  ck_assert_int_eq(y0_x0, 1);
  ck_assert_int_eq(y0_x1, 1);
  ck_assert_int_eq(y0_x2, 0);
  ck_assert_int_eq(y0_x3, 0);
  ck_assert_int_eq(y1_x0, 1);
  ck_assert_int_eq(y1_x1, 1);
  ck_assert_int_eq(y1_x2, 0);
  ck_assert_int_eq(y1_x3, 0);
}
END_TEST

/* show_next_piece(PIECE_101_00, next) */
START_TEST(tetris_next_test_5) {
  int **next;

  int y0_x0 = -1;
  int y0_x1 = -1;
  int y0_x2 = -1;
  int y0_x3 = -1;
  int y1_x0 = -1;
  int y1_x1 = -1;
  int y1_x2 = -1;
  int y1_x3 = -1;

  int res_code = allocate_memory(NEXT_ROWS, NEXT_COLS, &next);

  if (!res_code) {
    show_next_piece(PIECE_101_00, next);

    y0_x0 = next[0][0];
    y0_x1 = next[0][1];
    y0_x2 = next[0][2];
    y0_x3 = next[0][3];
    y1_x0 = next[1][0];
    y1_x1 = next[1][1];
    y1_x2 = next[1][2];
    y1_x3 = next[1][3];

    deallocate_memory(NEXT_ROWS, next);
  }

  ck_assert_int_eq(y0_x0, 0);
  ck_assert_int_eq(y0_x1, 1);
  ck_assert_int_eq(y0_x2, 1);
  ck_assert_int_eq(y0_x3, 0);
  ck_assert_int_eq(y1_x0, 1);
  ck_assert_int_eq(y1_x1, 1);
  ck_assert_int_eq(y1_x2, 0);
  ck_assert_int_eq(y1_x3, 0);
}
END_TEST

/* show_next_piece(PIECE_110_00, next) */
START_TEST(tetris_next_test_6) {
  int **next;

  int y0_x0 = -1;
  int y0_x1 = -1;
  int y0_x2 = -1;
  int y0_x3 = -1;
  int y1_x0 = -1;
  int y1_x1 = -1;
  int y1_x2 = -1;
  int y1_x3 = -1;

  int res_code = allocate_memory(NEXT_ROWS, NEXT_COLS, &next);

  if (!res_code) {
    show_next_piece(PIECE_110_00, next);

    y0_x0 = next[0][0];
    y0_x1 = next[0][1];
    y0_x2 = next[0][2];
    y0_x3 = next[0][3];
    y1_x0 = next[1][0];
    y1_x1 = next[1][1];
    y1_x2 = next[1][2];
    y1_x3 = next[1][3];

    deallocate_memory(NEXT_ROWS, next);
  }

  ck_assert_int_eq(y0_x0, 0);
  ck_assert_int_eq(y0_x1, 1);
  ck_assert_int_eq(y0_x2, 0);
  ck_assert_int_eq(y0_x3, 0);
  ck_assert_int_eq(y1_x0, 1);
  ck_assert_int_eq(y1_x1, 1);
  ck_assert_int_eq(y1_x2, 1);
  ck_assert_int_eq(y1_x3, 0);
}
END_TEST

/* show_next_piece(PIECE_111_00, next) */
START_TEST(tetris_next_test_7) {
  int **next;

  int y0_x0 = -1;
  int y0_x1 = -1;
  int y0_x2 = -1;
  int y0_x3 = -1;
  int y1_x0 = -1;
  int y1_x1 = -1;
  int y1_x2 = -1;
  int y1_x3 = -1;

  int res_code = allocate_memory(NEXT_ROWS, NEXT_COLS, &next);

  if (!res_code) {
    show_next_piece(PIECE_111_00, next);

    y0_x0 = next[0][0];
    y0_x1 = next[0][1];
    y0_x2 = next[0][2];
    y0_x3 = next[0][3];
    y1_x0 = next[1][0];
    y1_x1 = next[1][1];
    y1_x2 = next[1][2];
    y1_x3 = next[1][3];

    deallocate_memory(NEXT_ROWS, next);
  }

  ck_assert_int_eq(y0_x0, 1);
  ck_assert_int_eq(y0_x1, 1);
  ck_assert_int_eq(y0_x2, 0);
  ck_assert_int_eq(y0_x3, 0);
  ck_assert_int_eq(y1_x0, 0);
  ck_assert_int_eq(y1_x1, 1);
  ck_assert_int_eq(y1_x2, 1);
  ck_assert_int_eq(y1_x3, 0);
}
END_TEST

/* show_next_piece(-1, next) */
START_TEST(tetris_next_test_8) {
  int **next;

  int y0_x0 = -1;
  int y0_x1 = -1;
  int y0_x2 = -1;
  int y0_x3 = -1;
  int y1_x0 = -1;
  int y1_x1 = -1;
  int y1_x2 = -1;
  int y1_x3 = -1;

  int res_code = allocate_memory(NEXT_ROWS, NEXT_COLS, &next);

  if (!res_code) {
    show_next_piece(-1, next);

    y0_x0 = next[0][0];
    y0_x1 = next[0][1];
    y0_x2 = next[0][2];
    y0_x3 = next[0][3];
    y1_x0 = next[1][0];
    y1_x1 = next[1][1];
    y1_x2 = next[1][2];
    y1_x3 = next[1][3];

    deallocate_memory(NEXT_ROWS, next);
  }

  ck_assert_int_eq(y0_x0, 0);
  ck_assert_int_eq(y0_x1, 0);
  ck_assert_int_eq(y0_x2, 0);
  ck_assert_int_eq(y0_x3, 0);
  ck_assert_int_eq(y1_x0, 0);
  ck_assert_int_eq(y1_x1, 0);
  ck_assert_int_eq(y1_x2, 0);
  ck_assert_int_eq(y1_x3, 0);
}
END_TEST

/* show_next_piece(PIECE_001_00, next); clean_next(next) */
START_TEST(tetris_next_test_9) {
  int **next;

  int y0_x0 = -1;
  int y0_x1 = -1;
  int y0_x2 = -1;
  int y0_x3 = -1;
  int y1_x0 = -1;
  int y1_x1 = -1;
  int y1_x2 = -1;
  int y1_x3 = -1;

  int res_code = allocate_memory(NEXT_ROWS, NEXT_COLS, &next);

  if (!res_code) {
    show_next_piece(PIECE_001_00, next);
    clean_next(next);

    y0_x0 = next[0][0];
    y0_x1 = next[0][1];
    y0_x2 = next[0][2];
    y0_x3 = next[0][3];
    y1_x0 = next[1][0];
    y1_x1 = next[1][1];
    y1_x2 = next[1][2];
    y1_x3 = next[1][3];

    deallocate_memory(NEXT_ROWS, next);
  }

  ck_assert_int_eq(y0_x0, 0);
  ck_assert_int_eq(y0_x1, 0);
  ck_assert_int_eq(y0_x2, 0);
  ck_assert_int_eq(y0_x3, 0);
  ck_assert_int_eq(y1_x0, 0);
  ck_assert_int_eq(y1_x1, 0);
  ck_assert_int_eq(y1_x2, 0);
  ck_assert_int_eq(y1_x3, 0);
}
END_TEST

Suite *tetris_next_suite() {
  Suite *s = suite_create("tetris_next");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, tetris_next_test_1);
  tcase_add_test(tc_core, tetris_next_test_2);
  tcase_add_test(tc_core, tetris_next_test_3);
  tcase_add_test(tc_core, tetris_next_test_4);
  tcase_add_test(tc_core, tetris_next_test_5);
  tcase_add_test(tc_core, tetris_next_test_6);
  tcase_add_test(tc_core, tetris_next_test_7);
  tcase_add_test(tc_core, tetris_next_test_8);
  tcase_add_test(tc_core, tetris_next_test_9);
  suite_add_tcase(s, tc_core);
  return s;
}

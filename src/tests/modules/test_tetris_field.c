#include "test.h"

/* convert_piece_cells(...), redraw_piece(...) */
START_TEST(tetris_field_test_1) {
  int **field;

  int piece_0_p_0 = GROUND;
  int piece_0_p_1 = GROUND;
  int piece_0_p_2 = GROUND;
  int piece_0_p_3 = GROUND;
  int piece_1_p_0 = GROUND;
  int piece_1_p_1 = GROUND;
  int piece_1_p_2 = GROUND;
  int piece_1_p_3 = GROUND;

  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    piece_t piece_0 = {get_next_piece_type(), 5, 5};
    piece_pos_t piece_pos_0 = calc_pos(piece_0);

    piece_t piece_1 = {piece_0.type, 10, 5};
    piece_pos_t piece_pos_1 = calc_pos(piece_1);

    convert_piece_cells(piece_pos_0, BLOCK, field);
    redraw_piece(piece_pos_0, piece_pos_1, field);

    piece_0_p_0 = field[piece_pos_0.y_0][piece_pos_0.x_0];
    piece_0_p_1 = field[piece_pos_0.y_1][piece_pos_0.x_1];
    piece_0_p_2 = field[piece_pos_0.y_2][piece_pos_0.x_2];
    piece_0_p_3 = field[piece_pos_0.y_3][piece_pos_0.x_3];
    piece_1_p_0 = field[piece_pos_1.y_0][piece_pos_1.x_0];
    piece_1_p_1 = field[piece_pos_1.y_1][piece_pos_1.x_1];
    piece_1_p_2 = field[piece_pos_1.y_2][piece_pos_1.x_2];
    piece_1_p_3 = field[piece_pos_1.y_3][piece_pos_1.x_3];

    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(piece_0_p_0, VOID);
  ck_assert_int_eq(piece_0_p_1, VOID);
  ck_assert_int_eq(piece_0_p_2, VOID);
  ck_assert_int_eq(piece_0_p_3, VOID);
  ck_assert_int_eq(piece_1_p_0, BLOCK);
  ck_assert_int_eq(piece_1_p_1, BLOCK);
  ck_assert_int_eq(piece_1_p_2, BLOCK);
  ck_assert_int_eq(piece_1_p_3, BLOCK);
}
END_TEST

/* find_full_rows(...) --> YES */
START_TEST(tetris_field_test_2) {
  int **field;

  int row_10 = VOID;
  int row_11 = VOID;
  int row_12 = VOID;
  int row_13 = VOID;
  int row_14 = VOID;
  int row_15 = VOID;
  int row_16 = VOID;
  int row_17 = VOID;
  int row_18 = VOID;
  int row_19 = VOID;

  bool res = false;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    for (int i = 10; i < FIELD_ROWS; i++) {
      for (int j = 0; j < FIELD_COLS; j++) {
        field[i][j] = GROUND;
      }
    }

    field[11][0] = VOID;
    field[13][1] = VOID;
    field[15][2] = VOID;
    field[17][3] = VOID;
    field[19][4] = VOID;

    res = find_full_rows(field);

    row_10 = field[10][0];
    row_11 = field[11][0];
    row_12 = field[12][0];
    row_13 = field[13][0];
    row_14 = field[14][0];
    row_15 = field[15][0];
    row_16 = field[16][0];
    row_17 = field[17][0];
    row_18 = field[18][0];
    row_19 = field[19][0];

    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(res);
  ck_assert_int_eq(row_10, GROUND_FULL_ROW);
  ck_assert_int_ne(row_11, GROUND_FULL_ROW); /* != */
  ck_assert_int_eq(row_12, GROUND_FULL_ROW);
  ck_assert_int_ne(row_13, GROUND_FULL_ROW); /* != */
  ck_assert_int_eq(row_14, GROUND_FULL_ROW);
  ck_assert_int_ne(row_15, GROUND_FULL_ROW); /* != */
  ck_assert_int_eq(row_16, GROUND_FULL_ROW);
  ck_assert_int_ne(row_17, GROUND_FULL_ROW); /* != */
  ck_assert_int_eq(row_18, GROUND_FULL_ROW);
  ck_assert_int_ne(row_19, GROUND_FULL_ROW); /* != */
}
END_TEST

/* find_full_rows(...) --> NO */
START_TEST(tetris_field_test_3) {
  int **field;

  bool res = true;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    field[19][0] = GROUND;
    field[19][1] = GROUND;
    field[19][2] = GROUND;
    field[19][3] = GROUND;
    field[19][4] = GROUND;

    res = find_full_rows(field);
    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(!res);
}
END_TEST

/* collapse_ground(int **field) */
START_TEST(tetris_field_test_4) {
  int **field;

  int p_0_0 = GROUND;
  int p_0_1 = VOID;

  int p_1_0 = GROUND;
  int p_1_1 = VOID;

  int p_2_0 = GROUND;
  int p_2_1 = VOID;

  int p_3_0 = GROUND;
  int p_3_1 = VOID;

  int p_4_0 = GROUND;
  int p_4_1 = VOID;

  int res = 0;
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    int p_0_y_0 = 11;
    int p_0_x_0 = 4;
    int p_0_y_1 = 15;
    int p_0_x_1 = 4;

    int p_1_y_0 = 13;
    int p_1_x_0 = 3;
    int p_1_y_1 = 16;
    int p_1_x_1 = 3;

    int p_2_y_0 = 15;
    int p_2_x_0 = 2;
    int p_2_y_1 = 17;
    int p_2_x_1 = 2;

    int p_3_y_0 = 17;
    int p_3_x_0 = 1;
    int p_3_y_1 = 18;
    int p_3_x_1 = 1;

    int p_4_y_0 = 19;
    int p_4_x_0 = 0;
    int p_4_y_1 = 19;
    int p_4_x_1 = 0;

    for (int i = 12; i < FIELD_ROWS; i += 2) {
      for (int j = 0; j < FIELD_COLS; j++) {
        field[i][j] = GROUND_FULL_ROW;
      }
    }

    field[p_0_y_0][p_0_x_0] = GROUND;
    field[p_1_y_0][p_1_x_0] = GROUND;
    field[p_2_y_0][p_2_x_0] = GROUND;
    field[p_3_y_0][p_3_x_0] = GROUND;
    field[p_4_y_0][p_4_x_0] = GROUND;

    res = collapse_ground(field);

    p_0_0 = field[p_0_y_0][p_0_x_0];
    p_0_1 = field[p_0_y_1][p_0_x_1];

    p_1_0 = field[p_1_y_0][p_1_x_0];
    p_1_1 = field[p_1_y_1][p_1_x_1];

    p_2_0 = field[p_2_y_0][p_2_x_0];
    p_2_1 = field[p_2_y_1][p_2_x_1];

    p_3_0 = field[p_3_y_0][p_3_x_0];
    p_3_1 = field[p_3_y_1][p_3_x_1];

    p_4_0 = field[p_4_y_0][p_4_x_0];
    p_4_1 = field[p_4_y_1][p_4_x_1];

    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(res, 4);
  ck_assert_int_eq(p_0_0, VOID);
  ck_assert_int_eq(p_0_1, GROUND);
  ck_assert_int_eq(p_1_0, VOID);
  ck_assert_int_eq(p_1_1, GROUND);
  ck_assert_int_eq(p_2_0, VOID);
  ck_assert_int_eq(p_2_1, GROUND);
  ck_assert_int_eq(p_3_0, VOID);
  ck_assert_int_eq(p_3_1, GROUND);
  ck_assert_int_eq(p_4_0, GROUND);
  ck_assert_int_eq(p_4_1, GROUND);
}
END_TEST

/* decorate_field(VICTORY, ...) */
START_TEST(tetris_field_test_5) {
  int **field;

  int y_0 = arc4random() % FIELD_ROWS;
  int x_0 = arc4random() % FIELD_COLS;

  int y_1 = arc4random() % FIELD_ROWS;
  int x_1 = arc4random() % FIELD_COLS;

  int p_0 = GROUND;
  int p_1 = VOID;

  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    field[y_0][x_0] = VOID;
    field[y_1][x_1] = GROUND;

    decorate_field(VICTORY, field);

    p_0 = field[y_0][x_0];
    p_1 = field[y_1][x_1];

    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(p_0, VOID_GREEN);
  ck_assert_int_eq(p_1, GROUND_GREEN);
}
END_TEST

/* decorate_field(DEFEAT, ...) */
START_TEST(tetris_field_test_6) {
  int **field;

  int y_0 = arc4random() % FIELD_ROWS;
  int x_0 = arc4random() % FIELD_COLS;

  int y_1 = arc4random() % FIELD_ROWS;
  int x_1 = arc4random() % FIELD_COLS;

  int p_0 = GROUND;
  int p_1 = VOID;

  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    field[y_0][x_0] = VOID;
    field[y_1][x_1] = GROUND;

    decorate_field(DEFEAT, field);

    p_0 = field[y_0][x_0];
    p_1 = field[y_1][x_1];

    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(p_0, VOID_RED);
  ck_assert_int_eq(p_1, GROUND_RED);
}
END_TEST

/* clean_field(...) */
START_TEST(tetris_field_test_7) {
  int **field;

  int y_0 = arc4random() % FIELD_ROWS;
  int x_0 = arc4random() % FIELD_COLS;

  int y_1 = arc4random() % FIELD_ROWS;
  int x_1 = arc4random() % FIELD_COLS;

  int y_2 = arc4random() % FIELD_ROWS;
  int x_2 = arc4random() % FIELD_COLS;

  int y_3 = arc4random() % FIELD_ROWS;
  int x_3 = arc4random() % FIELD_COLS;

  int y_4 = arc4random() % FIELD_ROWS;
  int x_4 = arc4random() % FIELD_COLS;

  int y_5 = arc4random() % FIELD_ROWS;
  int x_5 = arc4random() % FIELD_COLS;

  int p_0 = GROUND;
  int p_1 = GROUND;
  int p_2 = GROUND;
  int p_3 = GROUND;
  int p_4 = GROUND;
  int p_5 = GROUND;

  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, &field);

  if (!res_code) {
    field[y_0][x_0] = BLOCK;
    field[y_1][x_1] = GROUND;
    field[y_2][x_2] = VOID_GREEN;
    field[y_3][x_3] = GROUND_GREEN;
    field[y_4][x_4] = VOID_RED;
    field[y_5][x_5] = GROUND_RED;

    clean_field(field);

    p_0 = field[y_0][x_0];
    p_1 = field[y_1][x_1];
    p_2 = field[y_2][x_2];
    p_3 = field[y_3][x_3];
    p_4 = field[y_4][x_4];
    p_5 = field[y_5][x_5];

    deallocate_memory(FIELD_ROWS, field);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(p_0, VOID);
  ck_assert_int_eq(p_1, VOID);
  ck_assert_int_eq(p_2, VOID);
  ck_assert_int_eq(p_3, VOID);
  ck_assert_int_eq(p_4, VOID);
  ck_assert_int_eq(p_5, VOID);
}
END_TEST

Suite *tetris_field_suite() {
  Suite *s = suite_create("tetris_field");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, tetris_field_test_1);
  tcase_add_test(tc_core, tetris_field_test_2);
  tcase_add_test(tc_core, tetris_field_test_3);
  tcase_add_test(tc_core, tetris_field_test_4);
  tcase_add_test(tc_core, tetris_field_test_5);
  tcase_add_test(tc_core, tetris_field_test_6);
  tcase_add_test(tc_core, tetris_field_test_7);
  suite_add_tcase(s, tc_core);
  return s;
}

#include "test.h"

const int piece_prim_types[PIECE_RANGE] = {
    PIECE_001_00, PIECE_010_00, PIECE_011_00, PIECE_100_00,
    PIECE_101_00, PIECE_110_00, PIECE_111_00};

/* get_next_piece_type() ... */
START_TEST(tetris_piece_test_1) {
  int type = get_next_piece_type();

  ck_assert(type == PIECE_001_00 || type == PIECE_010_00 ||
            type == PIECE_011_00 || type == PIECE_100_00 ||
            type == PIECE_101_00 || type == PIECE_110_00 ||
            type == PIECE_111_00);
}
END_TEST

/* gen_new_piece(...) ... */
START_TEST(tetris_piece_test_2) {
  int type = piece_prim_types[_i];
  piece_t piece = gen_new_piece(type);

  ck_assert_int_eq(piece.type, type);
  ck_assert_int_eq(piece.y, -2);
  ck_assert_int_eq(piece.x, type == PIECE_001_00 ? 3 : 4);
}
END_TEST

/* rot_piece(PIECE_001_00) */
START_TEST(tetris_piece_test_3) {
  piece_t piece_0 = {PIECE_001_00, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_001_01);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_001_01) */
START_TEST(tetris_piece_test_4) {
  piece_t piece_0 = {PIECE_001_01, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_001_00);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_010_00) */
START_TEST(tetris_piece_test_5) {
  piece_t piece_0 = {PIECE_010_00, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_010_01);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_010_01) */
START_TEST(tetris_piece_test_6) {
  piece_t piece_0 = {PIECE_010_01, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_010_10);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_010_10) */
START_TEST(tetris_piece_test_7) {
  piece_t piece_0 = {PIECE_010_10, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_010_11);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_010_11) */
START_TEST(tetris_piece_test_8) {
  piece_t piece_0 = {PIECE_010_11, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_010_00);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_011_00) */
START_TEST(tetris_piece_test_9) {
  piece_t piece_0 = {PIECE_011_00, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_011_01);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_011_01) */
START_TEST(tetris_piece_test_10) {
  piece_t piece_0 = {PIECE_011_01, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_011_10);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_011_10) */
START_TEST(tetris_piece_test_11) {
  piece_t piece_0 = {PIECE_011_10, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_011_11);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_011_11) */
START_TEST(tetris_piece_test_12) {
  piece_t piece_0 = {PIECE_011_11, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_011_00);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_100_00) */
START_TEST(tetris_piece_test_13) {
  piece_t piece_0 = {PIECE_100_00, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_100_00);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_101_00) */
START_TEST(tetris_piece_test_14) {
  piece_t piece_0 = {PIECE_101_00, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_101_01);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_101_01) */
START_TEST(tetris_piece_test_15) {
  piece_t piece_0 = {PIECE_101_01, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_101_00);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_110_00) */
START_TEST(tetris_piece_test_16) {
  piece_t piece_0 = {PIECE_110_00, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_110_01);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_110_01) */
START_TEST(tetris_piece_test_17) {
  piece_t piece_0 = {PIECE_110_01, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_110_10);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_110_10) */
START_TEST(tetris_piece_test_18) {
  piece_t piece_0 = {PIECE_110_10, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_110_11);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_110_11) */
START_TEST(tetris_piece_test_19) {
  piece_t piece_0 = {PIECE_110_11, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_110_00);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_111_00) */
START_TEST(tetris_piece_test_20) {
  piece_t piece_0 = {PIECE_111_00, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_111_01);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* rot_piece(PIECE_111_01) */
START_TEST(tetris_piece_test_21) {
  piece_t piece_0 = {PIECE_111_01, 0, 0};
  piece_t piece_1 = rot_piece(piece_0);

  ck_assert_int_eq(piece_1.type, PIECE_111_00);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* mv_piece_left(...) */
START_TEST(tetris_piece_test_22) {
  int type = get_next_piece_type();
  piece_t piece_0 = {type, 0, 0};
  piece_t piece_1 = mv_piece_left(piece_0);

  ck_assert_int_eq(piece_1.type, type);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, -1);
}
END_TEST

/* mv_piece_right(...) */
START_TEST(tetris_piece_test_23) {
  int type = get_next_piece_type();
  piece_t piece_0 = {type, 0, 0};
  piece_t piece_1 = mv_piece_right(piece_0);

  ck_assert_int_eq(piece_1.type, type);
  ck_assert_int_eq(piece_1.y, 0);
  ck_assert_int_eq(piece_1.x, 1);
}
END_TEST

/* mv_piece_down(...) */
START_TEST(tetris_piece_test_24) {
  int type = get_next_piece_type();
  piece_t piece_0 = {type, 0, 0};
  piece_t piece_1 = mv_piece_down(piece_0);

  ck_assert_int_eq(piece_1.type, type);
  ck_assert_int_eq(piece_1.y, 1);
  ck_assert_int_eq(piece_1.x, 0);
}
END_TEST

/* calc_pos(PIECE_001_00) */
START_TEST(tetris_piece_test_25) {
  piece_t piece = {PIECE_001_00, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 1);
  ck_assert_int_eq(piece_pos.x_0, 0);
  ck_assert_int_eq(piece_pos.y_1, 1);
  ck_assert_int_eq(piece_pos.x_1, 1);
  ck_assert_int_eq(piece_pos.y_2, 1);
  ck_assert_int_eq(piece_pos.x_2, 2);
  ck_assert_int_eq(piece_pos.y_3, 1);
  ck_assert_int_eq(piece_pos.x_3, 3);
}
END_TEST

/* calc_pos(PIECE_001_01) */
START_TEST(tetris_piece_test_26) {
  piece_t piece = {PIECE_001_01, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 1);
  ck_assert_int_eq(piece_pos.y_1, 1);
  ck_assert_int_eq(piece_pos.x_1, 1);
  ck_assert_int_eq(piece_pos.y_2, 2);
  ck_assert_int_eq(piece_pos.x_2, 1);
  ck_assert_int_eq(piece_pos.y_3, 3);
  ck_assert_int_eq(piece_pos.x_3, 1);
}
END_TEST

/* calc_pos(PIECE_010_00) */
START_TEST(tetris_piece_test_27) {
  piece_t piece = {PIECE_010_00, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 0);
  ck_assert_int_eq(piece_pos.y_1, 1);
  ck_assert_int_eq(piece_pos.x_1, 0);
  ck_assert_int_eq(piece_pos.y_2, 1);
  ck_assert_int_eq(piece_pos.x_2, 1);
  ck_assert_int_eq(piece_pos.y_3, 1);
  ck_assert_int_eq(piece_pos.x_3, 2);
}
END_TEST

/* calc_pos(PIECE_010_01) */
START_TEST(tetris_piece_test_28) {
  piece_t piece = {PIECE_010_01, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 1);
  ck_assert_int_eq(piece_pos.y_1, 1);
  ck_assert_int_eq(piece_pos.x_1, 1);
  ck_assert_int_eq(piece_pos.y_2, 2);
  ck_assert_int_eq(piece_pos.x_2, 0);
  ck_assert_int_eq(piece_pos.y_3, 2);
  ck_assert_int_eq(piece_pos.x_3, 1);
}
END_TEST

/* calc_pos(PIECE_010_10) */
START_TEST(tetris_piece_test_29) {
  piece_t piece = {PIECE_010_10, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 0);
  ck_assert_int_eq(piece_pos.y_1, 0);
  ck_assert_int_eq(piece_pos.x_1, 1);
  ck_assert_int_eq(piece_pos.y_2, 0);
  ck_assert_int_eq(piece_pos.x_2, 2);
  ck_assert_int_eq(piece_pos.y_3, 1);
  ck_assert_int_eq(piece_pos.x_3, 2);
}
END_TEST

/* calc_pos(PIECE_010_11) */
START_TEST(tetris_piece_test_30) {
  piece_t piece = {PIECE_010_11, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 0);
  ck_assert_int_eq(piece_pos.y_1, 0);
  ck_assert_int_eq(piece_pos.x_1, 1);
  ck_assert_int_eq(piece_pos.y_2, 1);
  ck_assert_int_eq(piece_pos.x_2, 0);
  ck_assert_int_eq(piece_pos.y_3, 2);
  ck_assert_int_eq(piece_pos.x_3, 0);
}
END_TEST

/* calc_pos(PIECE_011_00) */
START_TEST(tetris_piece_test_31) {
  piece_t piece = {PIECE_011_00, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 2);
  ck_assert_int_eq(piece_pos.y_1, 1);
  ck_assert_int_eq(piece_pos.x_1, 0);
  ck_assert_int_eq(piece_pos.y_2, 1);
  ck_assert_int_eq(piece_pos.x_2, 1);
  ck_assert_int_eq(piece_pos.y_3, 1);
  ck_assert_int_eq(piece_pos.x_3, 2);
}
END_TEST

/* calc_pos(PIECE_011_01) */
START_TEST(tetris_piece_test_32) {
  piece_t piece = {PIECE_011_01, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 0);
  ck_assert_int_eq(piece_pos.y_1, 0);
  ck_assert_int_eq(piece_pos.x_1, 1);
  ck_assert_int_eq(piece_pos.y_2, 1);
  ck_assert_int_eq(piece_pos.x_2, 1);
  ck_assert_int_eq(piece_pos.y_3, 2);
  ck_assert_int_eq(piece_pos.x_3, 1);
}
END_TEST

/* calc_pos(PIECE_011_10) */
START_TEST(tetris_piece_test_33) {
  piece_t piece = {PIECE_011_10, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 0);
  ck_assert_int_eq(piece_pos.y_1, 0);
  ck_assert_int_eq(piece_pos.x_1, 1);
  ck_assert_int_eq(piece_pos.y_2, 0);
  ck_assert_int_eq(piece_pos.x_2, 2);
  ck_assert_int_eq(piece_pos.y_3, 1);
  ck_assert_int_eq(piece_pos.x_3, 0);
}
END_TEST

/* calc_pos(PIECE_011_11) */
START_TEST(tetris_piece_test_34) {
  piece_t piece = {PIECE_011_11, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 0);
  ck_assert_int_eq(piece_pos.y_1, 1);
  ck_assert_int_eq(piece_pos.x_1, 0);
  ck_assert_int_eq(piece_pos.y_2, 2);
  ck_assert_int_eq(piece_pos.x_2, 0);
  ck_assert_int_eq(piece_pos.y_3, 2);
  ck_assert_int_eq(piece_pos.x_3, 1);
}
END_TEST

/* calc_pos(PIECE_100_00) */
START_TEST(tetris_piece_test_35) {
  piece_t piece = {PIECE_100_00, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 0);
  ck_assert_int_eq(piece_pos.y_1, 0);
  ck_assert_int_eq(piece_pos.x_1, 1);
  ck_assert_int_eq(piece_pos.y_2, 1);
  ck_assert_int_eq(piece_pos.x_2, 0);
  ck_assert_int_eq(piece_pos.y_3, 1);
  ck_assert_int_eq(piece_pos.x_3, 1);
}
END_TEST

/* calc_pos(PIECE_101_00) */
START_TEST(tetris_piece_test_36) {
  piece_t piece = {PIECE_101_00, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 1);
  ck_assert_int_eq(piece_pos.y_1, 0);
  ck_assert_int_eq(piece_pos.x_1, 2);
  ck_assert_int_eq(piece_pos.y_2, 1);
  ck_assert_int_eq(piece_pos.x_2, 0);
  ck_assert_int_eq(piece_pos.y_3, 1);
  ck_assert_int_eq(piece_pos.x_3, 1);
}
END_TEST

/* calc_pos(PIECE_101_01) */
START_TEST(tetris_piece_test_37) {
  piece_t piece = {PIECE_101_01, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 0);
  ck_assert_int_eq(piece_pos.y_1, 1);
  ck_assert_int_eq(piece_pos.x_1, 0);
  ck_assert_int_eq(piece_pos.y_2, 1);
  ck_assert_int_eq(piece_pos.x_2, 1);
  ck_assert_int_eq(piece_pos.y_3, 2);
  ck_assert_int_eq(piece_pos.x_3, 1);
}
END_TEST

/* calc_pos(PIECE_110_00) */
START_TEST(tetris_piece_test_38) {
  piece_t piece = {PIECE_110_00, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 1);
  ck_assert_int_eq(piece_pos.y_1, 1);
  ck_assert_int_eq(piece_pos.x_1, 0);
  ck_assert_int_eq(piece_pos.y_2, 1);
  ck_assert_int_eq(piece_pos.x_2, 1);
  ck_assert_int_eq(piece_pos.y_3, 1);
  ck_assert_int_eq(piece_pos.x_3, 2);
}
END_TEST

/* calc_pos(PIECE_110_01) */
START_TEST(tetris_piece_test_39) {
  piece_t piece = {PIECE_110_01, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 1);
  ck_assert_int_eq(piece_pos.y_1, 1);
  ck_assert_int_eq(piece_pos.x_1, 0);
  ck_assert_int_eq(piece_pos.y_2, 1);
  ck_assert_int_eq(piece_pos.x_2, 1);
  ck_assert_int_eq(piece_pos.y_3, 2);
  ck_assert_int_eq(piece_pos.x_3, 1);
}
END_TEST

/* calc_pos(PIECE_110_10) */
START_TEST(tetris_piece_test_40) {
  piece_t piece = {PIECE_110_10, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 1);
  ck_assert_int_eq(piece_pos.x_0, 0);
  ck_assert_int_eq(piece_pos.y_1, 1);
  ck_assert_int_eq(piece_pos.x_1, 1);
  ck_assert_int_eq(piece_pos.y_2, 1);
  ck_assert_int_eq(piece_pos.x_2, 2);
  ck_assert_int_eq(piece_pos.y_3, 2);
  ck_assert_int_eq(piece_pos.x_3, 1);
}
END_TEST

/* calc_pos(PIECE_110_11) */
START_TEST(tetris_piece_test_41) {
  piece_t piece = {PIECE_110_11, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 1);
  ck_assert_int_eq(piece_pos.y_1, 1);
  ck_assert_int_eq(piece_pos.x_1, 1);
  ck_assert_int_eq(piece_pos.y_2, 1);
  ck_assert_int_eq(piece_pos.x_2, 2);
  ck_assert_int_eq(piece_pos.y_3, 2);
  ck_assert_int_eq(piece_pos.x_3, 1);
}
END_TEST

/* calc_pos(PIECE_111_00) */
START_TEST(tetris_piece_test_42) {
  piece_t piece = {PIECE_111_00, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 0);
  ck_assert_int_eq(piece_pos.y_1, 0);
  ck_assert_int_eq(piece_pos.x_1, 1);
  ck_assert_int_eq(piece_pos.y_2, 1);
  ck_assert_int_eq(piece_pos.x_2, 1);
  ck_assert_int_eq(piece_pos.y_3, 1);
  ck_assert_int_eq(piece_pos.x_3, 2);
}
END_TEST

/* calc_pos(PIECE_111_01) */
START_TEST(tetris_piece_test_43) {
  piece_t piece = {PIECE_111_01, 0, 0};
  piece_pos_t piece_pos = calc_pos(piece);

  ck_assert_int_eq(piece_pos.y_0, 0);
  ck_assert_int_eq(piece_pos.x_0, 1);
  ck_assert_int_eq(piece_pos.y_1, 1);
  ck_assert_int_eq(piece_pos.x_1, 0);
  ck_assert_int_eq(piece_pos.y_2, 1);
  ck_assert_int_eq(piece_pos.x_2, 1);
  ck_assert_int_eq(piece_pos.y_3, 2);
  ck_assert_int_eq(piece_pos.x_3, 0);
}
END_TEST

Suite *tetris_piece_suite() {
  Suite *s = suite_create("tetris_piece");
  TCase *tc_core = tcase_create("Core");
  tcase_add_loop_test(tc_core, tetris_piece_test_1, 0, 100);
  tcase_add_loop_test(tc_core, tetris_piece_test_2, 0, 7);
  tcase_add_test(tc_core, tetris_piece_test_3);
  tcase_add_test(tc_core, tetris_piece_test_4);
  tcase_add_test(tc_core, tetris_piece_test_5);
  tcase_add_test(tc_core, tetris_piece_test_6);
  tcase_add_test(tc_core, tetris_piece_test_7);
  tcase_add_test(tc_core, tetris_piece_test_8);
  tcase_add_test(tc_core, tetris_piece_test_9);
  tcase_add_test(tc_core, tetris_piece_test_10);
  tcase_add_test(tc_core, tetris_piece_test_11);
  tcase_add_test(tc_core, tetris_piece_test_12);
  tcase_add_test(tc_core, tetris_piece_test_13);
  tcase_add_test(tc_core, tetris_piece_test_14);
  tcase_add_test(tc_core, tetris_piece_test_15);
  tcase_add_test(tc_core, tetris_piece_test_16);
  tcase_add_test(tc_core, tetris_piece_test_17);
  tcase_add_test(tc_core, tetris_piece_test_18);
  tcase_add_test(tc_core, tetris_piece_test_19);
  tcase_add_test(tc_core, tetris_piece_test_20);
  tcase_add_test(tc_core, tetris_piece_test_21);
  tcase_add_test(tc_core, tetris_piece_test_22);
  tcase_add_test(tc_core, tetris_piece_test_23);
  tcase_add_test(tc_core, tetris_piece_test_24);
  tcase_add_test(tc_core, tetris_piece_test_25);
  tcase_add_test(tc_core, tetris_piece_test_26);
  tcase_add_test(tc_core, tetris_piece_test_27);
  tcase_add_test(tc_core, tetris_piece_test_28);
  tcase_add_test(tc_core, tetris_piece_test_29);
  tcase_add_test(tc_core, tetris_piece_test_30);
  tcase_add_test(tc_core, tetris_piece_test_31);
  tcase_add_test(tc_core, tetris_piece_test_32);
  tcase_add_test(tc_core, tetris_piece_test_33);
  tcase_add_test(tc_core, tetris_piece_test_34);
  tcase_add_test(tc_core, tetris_piece_test_35);
  tcase_add_test(tc_core, tetris_piece_test_36);
  tcase_add_test(tc_core, tetris_piece_test_37);
  tcase_add_test(tc_core, tetris_piece_test_38);
  tcase_add_test(tc_core, tetris_piece_test_39);
  tcase_add_test(tc_core, tetris_piece_test_40);
  tcase_add_test(tc_core, tetris_piece_test_41);
  tcase_add_test(tc_core, tetris_piece_test_42);
  tcase_add_test(tc_core, tetris_piece_test_43);
  suite_add_tcase(s, tc_core);
  return s;
}

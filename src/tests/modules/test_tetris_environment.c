#include "test.h"

/* init_matrices(...), init_params(...), delete_matrices(...) */
START_TEST(tetris_environment_test_1) {
  int **field, **next;

  bool field_was_allocated = false;
  bool next_was_allocated = false;
  int signal = -1;
  int state = -1;
  int score = -1;
  int high_score = -1;
  int level = -1;
  int speed = -1;
  bool pause = false;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();

    field_was_allocated = game->field ? true : false;
    next_was_allocated = game->next ? true : false;
    signal = game->signal;
    state = game->state;
    score = game->score;
    high_score = game->high_score;
    level = game->level;
    speed = game->speed;
    pause = game->pause;

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert(field_was_allocated);
  ck_assert(next_was_allocated);
  ck_assert_int_eq(signal, SIG_NOSIG);
  ck_assert_int_eq(state, ST_START);
  ck_assert_int_eq(score, 0);
  ck_assert_int_eq(high_score, 0);
  ck_assert_int_eq(level, 1);
  ck_assert_int_eq(speed, INIT_SPEED);
  ck_assert(pause);
  ck_assert_ptr_null(field);
  ck_assert_ptr_null(next);
}
END_TEST

/* write_record(...), read_record(...) */
START_TEST(tetris_environment_test_2) {
  int record = 99999;
  int result;

  write_record(record);

  result = read_record();

  ck_assert_int_eq(result, record);
}
END_TEST

Suite *tetris_environment_suite() {
  Suite *s = suite_create("tetris_environment");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, tetris_environment_test_1);
  tcase_add_test(tc_core, tetris_environment_test_2);
  suite_add_tcase(s, tc_core);
  return s;
}

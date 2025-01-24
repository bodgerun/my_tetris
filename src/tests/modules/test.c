#include "test.h"

void run_test(Suite *test) {
  SRunner *sr = srunner_create(test);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
  printf("\n");
}

int main() {
  printf("\nUNIT TESTS\n\n");
  run_test(tetris_piece_suite());
  run_test(tetris_next_suite());
  run_test(tetris_field_suite());
  run_test(tetris_check_suite());
  run_test(tetris_environment_suite());
  run_test(tetris_fsm_suite());
}

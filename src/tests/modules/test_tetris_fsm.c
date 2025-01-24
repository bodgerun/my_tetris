#include "test.h"

/* userInput(Start, false) --> SIG_NOSIG */
START_TEST(tetris_fsm_test_1) {
  userInput(Start, false);

  ck_assert_int_eq(get_params()->signal, SIG_NOSIG);
}
END_TEST

/* userInput(Pause, true) --> SIG_PAUSE */
START_TEST(tetris_fsm_test_2) {
  userInput(Pause, true);

  ck_assert_int_eq(get_params()->signal, SIG_SWITCH);
}
END_TEST

/* userInput(Terminate, true) --> SIG_TERM */
START_TEST(tetris_fsm_test_3) {
  userInput(Terminate, true);

  ck_assert_int_eq(get_params()->signal, SIG_TERM);
}
END_TEST

/* userInput(Left, true) --> SIG_LEFT */
START_TEST(tetris_fsm_test_4) {
  userInput(Left, true);

  ck_assert_int_eq(get_params()->signal, SIG_LEFT);
}
END_TEST

/* userInput(Right, true) --> SIG_RIGHT */
START_TEST(tetris_fsm_test_5) {
  userInput(Right, true);

  ck_assert_int_eq(get_params()->signal, SIG_RIGHT);
}
END_TEST

/* userInput(Up, true) --> SIG_NOSIG */
START_TEST(tetris_fsm_test_6) {
  userInput(Up, true);

  ck_assert_int_eq(get_params()->signal, SIG_NOSIG);
}
END_TEST

/* userInput(Down, true) --> SIG_DOWN */
START_TEST(tetris_fsm_test_7) {
  userInput(Down, true);

  ck_assert_int_eq(get_params()->signal, SIG_DOWN);
}
END_TEST

/* userInput(Down, false) --> SIG_SHIFT */
START_TEST(tetris_fsm_test_8) {
  userInput(Down, false);

  ck_assert_int_eq(get_params()->signal, SIG_SHIFT);
}
END_TEST

/* userInput(Action, true) --> SIG_ACT */
START_TEST(tetris_fsm_test_9) {
  userInput(Action, true);

  ck_assert_int_eq(get_params()->signal, SIG_ACT);
}
END_TEST

/* userInput(...) --> SIG_NOSIG */
START_TEST(tetris_fsm_test_10) {
  userInput(Action, false);

  ck_assert_int_eq(get_params()->signal, SIG_NOSIG);
}
END_TEST

/* start(...) */
START_TEST(tetris_fsm_test_11) {
  int **field, **next;

  int state = ST_STOP;
  int next_piece_type = 0;
  int level = 0;
  int speed = 0;
  int score = -1;
  int fresh_score = -1;
  bool pause = true;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_SWITCH;

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    next_piece_type = game->next_piece.type;
    level = game_info.level;
    speed = game_info.speed;
    score = game_info.score;
    fresh_score = game->fresh_score;
    pause = game_info.pause;

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_SPAWN);
  ck_assert(next_piece_type);
  ck_assert_int_eq(level, 1);
  ck_assert_int_eq(speed, INIT_SPEED);
  ck_assert_int_eq(score, 0);
  ck_assert_int_eq(fresh_score, 0);
  ck_assert(!pause);
}
END_TEST

/* stop(...) */
START_TEST(tetris_fsm_test_12) {
  int **field, **next;

  int state = ST_START;
  int record = -1;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_TERM;
    game->state = ST_SUSPEND;
    game->score = 999;
    game->new_record = true;

    updateCurrentState();

    state = game->state;
    record = read_record();

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_STOP);
  ck_assert_int_eq(record, 999);
}
END_TEST

/* suspend(...) */
START_TEST(tetris_fsm_test_13) {
  int **field, **next;

  int state = ST_STOP;
  int state_to_return = ST_STOP;
  bool pause = false;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_SWITCH;
    game->state = ST_MOVE;

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    state_to_return = game->state_prev;
    pause = game_info.pause;

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_SUSPEND);
  ck_assert_int_eq(state_to_return, ST_MOVE);
  ck_assert(pause);
}
END_TEST

/* resume(...) */
START_TEST(tetris_fsm_test_14) {
  int **field, **next;

  int state = ST_STOP;
  int state_to_return = ST_STOP;
  int pause = true;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_ACT;
    game->state = ST_SUSPEND;
    game->state_prev = ST_MOVE;

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    state_to_return = game->state_prev;
    pause = game_info.pause;

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_MOVE);
  ck_assert_int_eq(state_to_return, -1);
  ck_assert(!pause);
}
END_TEST

/* spawn(...) --> OK (first row is clear) */
START_TEST(tetris_fsm_test_15) {
  int **field, **next;

  int state = ST_STOP;
  int piece_type = 0;
  int piece_y = 0;
  int piece_x = 0;
  int piece_pos_y_0 = 0;
  int piece_pos_x_0 = 0;
  int piece_pos_y_1 = 0;
  int piece_pos_x_1 = 0;
  int piece_pos_y_2 = 0;
  int piece_pos_x_2 = 0;
  int piece_pos_y_3 = 0;
  int piece_pos_x_3 = 0;
  int next_piece_type = 0;
  int next_p_0 = GROUND;
  int next_p_1 = GROUND;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_NOSIG;
    game->state = ST_SPAWN;
    game->next_piece.type = get_next_piece_type();

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    piece_type = game->piece.type;
    piece_y = game->piece.y;
    piece_x = game->piece.x;
    piece_pos_y_0 = game->piece_pos.y_0;
    piece_pos_x_0 = game->piece_pos.x_0;
    piece_pos_y_1 = game->piece_pos.y_1;
    piece_pos_x_1 = game->piece_pos.x_1;
    piece_pos_y_2 = game->piece_pos.y_2;
    piece_pos_x_2 = game->piece_pos.x_2;
    piece_pos_y_3 = game->piece_pos.y_3;
    piece_pos_x_3 = game->piece_pos.x_3;
    next_piece_type = game->next_piece.type;
    next_p_0 = game_info.next[0][3];
    next_p_1 = game_info.next[1][1];

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_MOVE);
  ck_assert(piece_type);
  ck_assert_int_eq(piece_y, -2);
  ck_assert_int_eq(piece_x, piece_type == PIECE_001_00 ? 3 : 4);
  ck_assert(piece_pos_y_0);
  ck_assert(piece_pos_x_0);
  ck_assert(piece_pos_y_1);
  ck_assert(piece_pos_x_1);
  ck_assert(piece_pos_y_2);
  ck_assert(piece_pos_x_2);
  ck_assert(piece_pos_y_3);
  ck_assert(piece_pos_x_3);
  ck_assert(next_piece_type);
  ck_assert_int_eq(next_p_0, VOID);
  ck_assert_int_eq(next_p_1, BLOCK);
}
END_TEST

/* spawn(...) --> FAIL (first row is not clear) */
START_TEST(tetris_fsm_test_16) {
  int **field, **next;

  int state = ST_STOP;
  int p_0 = BLOCK;
  int p_1 = BLOCK;
  int next_p_0_0 = GROUND;
  int next_p_0_1 = GROUND;
  int next_p_0_2 = GROUND;
  int next_p_0_3 = GROUND;
  int next_p_1_0 = GROUND;
  int next_p_1_1 = GROUND;
  int next_p_1_2 = GROUND;
  int next_p_1_3 = GROUND;
  bool new_record = true;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_NOSIG;
    game->state = ST_SPAWN;
    game->field[0][1] = GROUND;

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    p_0 = game_info.field[0][0];
    p_1 = game_info.field[0][1];
    next_p_0_0 = game_info.next[0][0];
    next_p_0_1 = game_info.next[0][1];
    next_p_0_2 = game_info.next[0][2];
    next_p_0_3 = game_info.next[0][3];
    next_p_1_0 = game_info.next[1][0];
    next_p_1_1 = game_info.next[1][1];
    next_p_1_2 = game_info.next[1][2];
    next_p_1_3 = game_info.next[1][3];
    new_record = game->new_record;

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_START);
  ck_assert_int_eq(p_0, VOID_RED);
  ck_assert_int_eq(p_1, GROUND_RED);
  ck_assert_int_eq(next_p_0_0, VOID);
  ck_assert_int_eq(next_p_0_1, VOID);
  ck_assert_int_eq(next_p_0_2, VOID);
  ck_assert_int_eq(next_p_0_3, VOID);
  ck_assert_int_eq(next_p_1_0, VOID);
  ck_assert_int_eq(next_p_1_1, VOID);
  ck_assert_int_eq(next_p_1_2, VOID);
  ck_assert_int_eq(next_p_1_3, VOID);
  ck_assert(!new_record);
}
END_TEST

/* rotate(...) --> done */
START_TEST(tetris_fsm_test_17) {
  int **field, **next;

  int state = ST_STOP;
  int piece_type = -2;
  int piece_y = -2;
  int piece_x = -2;
  int piece_pos_y_0 = -2;
  int piece_pos_x_0 = -2;
  int piece_pos_y_1 = -2;
  int piece_pos_x_1 = -2;
  int piece_pos_y_2 = -2;
  int piece_pos_x_2 = -2;
  int piece_pos_y_3 = -2;
  int piece_pos_x_3 = -2;
  int p_1_2 = GROUND;
  int p_1_3 = GROUND;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_ACT;
    game->state = ST_MOVE;
    game->piece.type = PIECE_001_00;
    game->piece.y = -2;
    game->piece.x = 3;
    game->piece_pos = calc_pos(game->piece);
    convert_piece_cells(game->piece_pos, BLOCK, field);

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    piece_type = game->piece.type;
    piece_y = game->piece.y;
    piece_x = game->piece.x;
    piece_pos_y_0 = game->piece_pos.y_0;
    piece_pos_x_0 = game->piece_pos.x_0;
    piece_pos_y_1 = game->piece_pos.y_1;
    piece_pos_x_1 = game->piece_pos.x_1;
    piece_pos_y_2 = game->piece_pos.y_2;
    piece_pos_x_2 = game->piece_pos.x_2;
    piece_pos_y_3 = game->piece_pos.y_3;
    piece_pos_x_3 = game->piece_pos.x_3;
    p_1_2 = game_info.field[0][4];
    p_1_3 = game_info.field[1][4];

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_MOVE);
  ck_assert_int_eq(piece_type, PIECE_001_01);
  ck_assert_int_eq(piece_y, -2);
  ck_assert_int_eq(piece_x, 3);
  ck_assert_int_eq(piece_pos_y_0, -2);
  ck_assert_int_eq(piece_pos_x_0, 4);
  ck_assert_int_eq(piece_pos_y_1, -1);
  ck_assert_int_eq(piece_pos_x_1, 4);
  ck_assert_int_eq(piece_pos_y_2, 0);
  ck_assert_int_eq(piece_pos_x_2, 4);
  ck_assert_int_eq(piece_pos_y_3, 1);
  ck_assert_int_eq(piece_pos_x_3, 4);
  ck_assert_int_eq(p_1_2, BLOCK);
  ck_assert_int_eq(p_1_3, BLOCK);
}
END_TEST

/* rotate(...) --> not done */
START_TEST(tetris_fsm_test_18) {
  int **field, **next;

  int state = ST_STOP;
  int piece_type = -2;
  int piece_y = -2;
  int piece_x = -2;
  int piece_pos_y_0 = -2;
  int piece_pos_x_0 = -2;
  int piece_pos_y_1 = -2;
  int piece_pos_x_1 = -2;
  int piece_pos_y_2 = -2;
  int piece_pos_x_2 = -2;
  int piece_pos_y_3 = -2;
  int piece_pos_x_3 = -2;
  int p_0 = GROUND;
  int p_1 = GROUND;
  int p_2 = GROUND;
  int p_3 = GROUND;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_ACT;
    game->state = ST_MOVE;
    game->piece.type = PIECE_001_00;
    game->piece.y = 17;
    game->piece.x = 3;
    game->piece_pos = calc_pos(game->piece);
    convert_piece_cells(game->piece_pos, BLOCK, field);

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    piece_type = game->piece.type;
    piece_y = game->piece.y;
    piece_x = game->piece.x;
    piece_pos_y_0 = game->piece_pos.y_0;
    piece_pos_x_0 = game->piece_pos.x_0;
    piece_pos_y_1 = game->piece_pos.y_1;
    piece_pos_x_1 = game->piece_pos.x_1;
    piece_pos_y_2 = game->piece_pos.y_2;
    piece_pos_x_2 = game->piece_pos.x_2;
    piece_pos_y_3 = game->piece_pos.y_3;
    piece_pos_x_3 = game->piece_pos.x_3;
    p_0 = game_info.field[18][3];
    p_1 = game_info.field[18][4];
    p_2 = game_info.field[18][5];
    p_3 = game_info.field[18][6];

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_MOVE);
  ck_assert_int_eq(piece_type, PIECE_001_00);
  ck_assert_int_eq(piece_y, 17);
  ck_assert_int_eq(piece_x, 3);
  ck_assert_int_eq(piece_pos_y_0, 18);
  ck_assert_int_eq(piece_pos_x_0, 3);
  ck_assert_int_eq(piece_pos_y_1, 18);
  ck_assert_int_eq(piece_pos_x_1, 4);
  ck_assert_int_eq(piece_pos_y_2, 18);
  ck_assert_int_eq(piece_pos_x_2, 5);
  ck_assert_int_eq(piece_pos_y_3, 18);
  ck_assert_int_eq(piece_pos_x_3, 6);
  ck_assert_int_eq(p_0, BLOCK);
  ck_assert_int_eq(p_1, BLOCK);
  ck_assert_int_eq(p_2, BLOCK);
  ck_assert_int_eq(p_3, BLOCK);
}
END_TEST

/* left(...) --> done */
START_TEST(tetris_fsm_test_19) {
  int **field, **next;

  int state = ST_STOP;
  int piece_type = -2;
  int piece_y = -2;
  int piece_x = -2;
  int piece_pos_y_0 = -2;
  int piece_pos_x_0 = -2;
  int piece_pos_y_1 = -2;
  int piece_pos_x_1 = -2;
  int piece_pos_y_2 = -2;
  int piece_pos_x_2 = -2;
  int piece_pos_y_3 = -2;
  int piece_pos_x_3 = -2;
  int p_0_0 = GROUND;
  int p_0_1 = GROUND;
  int p_0_2 = GROUND;
  int p_0_3 = GROUND;
  int p_1_0 = GROUND;
  int p_1_1 = GROUND;
  int p_1_2 = GROUND;
  int p_1_3 = GROUND;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_LEFT;
    game->state = ST_MOVE;
    game->piece.type = PIECE_001_01;
    game->piece.y = 5;
    game->piece.x = 0;
    game->piece_pos = calc_pos(game->piece);
    convert_piece_cells(game->piece_pos, BLOCK, field);

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    piece_type = game->piece.type;
    piece_y = game->piece.y;
    piece_x = game->piece.x;
    piece_pos_y_0 = game->piece_pos.y_0;
    piece_pos_x_0 = game->piece_pos.x_0;
    piece_pos_y_1 = game->piece_pos.y_1;
    piece_pos_x_1 = game->piece_pos.x_1;
    piece_pos_y_2 = game->piece_pos.y_2;
    piece_pos_x_2 = game->piece_pos.x_2;
    piece_pos_y_3 = game->piece_pos.y_3;
    piece_pos_x_3 = game->piece_pos.x_3;
    p_0_0 = game_info.field[5][1];
    p_0_1 = game_info.field[6][1];
    p_0_2 = game_info.field[7][1];
    p_0_3 = game_info.field[8][1];
    p_1_0 = game_info.field[5][0];
    p_1_1 = game_info.field[6][0];
    p_1_2 = game_info.field[7][0];
    p_1_3 = game_info.field[8][0];

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_MOVE);
  ck_assert_int_eq(piece_type, PIECE_001_01);
  ck_assert_int_eq(piece_y, 5);
  ck_assert_int_eq(piece_x, -1);
  ck_assert_int_eq(piece_pos_y_0, 5);
  ck_assert_int_eq(piece_pos_x_0, 0);
  ck_assert_int_eq(piece_pos_y_1, 6);
  ck_assert_int_eq(piece_pos_x_1, 0);
  ck_assert_int_eq(piece_pos_y_2, 7);
  ck_assert_int_eq(piece_pos_x_2, 0);
  ck_assert_int_eq(piece_pos_y_3, 8);
  ck_assert_int_eq(piece_pos_x_3, 0);
  ck_assert_int_eq(p_0_0, VOID);
  ck_assert_int_eq(p_0_1, VOID);
  ck_assert_int_eq(p_0_2, VOID);
  ck_assert_int_eq(p_0_3, VOID);
  ck_assert_int_eq(p_1_0, BLOCK);
  ck_assert_int_eq(p_1_1, BLOCK);
  ck_assert_int_eq(p_1_2, BLOCK);
  ck_assert_int_eq(p_1_3, BLOCK);
}
END_TEST

/* left(...) --> not done */
START_TEST(tetris_fsm_test_20) {
  int **field, **next;

  int state = ST_STOP;
  int piece_type = -2;
  int piece_y = -2;
  int piece_x = -2;
  int piece_pos_y_0 = -2;
  int piece_pos_x_0 = -2;
  int piece_pos_y_1 = -2;
  int piece_pos_x_1 = -2;
  int piece_pos_y_2 = -2;
  int piece_pos_x_2 = -2;
  int piece_pos_y_3 = -2;
  int piece_pos_x_3 = -2;
  int p_0 = GROUND;
  int p_1 = GROUND;
  int p_2 = GROUND;
  int p_3 = GROUND;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_LEFT;
    game->state = ST_MOVE;
    game->piece.type = PIECE_001_01;
    game->piece.y = 5;
    game->piece.x = -1;
    game->piece_pos = calc_pos(game->piece);
    convert_piece_cells(game->piece_pos, BLOCK, field);

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    piece_type = game->piece.type;
    piece_y = game->piece.y;
    piece_x = game->piece.x;
    piece_pos_y_0 = game->piece_pos.y_0;
    piece_pos_x_0 = game->piece_pos.x_0;
    piece_pos_y_1 = game->piece_pos.y_1;
    piece_pos_x_1 = game->piece_pos.x_1;
    piece_pos_y_2 = game->piece_pos.y_2;
    piece_pos_x_2 = game->piece_pos.x_2;
    piece_pos_y_3 = game->piece_pos.y_3;
    piece_pos_x_3 = game->piece_pos.x_3;
    p_0 = game_info.field[5][0];
    p_1 = game_info.field[6][0];
    p_2 = game_info.field[7][0];
    p_3 = game_info.field[8][0];

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_MOVE);
  ck_assert_int_eq(piece_type, PIECE_001_01);
  ck_assert_int_eq(piece_y, 5);
  ck_assert_int_eq(piece_x, -1);
  ck_assert_int_eq(piece_pos_y_0, 5);
  ck_assert_int_eq(piece_pos_x_0, 0);
  ck_assert_int_eq(piece_pos_y_1, 6);
  ck_assert_int_eq(piece_pos_x_1, 0);
  ck_assert_int_eq(piece_pos_y_2, 7);
  ck_assert_int_eq(piece_pos_x_2, 0);
  ck_assert_int_eq(piece_pos_y_3, 8);
  ck_assert_int_eq(piece_pos_x_3, 0);
  ck_assert_int_eq(p_0, BLOCK);
  ck_assert_int_eq(p_1, BLOCK);
  ck_assert_int_eq(p_2, BLOCK);
  ck_assert_int_eq(p_3, BLOCK);
}
END_TEST

/* right(...) --> done */
START_TEST(tetris_fsm_test_21) {
  int **field, **next;

  int state = ST_STOP;
  int piece_type = -2;
  int piece_y = -2;
  int piece_x = -2;
  int piece_pos_y_0 = -2;
  int piece_pos_x_0 = -2;
  int piece_pos_y_1 = -2;
  int piece_pos_x_1 = -2;
  int piece_pos_y_2 = -2;
  int piece_pos_x_2 = -2;
  int piece_pos_y_3 = -2;
  int piece_pos_x_3 = -2;
  int p_0_0 = GROUND;
  int p_0_1 = GROUND;
  int p_0_2 = GROUND;
  int p_0_3 = GROUND;
  int p_1_0 = GROUND;
  int p_1_1 = GROUND;
  int p_1_2 = GROUND;
  int p_1_3 = GROUND;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_RIGHT;
    game->state = ST_MOVE;
    game->piece.type = PIECE_001_01;
    game->piece.y = 5;
    game->piece.x = 7;
    game->piece_pos = calc_pos(game->piece);
    convert_piece_cells(game->piece_pos, BLOCK, field);

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    piece_type = game->piece.type;
    piece_y = game->piece.y;
    piece_x = game->piece.x;
    piece_pos_y_0 = game->piece_pos.y_0;
    piece_pos_x_0 = game->piece_pos.x_0;
    piece_pos_y_1 = game->piece_pos.y_1;
    piece_pos_x_1 = game->piece_pos.x_1;
    piece_pos_y_2 = game->piece_pos.y_2;
    piece_pos_x_2 = game->piece_pos.x_2;
    piece_pos_y_3 = game->piece_pos.y_3;
    piece_pos_x_3 = game->piece_pos.x_3;
    p_0_0 = game_info.field[5][8];
    p_0_1 = game_info.field[6][8];
    p_0_2 = game_info.field[7][8];
    p_0_3 = game_info.field[8][8];
    p_1_0 = game_info.field[5][9];
    p_1_1 = game_info.field[6][9];
    p_1_2 = game_info.field[7][9];
    p_1_3 = game_info.field[8][9];

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_MOVE);
  ck_assert_int_eq(piece_type, PIECE_001_01);
  ck_assert_int_eq(piece_y, 5);
  ck_assert_int_eq(piece_x, 8);
  ck_assert_int_eq(piece_pos_y_0, 5);
  ck_assert_int_eq(piece_pos_x_0, 9);
  ck_assert_int_eq(piece_pos_y_1, 6);
  ck_assert_int_eq(piece_pos_x_1, 9);
  ck_assert_int_eq(piece_pos_y_2, 7);
  ck_assert_int_eq(piece_pos_x_2, 9);
  ck_assert_int_eq(piece_pos_y_3, 8);
  ck_assert_int_eq(piece_pos_x_3, 9);
  ck_assert_int_eq(p_0_0, VOID);
  ck_assert_int_eq(p_0_1, VOID);
  ck_assert_int_eq(p_0_2, VOID);
  ck_assert_int_eq(p_0_3, VOID);
  ck_assert_int_eq(p_1_0, BLOCK);
  ck_assert_int_eq(p_1_1, BLOCK);
  ck_assert_int_eq(p_1_2, BLOCK);
  ck_assert_int_eq(p_1_3, BLOCK);
}
END_TEST

/* right(...) --> not done */
START_TEST(tetris_fsm_test_22) {
  int **field, **next;

  int state = ST_STOP;
  int piece_type = -2;
  int piece_y = -2;
  int piece_x = -2;
  int piece_pos_y_0 = -2;
  int piece_pos_x_0 = -2;
  int piece_pos_y_1 = -2;
  int piece_pos_x_1 = -2;
  int piece_pos_y_2 = -2;
  int piece_pos_x_2 = -2;
  int piece_pos_y_3 = -2;
  int piece_pos_x_3 = -2;
  int p_0 = GROUND;
  int p_1 = GROUND;
  int p_2 = GROUND;
  int p_3 = GROUND;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_RIGHT;
    game->state = ST_MOVE;
    game->piece.type = PIECE_001_01;
    game->piece.y = 5;
    game->piece.x = 8;
    game->piece_pos = calc_pos(game->piece);
    convert_piece_cells(game->piece_pos, BLOCK, field);

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    piece_type = game->piece.type;
    piece_y = game->piece.y;
    piece_x = game->piece.x;
    piece_pos_y_0 = game->piece_pos.y_0;
    piece_pos_x_0 = game->piece_pos.x_0;
    piece_pos_y_1 = game->piece_pos.y_1;
    piece_pos_x_1 = game->piece_pos.x_1;
    piece_pos_y_2 = game->piece_pos.y_2;
    piece_pos_x_2 = game->piece_pos.x_2;
    piece_pos_y_3 = game->piece_pos.y_3;
    piece_pos_x_3 = game->piece_pos.x_3;
    p_0 = game_info.field[5][9];
    p_1 = game_info.field[6][9];
    p_2 = game_info.field[7][9];
    p_3 = game_info.field[8][9];

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_MOVE);
  ck_assert_int_eq(piece_type, PIECE_001_01);
  ck_assert_int_eq(piece_y, 5);
  ck_assert_int_eq(piece_x, 8);
  ck_assert_int_eq(piece_pos_y_0, 5);
  ck_assert_int_eq(piece_pos_x_0, 9);
  ck_assert_int_eq(piece_pos_y_1, 6);
  ck_assert_int_eq(piece_pos_x_1, 9);
  ck_assert_int_eq(piece_pos_y_2, 7);
  ck_assert_int_eq(piece_pos_x_2, 9);
  ck_assert_int_eq(piece_pos_y_3, 8);
  ck_assert_int_eq(piece_pos_x_3, 9);
  ck_assert_int_eq(p_0, BLOCK);
  ck_assert_int_eq(p_1, BLOCK);
  ck_assert_int_eq(p_2, BLOCK);
  ck_assert_int_eq(p_3, BLOCK);
}
END_TEST

/* drop(...) --> done */
START_TEST(tetris_fsm_test_23) {
  int **field, **next;

  int state = ST_STOP;
  int piece_type = -2;
  int piece_y = -2;
  int piece_x = -2;
  int piece_pos_y_0 = -2;
  int piece_pos_x_0 = -2;
  int piece_pos_y_1 = -2;
  int piece_pos_x_1 = -2;
  int piece_pos_y_2 = -2;
  int piece_pos_x_2 = -2;
  int piece_pos_y_3 = -2;
  int piece_pos_x_3 = -2;
  int p_0_0 = GROUND;
  int p_0_1 = GROUND;
  int p_0_2 = GROUND;
  int p_0_3 = GROUND;
  int p_1_0 = GROUND;
  int p_1_1 = GROUND;
  int p_1_2 = GROUND;
  int p_1_3 = GROUND;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_DOWN;
    game->state = ST_MOVE;
    game->piece.type = PIECE_100_00;
    game->piece.y = 5;
    game->piece.x = 4;
    game->piece_pos = calc_pos(game->piece);
    convert_piece_cells(game->piece_pos, BLOCK, field);

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    piece_type = game->piece.type;
    piece_y = game->piece.y;
    piece_x = game->piece.x;
    piece_pos_y_0 = game->piece_pos.y_0;
    piece_pos_x_0 = game->piece_pos.x_0;
    piece_pos_y_1 = game->piece_pos.y_1;
    piece_pos_x_1 = game->piece_pos.x_1;
    piece_pos_y_2 = game->piece_pos.y_2;
    piece_pos_x_2 = game->piece_pos.x_2;
    piece_pos_y_3 = game->piece_pos.y_3;
    piece_pos_x_3 = game->piece_pos.x_3;
    p_0_0 = game_info.field[5][4];
    p_0_1 = game_info.field[5][5];
    p_0_2 = game_info.field[6][4];
    p_0_3 = game_info.field[6][5];
    p_1_0 = game_info.field[18][4];
    p_1_1 = game_info.field[18][5];
    p_1_2 = game_info.field[19][4];
    p_1_3 = game_info.field[19][5];

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_ATTACH);
  ck_assert_int_eq(piece_type, PIECE_100_00);
  ck_assert_int_eq(piece_y, 18);
  ck_assert_int_eq(piece_x, 4);
  ck_assert_int_eq(piece_pos_y_0, 18);
  ck_assert_int_eq(piece_pos_x_0, 4);
  ck_assert_int_eq(piece_pos_y_1, 18);
  ck_assert_int_eq(piece_pos_x_1, 5);
  ck_assert_int_eq(piece_pos_y_2, 19);
  ck_assert_int_eq(piece_pos_x_2, 4);
  ck_assert_int_eq(piece_pos_y_3, 19);
  ck_assert_int_eq(piece_pos_x_3, 5);
  ck_assert_int_eq(p_0_0, VOID);
  ck_assert_int_eq(p_0_1, VOID);
  ck_assert_int_eq(p_0_2, VOID);
  ck_assert_int_eq(p_0_3, VOID);
  ck_assert_int_eq(p_1_0, BLOCK);
  ck_assert_int_eq(p_1_1, BLOCK);
  ck_assert_int_eq(p_1_2, BLOCK);
  ck_assert_int_eq(p_1_3, BLOCK);
}
END_TEST

/* drop(...) --> not done */
START_TEST(tetris_fsm_test_24) {
  int **field, **next;

  int state = ST_STOP;
  int piece_type = -2;
  int piece_y = -2;
  int piece_x = -2;
  int piece_pos_y_0 = -2;
  int piece_pos_x_0 = -2;
  int piece_pos_y_1 = -2;
  int piece_pos_x_1 = -2;
  int piece_pos_y_2 = -2;
  int piece_pos_x_2 = -2;
  int piece_pos_y_3 = -2;
  int piece_pos_x_3 = -2;
  int p_0 = GROUND;
  int p_1 = GROUND;
  int p_2 = GROUND;
  int p_3 = GROUND;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_DOWN;
    game->state = ST_MOVE;
    game->piece.type = PIECE_100_00;
    game->piece.y = 18;
    game->piece.x = 4;
    game->piece_pos = calc_pos(game->piece);
    convert_piece_cells(game->piece_pos, BLOCK, field);

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    piece_type = game->piece.type;
    piece_y = game->piece.y;
    piece_x = game->piece.x;
    piece_pos_y_0 = game->piece_pos.y_0;
    piece_pos_x_0 = game->piece_pos.x_0;
    piece_pos_y_1 = game->piece_pos.y_1;
    piece_pos_x_1 = game->piece_pos.x_1;
    piece_pos_y_2 = game->piece_pos.y_2;
    piece_pos_x_2 = game->piece_pos.x_2;
    piece_pos_y_3 = game->piece_pos.y_3;
    piece_pos_x_3 = game->piece_pos.x_3;
    p_0 = game_info.field[18][4];
    p_1 = game_info.field[18][5];
    p_2 = game_info.field[19][4];
    p_3 = game_info.field[19][5];

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_ATTACH);
  ck_assert_int_eq(piece_type, PIECE_100_00);
  ck_assert_int_eq(piece_y, 18);
  ck_assert_int_eq(piece_x, 4);
  ck_assert_int_eq(piece_pos_y_0, 18);
  ck_assert_int_eq(piece_pos_x_0, 4);
  ck_assert_int_eq(piece_pos_y_1, 18);
  ck_assert_int_eq(piece_pos_x_1, 5);
  ck_assert_int_eq(piece_pos_y_2, 19);
  ck_assert_int_eq(piece_pos_x_2, 4);
  ck_assert_int_eq(piece_pos_y_3, 19);
  ck_assert_int_eq(piece_pos_x_3, 5);
  ck_assert_int_eq(p_0, BLOCK);
  ck_assert_int_eq(p_1, BLOCK);
  ck_assert_int_eq(p_2, BLOCK);
  ck_assert_int_eq(p_3, BLOCK);
}
END_TEST

/* shift(...) --> move */
START_TEST(tetris_fsm_test_25) {
  int **field, **next;

  int state = ST_STOP;
  int piece_type = -2;
  int piece_y = -2;
  int piece_x = -2;
  int piece_pos_y_0 = -2;
  int piece_pos_x_0 = -2;
  int piece_pos_y_1 = -2;
  int piece_pos_x_1 = -2;
  int piece_pos_y_2 = -2;
  int piece_pos_x_2 = -2;
  int piece_pos_y_3 = -2;
  int piece_pos_x_3 = -2;
  int p_0_0 = GROUND;
  int p_0_1 = GROUND;
  int p_0_2 = GROUND;
  int p_0_3 = GROUND;
  int p_1_0 = GROUND;
  int p_1_1 = GROUND;
  int p_1_2 = GROUND;
  int p_1_3 = GROUND;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_SHIFT;
    game->state = ST_MOVE;
    game->piece.type = PIECE_001_00;
    game->piece.y = 17;
    game->piece.x = 3;
    game->piece_pos = calc_pos(game->piece);
    convert_piece_cells(game->piece_pos, BLOCK, field);

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    piece_type = game->piece.type;
    piece_y = game->piece.y;
    piece_x = game->piece.x;
    piece_pos_y_0 = game->piece_pos.y_0;
    piece_pos_x_0 = game->piece_pos.x_0;
    piece_pos_y_1 = game->piece_pos.y_1;
    piece_pos_x_1 = game->piece_pos.x_1;
    piece_pos_y_2 = game->piece_pos.y_2;
    piece_pos_x_2 = game->piece_pos.x_2;
    piece_pos_y_3 = game->piece_pos.y_3;
    piece_pos_x_3 = game->piece_pos.x_3;
    p_0_0 = game_info.field[18][3];
    p_0_1 = game_info.field[18][4];
    p_0_2 = game_info.field[18][5];
    p_0_3 = game_info.field[18][6];
    p_1_0 = game_info.field[19][3];
    p_1_1 = game_info.field[19][4];
    p_1_2 = game_info.field[19][5];
    p_1_3 = game_info.field[19][6];

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_MOVE);
  ck_assert_int_eq(piece_type, PIECE_001_00);
  ck_assert_int_eq(piece_y, 18);
  ck_assert_int_eq(piece_x, 3);
  ck_assert_int_eq(piece_pos_y_0, 19);
  ck_assert_int_eq(piece_pos_x_0, 3);
  ck_assert_int_eq(piece_pos_y_1, 19);
  ck_assert_int_eq(piece_pos_x_1, 4);
  ck_assert_int_eq(piece_pos_y_2, 19);
  ck_assert_int_eq(piece_pos_x_2, 5);
  ck_assert_int_eq(piece_pos_y_3, 19);
  ck_assert_int_eq(piece_pos_x_3, 6);
  ck_assert_int_eq(p_0_0, VOID);
  ck_assert_int_eq(p_0_1, VOID);
  ck_assert_int_eq(p_0_2, VOID);
  ck_assert_int_eq(p_0_3, VOID);
  ck_assert_int_eq(p_1_0, BLOCK);
  ck_assert_int_eq(p_1_1, BLOCK);
  ck_assert_int_eq(p_1_2, BLOCK);
  ck_assert_int_eq(p_1_3, BLOCK);
}
END_TEST

/* shift(...) --> attach */
START_TEST(tetris_fsm_test_26) {
  int **field, **next;

  int state = ST_STOP;
  int piece_type = -2;
  int piece_y = -2;
  int piece_x = -2;
  int piece_pos_y_0 = -2;
  int piece_pos_x_0 = -2;
  int piece_pos_y_1 = -2;
  int piece_pos_x_1 = -2;
  int piece_pos_y_2 = -2;
  int piece_pos_x_2 = -2;
  int piece_pos_y_3 = -2;
  int piece_pos_x_3 = -2;
  int p_0 = GROUND;
  int p_1 = GROUND;
  int p_2 = GROUND;
  int p_3 = GROUND;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_SHIFT;
    game->state = ST_MOVE;
    game->piece.type = PIECE_001_00;
    game->piece.y = 18;
    game->piece.x = 3;
    game->piece_pos = calc_pos(game->piece);
    convert_piece_cells(game->piece_pos, BLOCK, field);

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    piece_type = game->piece.type;
    piece_y = game->piece.y;
    piece_x = game->piece.x;
    piece_pos_y_0 = game->piece_pos.y_0;
    piece_pos_x_0 = game->piece_pos.x_0;
    piece_pos_y_1 = game->piece_pos.y_1;
    piece_pos_x_1 = game->piece_pos.x_1;
    piece_pos_y_2 = game->piece_pos.y_2;
    piece_pos_x_2 = game->piece_pos.x_2;
    piece_pos_y_3 = game->piece_pos.y_3;
    piece_pos_x_3 = game->piece_pos.x_3;
    p_0 = game_info.field[19][3];
    p_1 = game_info.field[19][4];
    p_2 = game_info.field[19][5];
    p_3 = game_info.field[19][6];

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_ATTACH);
  ck_assert_int_eq(piece_type, PIECE_001_00);
  ck_assert_int_eq(piece_y, 18);
  ck_assert_int_eq(piece_x, 3);
  ck_assert_int_eq(piece_pos_y_0, 19);
  ck_assert_int_eq(piece_pos_x_0, 3);
  ck_assert_int_eq(piece_pos_y_1, 19);
  ck_assert_int_eq(piece_pos_x_1, 4);
  ck_assert_int_eq(piece_pos_y_2, 19);
  ck_assert_int_eq(piece_pos_x_2, 5);
  ck_assert_int_eq(piece_pos_y_3, 19);
  ck_assert_int_eq(piece_pos_x_3, 6);
  ck_assert_int_eq(p_0, BLOCK);
  ck_assert_int_eq(p_1, BLOCK);
  ck_assert_int_eq(p_2, BLOCK);
  ck_assert_int_eq(p_3, BLOCK);
}
END_TEST

/* attach(...) */
START_TEST(tetris_fsm_test_27) {
  int **field, **next;

  int state = ST_STOP;
  int p_0 = VOID;
  int p_1 = VOID;
  int p_2 = VOID;
  int p_3 = VOID;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_NOSIG;
    game->state = ST_ATTACH;
    game->piece.type = PIECE_001_00;
    game->piece.y = 18;
    game->piece.x = 3;
    game->piece_pos = calc_pos(game->piece);
    convert_piece_cells(game->piece_pos, BLOCK, field);

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    p_0 = game_info.field[19][3];
    p_1 = game_info.field[19][4];
    p_2 = game_info.field[19][5];
    p_3 = game_info.field[19][6];

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_CHECK);
  ck_assert_int_eq(p_0, GROUND);
  ck_assert_int_eq(p_1, GROUND);
  ck_assert_int_eq(p_2, GROUND);
  ck_assert_int_eq(p_3, GROUND);
}
END_TEST

/* check(...) --> no full rows */
START_TEST(tetris_fsm_test_28) {
  int **field, **next;

  int state = ST_STOP;
  int p = VOID;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_NOSIG;
    game->state = ST_CHECK;

    for (int j = 0; j < FIELD_COLS - 1; j++) {
      game->field[19][j] = GROUND;
    }

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    p = game_info.field[19][0];

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_SPAWN);
  ck_assert_int_eq(p, GROUND);
}
END_TEST

/* check(...) --> one full row */
START_TEST(tetris_fsm_test_29) {
  int **field, **next;

  int state = ST_STOP;
  int p = VOID;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_NOSIG;
    game->state = ST_CHECK;

    for (int j = 0; j < FIELD_COLS; j++) {
      game->field[19][j] = GROUND;
    }

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    p = game_info.field[19][0];

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_COLLAPSE);
  ck_assert_int_eq(p, GROUND_FULL_ROW);
}
END_TEST

/* collapse(...) --> one row */
START_TEST(tetris_fsm_test_30) {
  int **field, **next;

  int state = ST_STOP;
  int p_0 = BLOCK;
  int p_1 = BLOCK;
  int score = -1;
  int high_score = -1;
  int level = -1;
  int speed = -1;
  bool new_record = true;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_NOSIG;
    game->state = ST_COLLAPSE;
    game->high_score = 999;

    game->field[18][0] = GROUND;
    game->field[19][0] = GROUND_FULL_ROW;

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    p_0 = game_info.field[18][0];
    p_1 = game_info.field[19][0];
    score = game_info.score;
    high_score = game_info.high_score;
    level = game_info.level;
    speed = game_info.speed;
    new_record = game->new_record;

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_SPAWN);
  ck_assert_int_eq(p_0, VOID);
  ck_assert_int_eq(p_1, GROUND);
  ck_assert_int_eq(score, ONE_ROW_FULL);
  ck_assert_int_eq(high_score, 999);
  ck_assert_int_eq(level, 1);
  ck_assert_int_eq(speed, INIT_SPEED);
  ck_assert(!new_record);
}
END_TEST

/* collapse(...) --> two rows */
START_TEST(tetris_fsm_test_31) {
  int **field, **next;

  int state = ST_STOP;
  int p_0 = BLOCK;
  int p_1 = BLOCK;
  int score = -1;
  int high_score = -1;
  int level = -1;
  int speed = -1;
  bool new_record = true;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_NOSIG;
    game->state = ST_COLLAPSE;
    game->high_score = 999;

    game->field[17][0] = GROUND;
    game->field[18][0] = GROUND_FULL_ROW;
    game->field[19][0] = GROUND_FULL_ROW;

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    p_0 = game_info.field[17][0];
    p_1 = game_info.field[19][0];
    score = game_info.score;
    high_score = game_info.high_score;
    level = game_info.level;
    speed = game_info.speed;
    new_record = game->new_record;

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_SPAWN);
  ck_assert_int_eq(p_0, VOID);
  ck_assert_int_eq(p_1, GROUND);
  ck_assert_int_eq(score, TWO_ROWS_FULL);
  ck_assert_int_eq(high_score, 999);
  ck_assert_int_eq(level, 1);
  ck_assert_int_eq(speed, INIT_SPEED);
  ck_assert(!new_record);
}
END_TEST

/* collapse(...) --> three rows */
START_TEST(tetris_fsm_test_32) {
  int **field, **next;

  int state = ST_STOP;
  int p_0 = BLOCK;
  int p_1 = BLOCK;
  int score = -1;
  int high_score = -1;
  int level = -1;
  int speed = -1;
  bool new_record = true;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_NOSIG;
    game->state = ST_COLLAPSE;
    game->high_score = 999;

    game->field[16][0] = GROUND;
    game->field[17][0] = GROUND_FULL_ROW;
    game->field[18][0] = GROUND_FULL_ROW;
    game->field[19][0] = GROUND_FULL_ROW;

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    p_0 = game_info.field[16][0];
    p_1 = game_info.field[19][0];
    score = game_info.score;
    high_score = game_info.high_score;
    level = game_info.level;
    speed = game_info.speed;
    new_record = game->new_record;

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_SPAWN);
  ck_assert_int_eq(p_0, VOID);
  ck_assert_int_eq(p_1, GROUND);
  ck_assert_int_eq(score, THREE_ROWS_FULL);
  ck_assert_int_eq(level, 2);
  ck_assert_int_eq(high_score, 999);
  ck_assert_int_eq(speed, INIT_SPEED - SPEED_CHANGE);
  ck_assert(!new_record);
}
END_TEST

/* collapse(...) --> four rows, new record, ST_SPAWN */
START_TEST(tetris_fsm_test_33) {
  int **field, **next;

  int state = ST_STOP;
  int p_0 = BLOCK;
  int p_1 = BLOCK;
  int score = -1;
  int high_score = -1;
  int level = -1;
  int speed = -1;
  bool new_record = true;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_NOSIG;
    game->state = ST_COLLAPSE;
    game->high_score = 999;

    game->field[15][0] = GROUND;
    game->field[16][0] = GROUND_FULL_ROW;
    game->field[17][0] = GROUND_FULL_ROW;
    game->field[18][0] = GROUND_FULL_ROW;
    game->field[19][0] = GROUND_FULL_ROW;

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    p_0 = game_info.field[15][0];
    p_1 = game_info.field[19][0];
    score = game_info.score;
    high_score = game_info.high_score;
    level = game_info.level;
    speed = game_info.speed;
    new_record = game->new_record;

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_SPAWN);
  ck_assert_int_eq(p_0, VOID);
  ck_assert_int_eq(p_1, GROUND);
  ck_assert_int_eq(score, FOUR_ROWS_FULL);
  ck_assert_int_eq(level, 2);
  ck_assert_int_eq(high_score, FOUR_ROWS_FULL);
  ck_assert_int_eq(speed, INIT_SPEED - SPEED_CHANGE);
  ck_assert(new_record);
}
END_TEST

/* collapse(...) --> four rows, victory, ST_START */
START_TEST(tetris_fsm_test_34) {
  int **field, **next;

  int state = ST_STOP;
  int p_0 = BLOCK;
  int p_1 = BLOCK;
  int next_p_0_0 = GROUND;
  int next_p_0_1 = GROUND;
  int next_p_0_2 = GROUND;
  int next_p_0_3 = GROUND;
  int next_p_1_0 = GROUND;
  int next_p_1_1 = GROUND;
  int next_p_1_2 = GROUND;
  int next_p_1_3 = GROUND;
  int level = -1;
  int speed = -1;
  bool pause = false;
  bool new_record = true;

  int res_code = init_matrices(&field, &next);

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    game->signal = SIG_NOSIG;
    game->state = ST_COLLAPSE;
    game->level = 9;
    game->speed = INIT_SPEED - (SPEED_CHANGE * 8);

    game->field[15][0] = GROUND;
    game->field[16][0] = GROUND_FULL_ROW;
    game->field[17][0] = GROUND_FULL_ROW;
    game->field[18][0] = GROUND_FULL_ROW;
    game->field[19][0] = GROUND_FULL_ROW;

    GameInfo_t game_info = updateCurrentState();

    state = game->state;
    p_0 = game_info.field[15][0];
    p_1 = game_info.field[19][0];
    next_p_0_0 = game_info.next[0][0];
    next_p_0_1 = game_info.next[0][1];
    next_p_0_2 = game_info.next[0][2];
    next_p_0_3 = game_info.next[0][3];
    next_p_1_0 = game_info.next[1][0];
    next_p_1_1 = game_info.next[1][1];
    next_p_1_2 = game_info.next[1][2];
    next_p_1_3 = game_info.next[1][3];
    level = game_info.level;
    speed = game_info.speed;
    pause = game_info.pause;
    new_record = game->new_record;

    delete_matrices(&field, &next);
  }

  ck_assert_int_eq(res_code, SUCCESS);
  ck_assert_int_eq(state, ST_START);
  ck_assert_int_eq(p_0, VOID_GREEN);
  ck_assert_int_eq(p_1, GROUND_GREEN);
  ck_assert_int_eq(next_p_0_0, VOID);
  ck_assert_int_eq(next_p_0_1, VOID);
  ck_assert_int_eq(next_p_0_2, VOID);
  ck_assert_int_eq(next_p_0_3, VOID);
  ck_assert_int_eq(next_p_1_0, VOID);
  ck_assert_int_eq(next_p_1_1, VOID);
  ck_assert_int_eq(next_p_1_2, VOID);
  ck_assert_int_eq(next_p_1_3, VOID);
  ck_assert_int_eq(level, 9);
  ck_assert_int_eq(speed, INIT_SPEED - (SPEED_CHANGE * 8));
  ck_assert(pause);
  ck_assert(!new_record);
}
END_TEST

Suite *tetris_fsm_suite() {
  Suite *s = suite_create("tetris_fsm");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, tetris_fsm_test_1);
  tcase_add_test(tc_core, tetris_fsm_test_2);
  tcase_add_test(tc_core, tetris_fsm_test_3);
  tcase_add_test(tc_core, tetris_fsm_test_4);
  tcase_add_test(tc_core, tetris_fsm_test_5);
  tcase_add_test(tc_core, tetris_fsm_test_6);
  tcase_add_test(tc_core, tetris_fsm_test_7);
  tcase_add_test(tc_core, tetris_fsm_test_8);
  tcase_add_test(tc_core, tetris_fsm_test_9);
  tcase_add_test(tc_core, tetris_fsm_test_10);
  tcase_add_test(tc_core, tetris_fsm_test_11);
  tcase_add_test(tc_core, tetris_fsm_test_12);
  tcase_add_test(tc_core, tetris_fsm_test_13);
  tcase_add_test(tc_core, tetris_fsm_test_14);
  tcase_add_test(tc_core, tetris_fsm_test_15);
  tcase_add_test(tc_core, tetris_fsm_test_16);
  tcase_add_test(tc_core, tetris_fsm_test_17);
  tcase_add_test(tc_core, tetris_fsm_test_18);
  tcase_add_test(tc_core, tetris_fsm_test_19);
  tcase_add_test(tc_core, tetris_fsm_test_20);
  tcase_add_test(tc_core, tetris_fsm_test_21);
  tcase_add_test(tc_core, tetris_fsm_test_22);
  tcase_add_test(tc_core, tetris_fsm_test_23);
  tcase_add_test(tc_core, tetris_fsm_test_24);
  tcase_add_test(tc_core, tetris_fsm_test_25);
  tcase_add_test(tc_core, tetris_fsm_test_26);
  tcase_add_test(tc_core, tetris_fsm_test_27);
  tcase_add_test(tc_core, tetris_fsm_test_28);
  tcase_add_test(tc_core, tetris_fsm_test_29);
  tcase_add_test(tc_core, tetris_fsm_test_30);
  tcase_add_test(tc_core, tetris_fsm_test_31);
  tcase_add_test(tc_core, tetris_fsm_test_32);
  tcase_add_test(tc_core, tetris_fsm_test_33);
  tcase_add_test(tc_core, tetris_fsm_test_34);
  suite_add_tcase(s, tc_core);
  return s;
}

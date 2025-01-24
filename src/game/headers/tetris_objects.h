#ifndef TETRIS_OBJECTS
#define TETRIS_OBJECTS

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  UserAction_t action;
  bool hold;
} input_t;

typedef enum {
  SIG_NOSIG,
  SIG_SWITCH,
  SIG_TERM,
  SIG_ACT,
  SIG_LEFT,
  SIG_RIGHT,
  SIG_DOWN,
  SIG_SHIFT
} signal_t;

typedef enum {
  ST_START,
  ST_SPAWN,
  ST_MOVE,
  ST_ATTACH,
  ST_CHECK,
  ST_COLLAPSE,
  ST_SUSPEND,
  ST_STOP
} state_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct {
  int type;
  int y;
  int x;
} piece_t;

typedef struct {
  int y_0, x_0;
  int y_1, x_1;
  int y_2, x_2;
  int y_3, x_3;
} piece_pos_t;

typedef struct {
  signal_t signal;
  state_t state;
  int **field;
  int **next;
  piece_t piece;
  piece_pos_t piece_pos;
  piece_t next_piece;
  int level;
  int speed;
  int score;
  int fresh_score;
  int high_score;
  bool new_record;
  bool pause;
  int state_prev;
} game_t;

#endif

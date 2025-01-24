#ifndef INTERFACE_OBJECTS
#define INTERFACE_OBJECTS

#include "../../game/headers/tetris_objects.h"

typedef struct {
  int start_y;
  int start_x;
} start_pos_t;

typedef struct {
  bool f_debug;
  bool f_silent;
  bool f_stop;
  bool f_resumed;
  bool f_mv_key;
} interf_flags_t;

typedef struct {
  WINDOW *w_debug;
  WINDOW *w_board;
  WINDOW *w_field;
  WINDOW *w_next;
  WINDOW *w_record;
  WINDOW *w_score;
  WINDOW *w_level;
  WINDOW *w_message;
} subwins_t;

typedef struct {
  int iter_count;
  int ch_count;
  int cur_ch;
  interf_flags_t flags;
  subwins_t subwins;
} interf_t;

#endif

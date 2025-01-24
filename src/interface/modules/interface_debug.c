#include "../headers/interface_headers.h"

char *show_ch(int ch) {
  char *res;

  switch (ch) {
    case ESCAPE:
      res = "ESCAPE";
      break;
    case ENTER:
      res = "ENTER";
      break;
    case KEY_ENTER:
      res = "KEY_ENTER";
      break;
    case KEY_UP:
      res = "KEY_UP";
      break;
    case KEY_LEFT:
      res = "KEY_LEFT";
      break;
    case KEY_RIGHT:
      res = "KEY_RIGHT";
      break;
    case KEY_DOWN:
      res = "KEY_DOWN";
      break;
    case KEY_RESIZE:
      res = "KEY_RESIZE";
      break;
    case ERR:
      res = "ERR";
      break;
    case 'p':
      res = "p";
      break;
    case 'd':
      res = "d";
      break;
    case 's':
      res = "s";
      break;
    case 0:
      res = "0";
      break;
    default:
      res = "--";
  }

  return res;
}

char *show_signal(signal_t signal) {
  char *res;

  switch (signal) {
    case SIG_NOSIG:
      res = "SIG_NOSIG";
      break;
    case SIG_TERM:
      res = "SIG_TERM";
      break;
    case SIG_ACT:
      res = "SIG_ACT";
      break;
    case SIG_LEFT:
      res = "SIG_LEFT";
      break;
    case SIG_RIGHT:
      res = "SIG_RIGHT";
      break;
    case SIG_DOWN:
      res = "SIG_DOWN";
      break;
    case SIG_SHIFT:
      res = "SIG_SHIFT";
      break;
    default:
      res = "--";
  }

  return res;
}

char *show_state(state_t state) {
  char *res;

  switch (state) {
    case ST_START:
      res = "ST_START";
      break;
    case ST_SPAWN:
      res = "ST_SPAWN";
      break;
    case ST_MOVE:
      res = "ST_MOVE";
      break;
    case ST_ATTACH:
      res = "ST_ATTACH";
      break;
    case ST_CHECK:
      res = "ST_CHECK";
      break;
    case ST_COLLAPSE:
      res = "ST_COLLAPSE";
      break;
    case ST_SUSPEND:
      res = "ST_SUSPEND";
      break;
    case ST_STOP:
      res = "ST_STOP";
      break;
    default:
      res = "--";
  }

  return res;
}

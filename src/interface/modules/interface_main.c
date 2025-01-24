#include "../headers/interface_headers.h"

int main() {
  initscr();
  curs_set(0);
  noecho();
  keypad(stdscr, TRUE);

  int **field, **next;

  int res_code = has_colors() ? SUCCESS : ERROR;

  if (!res_code) {
    init_colors();
    res_code = init_matrices(&field, &next); /* SUCCESS or MALLOC_ERROR */
  }

  if (!res_code) {
    init_params(field, next);
    game_t *game = get_params();
    GameInfo_t game_info = get_info(game);
    interf_t interf = init_interf();
    render(game_info, game, &interf);

    while (!interf.flags.f_stop) {
      interf.iter_count++;

      reset_timeout(&interf, game);

      int ch = getch();
      input_t input = preprocess_ch(ch, &interf, game);

      userInput(input.action, input.hold);
      game_info = updateCurrentState();

      render(game_info, game, &interf);
      use_effects(&interf, game);

      if (game->state == ST_STOP) {
        interf.flags.f_stop = true;
      }
    }

    delete_matrices(&field, &next);
  }

  endwin();

  return res_code;
}

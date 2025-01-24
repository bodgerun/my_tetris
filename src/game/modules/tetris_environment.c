#include "../headers/tetris_headers.h"

/* library functions */

int init_matrices(int ***field, int ***next) {
  int res_code = allocate_memory(FIELD_ROWS, FIELD_COLS, field);

  if (!res_code) {
    res_code = allocate_memory(NEXT_ROWS, NEXT_COLS, next);

    if (res_code) {
      deallocate_memory(FIELD_ROWS, *field);
    }
  }

  return res_code;
}

void delete_matrices(int ***field, int ***next) {
  deallocate_memory(FIELD_ROWS, *field);
  deallocate_memory(NEXT_ROWS, *next);
  *field = NULL;
  *next = NULL;
}

int allocate_memory(int rows, int cols, int ***matrix) {
  int **res = (int **)malloc(rows * sizeof(int *));
  int res_code = res ? SUCCESS : MALLOC_ERROR;

  for (int i = 0; !res_code && i < rows; i++) {
    res[i] = (int *)calloc(cols, sizeof(int));
    res_code = res[i] ? SUCCESS : MALLOC_ERROR;

    if (res_code) {
      for (int j = 0; j < i; j++) {
        free(res[j]);
      }
      free(res);
    }
  }

  if (!res_code) {
    *matrix = res;
  }

  return res_code;
}

void deallocate_memory(int rows, int **matrix) {
  for (int j = 0; j < rows; j++) {
    free(matrix[j]);
  }
  free(matrix);
}

void init_params(int **field, int **next) {
  game_t *game = get_params();

  game->signal = SIG_NOSIG;
  game->state = ST_START;
  game->field = field;
  game->next = next;
  game->piece.type = 0;
  game->piece.y = 0;
  game->piece.x = 0;
  game->piece_pos.y_0 = 0;
  game->piece_pos.x_0 = 0;
  game->piece_pos.y_1 = 0;
  game->piece_pos.x_1 = 0;
  game->piece_pos.y_2 = 0;
  game->piece_pos.x_2 = 0;
  game->piece_pos.y_3 = 0;
  game->piece_pos.x_3 = 0;
  game->next_piece.type = 0;
  game->next_piece.y = 0;
  game->next_piece.x = 0;
  game->level = 1;
  game->speed = INIT_SPEED;
  game->score = 0;
  game->fresh_score = 0;
  game->high_score = read_record();
  game->new_record = false;
  game->pause = true;
  game->state_prev = -1;
}

int read_record() {
  int record = 0;

  FILE *f = fopen("record.txt", "r");

  if (f) {
    fscanf(f, "%d", &record);
    fclose(f);
  }

  return record;
}

void write_record(int record) {
  FILE *f = fopen("record.txt", "w");

  if (f) {
    fprintf(f, "%d", record);
    fclose(f);
  }
}

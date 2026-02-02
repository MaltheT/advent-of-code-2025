#include <stdio.h>
#include <string.h>

#define MAX_ROW_SIZE 512
#define MAX_COL_SIZE 512
#define START 'S'
#define EMPTY '.'
#define SPLITTER '^'
#define BEAM '|'

void load_teleporter_data(char *path_to_txt,
                          char inputdata[MAX_ROW_SIZE][MAX_COL_SIZE]);

int create_beams(char data[MAX_ROW_SIZE][MAX_COL_SIZE]);

int count_beams(char data[MAX_ROW_SIZE][MAX_COL_SIZE]);

//=== IMPL ===

void load_teleporter_data(char *path_to_txt,
                          char inputdata[MAX_ROW_SIZE][MAX_COL_SIZE]) {
  FILE *fptr;
  fptr = fopen(path_to_txt, "r");
  if (!fptr)
    return;

  char buff[MAX_ROW_SIZE];

  int row_i = 0;
  while (fgets(buff, MAX_ROW_SIZE, fptr)) {
    char *token = strtok(buff, "\n");
    int col_i = 0;
    for (;;) {
      if (token[col_i] == '\0') {
        inputdata[row_i][col_i] = token[col_i];
        break;
      }
      if (token[col_i] == ' ') {
        col_i++;
        continue;
      }
      inputdata[row_i][col_i] = token[col_i];
      col_i++;
    }
    row_i++;
  }
  fclose(fptr);
}

int create_beams(char data[MAX_ROW_SIZE][MAX_COL_SIZE]) {
  int row_i = 0, col_i = 0, split_ctr = 0;

  for (;;) {
    while (data[row_i][col_i] != '\0') {
      if (data[row_i][col_i] == START || data[row_i][col_i] == BEAM) {
        if (data[row_i + 1][col_i] == EMPTY) {
          data[row_i + 1][col_i] = BEAM;
        } else if (data[row_i + 1][col_i] == SPLITTER) {
          split_ctr++;

          if (data[row_i + 1][col_i - 1] == EMPTY)
            data[row_i + 1][col_i - 1] = BEAM;

          if (data[row_i + 1][col_i + 1] == EMPTY)
            data[row_i + 1][col_i + 1] = BEAM;
        }
      }
      col_i++;
    }
    col_i = 0;
    row_i++;
    if (data[row_i][col_i] == '\0')
      return split_ctr;
  }
}

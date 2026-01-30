#include <stdio.h>
#include <string.h>

#define MAX_ROW_SIZE 512
#define MAX_COL_SIZE 512
#define START 'S'
#define EMPTY '.'
#define SPLITTER '^'
#define BEAM '|'

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

void create_beams(char data[MAX_ROW_SIZE][MAX_COL_SIZE]) {
  int row_i = 0, col_i = 0;

  for (;;) {
    while (data[row_i][col_i] != '\0') {
      if (data[row_i][col_i] == START || data[row_i][col_i] == BEAM) {
        if (data[row_i + 1][col_i] == EMPTY)
          data[row_i + 1][col_i] = BEAM;
      }
      col_i++;
    }
    row_i++;
  }
}

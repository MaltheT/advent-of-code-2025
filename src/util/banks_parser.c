#include "util/banks_parser.h"
#include <stdio.h>
#include <string.h>

Matrix ReadInputBanks(char *path_to_txt) {

  FILE *fptr;
  fptr = fopen(path_to_txt, "r");
  char buff[256];
  int size = 0;
  size_t length = 0;

  while (fgets(buff, 256, fptr)) {
    size++;
    char *token = strtok(buff, "\n");
    length = strlen(token);
  };

  Matrix banks_matrix = create_matrix(size, length);

  int row_idx = 0;
  fseek(fptr, 0, SEEK_SET);
  while (fgets(buff, 256, fptr)) {
    char *token = strtok(buff, "\n");
    for (size_t col_idx = 0; col_idx < length; col_idx++) {
      int value = token[col_idx] - '0';
      if (value <= 9 && value >= 0) {
        set_matrix_element(&banks_matrix, row_idx, col_idx, value);
      } else {
        printf("Character could not be converted to single digit int\n");
      }
    }
    row_idx++;
  };
  fclose(fptr);

  return banks_matrix;
}

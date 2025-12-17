#include "util/matrix.h"
#include <stdio.h>
#include <string.h>

Matrix read_input_rolls_of_paper(char *path_to_txt) {

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

  Matrix rolls_of_paper_matrix = create_matrix(size, length, sizeof(char));

  int row_idx = 0;
  fseek(fptr, 0, SEEK_SET);
  while (fgets(buff, 256, fptr)) {
    char *token = strtok(buff, "\n");
    for (size_t col_idx = 0; col_idx < length; col_idx++) {
      char value = token[col_idx];
      set_matrix_element(&rolls_of_paper_matrix, row_idx, col_idx, &value);
    }
    row_idx++;
  };
  fclose(fptr);

  return rolls_of_paper_matrix;
}

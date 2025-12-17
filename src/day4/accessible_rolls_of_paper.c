#include "util/matrix.h"
#include <stddef.h>

#define WINDOW_SIZE 8

int accessible_rolls_of_paper(Matrix *rolls_of_paper) {
  char window[WINDOW_SIZE];
  int result = 0;
  for (size_t i = 0; i < rolls_of_paper->M; i++) {
    for (size_t j = 0; j < rolls_of_paper->N - WINDOW_SIZE; j++) {
      for (size_t k = 0; k < WINDOW_SIZE; k++) {
        window[k] = *(char *)get_matrix_element(rolls_of_paper, i, j);
      }
    }
  }
  return result;
}

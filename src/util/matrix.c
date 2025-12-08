#include "util/matrix.h"
#include <stdlib.h>

Matrix create_matrix(unsigned M, unsigned N) {
  Matrix matrix;
  matrix.M = M;
  matrix.N = N;
  matrix.data = (int *)calloc(M * N, sizeof(int));
  return matrix;
}

int *get_matrix_element(Matrix *matrix, unsigned m, unsigned n) {
  return matrix->data + m * matrix->N + n;
}

void set_matrix_element(Matrix *matrix, unsigned m, unsigned n, int value) {
  *get_matrix_element(matrix, m, n) = value;
}

void delete_matrix(Matrix *matrix) { free(matrix->data); }

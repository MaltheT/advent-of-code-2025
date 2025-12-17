#include "util/matrix.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Matrix create_matrix(unsigned M, unsigned N, size_t element_size) {
  Matrix matrix;
  matrix.M = M;
  matrix.N = N;
  matrix.element_size = element_size;
  matrix.data = calloc(M * N, element_size);
  return matrix;
}

void *get_matrix_element(Matrix *matrix, unsigned m, unsigned n) {
  if (m >= matrix->M || n >= matrix->N) {
    return NULL;
  }
  // Calculate offset: row * num_columns + column
  size_t index = m * matrix->N + n;

  // Cast to char* for byte arithmetic, then offset by element_size
  return (char *)matrix->data + (index * matrix->element_size);
}

void set_matrix_element(Matrix *matrix, unsigned m, unsigned n,
                        const void *value) {
  void *element = get_matrix_element(matrix, m, n);
  if (element != NULL) {
    memcpy(element, value, matrix->element_size);
  }
}

void delete_matrix(Matrix *matrix) { free(matrix->data); }

#pragma once
// Source - https://stackoverflow.com/a
// Posted by Tarek Dakhran
// Retrieved 2025-12-05, License - CC BY-SA 4.0

#include <stdlib.h>

typedef struct {
  unsigned M;
  unsigned N;
  size_t element_size;
  void *data;
} Matrix;

Matrix create_matrix(unsigned M, unsigned N, size_t element_size);

void *get_matrix_element(Matrix *matrix, unsigned m, unsigned n);

void set_matrix_element(Matrix *matrix, unsigned m, unsigned n,
                        const void *value);

void delete_matrix(Matrix *matrix);

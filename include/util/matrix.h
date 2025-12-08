#pragma once
// Source - https://stackoverflow.com/a
// Posted by Tarek Dakhran
// Retrieved 2025-12-05, License - CC BY-SA 4.0

typedef struct {
  unsigned M;
  unsigned N;
  int *data;
} Matrix;

Matrix create_matrix(unsigned M, unsigned N);

int *get_matrix_element(Matrix *matrix, unsigned m, unsigned n);

void set_matrix_element(Matrix *matrix, unsigned m, unsigned n, int value);

void delete_matrix(Matrix *matrix);


#ifndef CEPH_MATH_PARSER_H
#define CEPH_MATH_PARSER_H

#include "util/areana.h"

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { CEPH_OP_ADD, CEPH_OP_MUL } ceph_operation;

typedef struct {
  uint64_t *values;
  size_t value_count;
  ceph_operation op;
} ceph_problem;

typedef struct {
  ceph_problem *problems;
  size_t problem_count;
} ceph_worksheet;

/*
    Parses the cephalopod math worksheet.

    Layout assumptions:
    - Problems are vertical columns
    - Columns are separated by one or more full-space columns
    - Last non-empty row contains operators

    Returns 1 on success, 0 on failure.
*/
static int parse_ceph_math_worksheet(Arena *arena, const char *path,
                                     ceph_worksheet *out) {
  FILE *f = fopen(path, "r");
  if (!f)
    return 0;

  char lines[512][1024];
  size_t line_count = 0;

  while (line_count < 512 &&
         fgets(lines[line_count], sizeof(lines[line_count]), f)) {
    size_t len = strlen(lines[line_count]);
    if (len && lines[line_count][len - 1] == '\n') {
      lines[line_count][len - 1] = '\0';
    }
    line_count++;
  }
  fclose(f);

  if (line_count < 2)
    return 0;

  const char *op_line = lines[line_count - 1];
  size_t width = strlen(op_line);

  out->problems = arena_alloc(arena, sizeof(ceph_problem) * 128);
  out->problem_count = 0;

  for (size_t col = 0; col < width;) {
    if (op_line[col] == ' ') {
      col++;
      continue;
    }

    ceph_problem *p = &out->problems[out->problem_count++];
    p->values = arena_alloc(arena, sizeof(uint64_t) * 64);
    p->value_count = 0;

    if (op_line[col] == '+')
      p->op = CEPH_OP_ADD;
    else if (op_line[col] == '*')
      p->op = CEPH_OP_MUL;
    else
      return 0;

    for (size_t row = 0; row + 1 < line_count; row++) {
      if (col >= strlen(lines[row]))
        continue;
      if (!isdigit(lines[row][col]))
        continue;

      char buf[32];
      size_t k = 0;
      size_t c = col;

      while (c < strlen(lines[row]) && isdigit(lines[row][c])) {
        buf[k++] = lines[row][c++];
      }
      buf[k] = '\0';

      uint64_t v = strtoull(buf, NULL, 10);
      p->values[p->value_count++] = v;
    }

    col++;
  }

  return 1;
}

#endif /* CEPH_MATH_PARSER_H */

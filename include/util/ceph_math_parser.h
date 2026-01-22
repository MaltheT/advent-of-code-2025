
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
    - Problems are vertical columns of numbers
    - Operators are positioned between columns on the last line
    - Multiple spaces separate columns, single spaces may be within numbers

    Returns 1 on success, 0 on failure.
*/
static int parse_ceph_math_worksheet(Arena *arena, const char *path,
                                     ceph_worksheet *out) {
  FILE *f = fopen(path, "r");
  if (!f)
    return 0;

  char lines[512][4096];
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

  // Find the operator line (last non-empty line)
  int op_line_index = -1;
  for (int i = line_count - 1; i >= 0; i--) {
    bool has_content = false;
    for (size_t j = 0; j < strlen(lines[i]); j++) {
      if (lines[i][j] != ' ') {
        has_content = true;
        break;
      }
    }
    if (has_content) {
      op_line_index = i;
      break;
    }
  }
  
  if (op_line_index == -1)
    return 0;

  const char *op_line = lines[op_line_index];
  size_t width = strlen(op_line);

  // Pre-allocate space for problems
  // First pass: count operators to know how many problems we need
  size_t operator_count = 0;
  for (size_t col = 0; col < width; col++) {
    if (op_line[col] == '+' || op_line[col] == '*') {
      operator_count++;
    }
  }

  // Allocate space for all problems
  out->problems = arena_alloc(arena, sizeof(ceph_problem) * operator_count);
  out->problem_count = 0;

  // Second pass: parse each problem
  for (size_t col = 0; col < width;) {
    // Skip spaces
    while (col < width && op_line[col] == ' ') {
      col++;
    }
    if (col >= width) break;

    // Find the operator at this position
    char op_char = op_line[col];
    
    if (op_char != '+' && op_char != '*') {
      col++;
      continue;
    }

    ceph_problem *p = &out->problems[out->problem_count++];
    p->values = arena_alloc(arena, sizeof(uint64_t) * 64);
    p->value_count = 0;

    if (op_char == '+')
      p->op = CEPH_OP_ADD;
    else
      p->op = CEPH_OP_MUL;

    // Read numbers vertically from this column position
    // The column starts at the operator position
    for (int row = 0; row < op_line_index; row++) {
      const char *line = lines[row];
      
      // Skip spaces at the beginning of this column position
      size_t pos = col;
      while (pos < strlen(line) && line[pos] == ' ') {
        pos++;
      }
      
      // If we found digits at this position, extract the number
      if (pos < strlen(line) && isdigit(line[pos])) {
        char buf[32];
        size_t k = 0;
        
        // Extract the full number
        while (pos < strlen(line) && isdigit(line[pos]) && k < sizeof(buf) - 1) {
          buf[k++] = line[pos++];
        }
        buf[k] = '\0';

        if (k > 0) {
          uint64_t v = strtoull(buf, NULL, 10);
          p->values[p->value_count++] = v;
        }
      }
    }

    col++;
  }

  return 1;
}

#endif /* CEPH_MATH_PARSER_H */

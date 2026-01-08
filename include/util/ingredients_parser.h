#ifndef INGREDIENTS_PARSER_H
#define INGREDIENTS_PARSER_H

#include "util/areana.h"
#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint64_t start;
  uint64_t end;

} ingredient_id_range;

int read_input_ingredient_data(Arena *arena, char *path_to_txt,
                               ingredient_id_range **ranges,
                               size_t *range_count, uint64_t **values,
                               size_t *value_count);

#endif // INGREDIENTS_PARSER_H

#if defined(INGREDIENTS_PARSER_IMPLEMENTATION)

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 256

int read_input_ingredient_data(Arena *arena, char *path_to_txt,
                               ingredient_id_range **ranges,
                               size_t *range_count, uint64_t **values,
                               size_t *value_count) {

  FILE *fptr = fopen(path_to_txt, "r");
  if (!fptr)
    return 0;

  char buff[BUFF_SIZE];
  bool reading_ranges = true;

  *range_count = 0;
  *value_count = 0;

  size_t max_ranges = 1024;
  size_t max_values = 1024;

  *ranges = arena_alloc(arena, max_ranges * sizeof(**ranges));
  *values = arena_alloc(arena, max_values * sizeof(**values));

  while (fgets(buff, sizeof(buff), fptr)) {

    if (buff[0] == '\n') {
      reading_ranges = false;
      continue;
    }

    if (reading_ranges) {
      uint64_t start, end;
      if (sscanf(buff, "%" SCNu64 "-%" SCNu64, &start, &end) == 2) {
        (*ranges)[*range_count].start = start;
        (*ranges)[*range_count].end = end;
        (*range_count)++;
      }
    } else {
      uint64_t value;
      if (sscanf(buff, "%" SCNu64, &value) == 1) {
        (*values)[*value_count] = value;
        (*value_count)++;
      }
    }
  }

  fclose(fptr);
  return 1;
}

#endif // INGREDIENTS_PARSER_IMPLEMENTATION

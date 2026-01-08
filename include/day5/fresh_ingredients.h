
#ifndef FRESH_INGREDIENTS_H
#define FRESH_INGREDIENTS_H

#include "util/ingredients_parser.h"
#include <stddef.h>
#include <stdint.h>

uint64_t count_num_fresh_ingredients(ingredient_id_range *ranges,
                                     size_t ranges_count, uint64_t *values,
                                     size_t values_count);
uint64_t count_num_fresh_ingredient_ids(ingredient_id_range *ranges,
                                        size_t ranges_count);
#endif // FRESH_INGREDIENTS_H

#if defined(FRESH_INGREDIENTS_IMPLEMENTATION)

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t count_num_fresh_ingredients(ingredient_id_range *ranges,
                                     size_t ranges_count, uint64_t *values,
                                     size_t values_count) {

  uint64_t fresh_ctr = 0;
  for (size_t i = 0; i < values_count; i++) {
    for (size_t j = 0; j < ranges_count; j++) {
      if (values[i] >= ranges[j].start && values[i] <= ranges[j].end) {
        fresh_ctr++;
        break;
      }
    }
  }
  return fresh_ctr;
}
uint64_t count_num_fresh_ingredient_ids(ingredient_id_range *ranges,
                                        size_t ranges_count) {
  return 0;
}
// 916 too high

#endif // INGREDIENTS_PARSER_IMPLEMENTATION

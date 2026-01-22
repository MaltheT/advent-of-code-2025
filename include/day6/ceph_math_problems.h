

#ifndef CEPH_MATH_PROBLEMS_H
#define CEPH_MATH_PROBLEMS_H

#include "util/ceph_math_parser.h"
#include <stddef.h>
#include <stdint.h>

uint64_t calcuate_grand_total(ceph_worksheet worksheet);

#endif // CEPH_MATH_PROBLEMS_H

#if defined(CEPH_MATH_PROBLEMS_IMPLEMENTATION)

uint64_t calcuate_grand_total(ceph_worksheet worksheet) {
  uint64_t result = 0;
  for (size_t i = 0; i < worksheet.problem_count; i++) {
    uint64_t value = 0;
    if (worksheet.problems[i].op == CEPH_OP_MUL) {
      value = 1; // Initialize to 1 for multiplication!
      for (size_t j = 0; j < worksheet.problems[i].value_count; j++)
        value *= worksheet.problems[i].values[j];
    } else if (worksheet.problems[i].op == CEPH_OP_ADD) {
      for (size_t j = 0; j < worksheet.problems[i].value_count; j++)
        value += worksheet.problems[i].values[j];
    }
    result += value;
  }
  return result;
}

#endif // CEPH_MATH_PROBLEMS_IMPLEMENTATION

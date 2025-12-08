#include "util/matrix.h"

typedef struct Battery {
  int joltage;
  unsigned idx;
} Battery;

int max_joltage_part1(Matrix *banks);
int max_joltage_part2(Matrix *banks);
int activate_batteries(Battery batt1, Battery batt2);
int activate_batteries_array(Battery *batts);
unsigned concatenate(unsigned x, unsigned y);

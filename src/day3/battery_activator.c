#include "day3/battery_activator.h"

int max_joltage_part1(Matrix *banks) {
  int sum = 0;
  Battery batt1 = {.joltage = 0, .idx = 0};
  Battery batt2 = {.joltage = 0, .idx = 0};

  for (unsigned int i = 0; i < banks->M; i++) {
    for (unsigned int j = 0; j < banks->N; j++) {
      int value = *(int *)get_matrix_element(banks, i, j);
      Battery batt_tmp = {.joltage = value, .idx = j};
      int curr = activate_batteries(batt1, batt2);
      int res1 = activate_batteries(batt1, batt_tmp);
      int res2 = activate_batteries(batt2, batt_tmp);

      if (curr > res1 && curr > res2) {
        continue;
      }
      if (res1 > res2) {
        batt2 = batt_tmp;
      } else {
        batt1 = batt_tmp;
      }
    }
    sum += activate_batteries(batt1, batt2);
    batt1.joltage = 0;
    batt1.idx = 0;
    batt2.joltage = 0;
    batt2.idx = 0;
  }

  return sum;
}
int activate_batteries(Battery batt1, Battery batt2) {
  if (batt1.idx < batt2.idx) {
    return concatenate(batt1.joltage, batt2.joltage);
  }
  return concatenate(batt2.joltage, batt1.joltage);
}

int activate_batteries_array(Battery *batts) {}

// Source - https://stackoverflow.com/a
// Posted by Mooing Duck, modified by community. See post 'Timeline' for change
// history Retrieved 2025-12-08, License - CC BY-SA 3.0

unsigned concatenate(unsigned x, unsigned y) {
  unsigned pow = 10;
  while (y >= pow)
    pow *= 10;
  return x * pow + y;
}

int MaxJoltagePart2(Matrix *banks) {
  int sum = 0;
  Battery batt1 = {.joltage = 0, .idx = 0};
  Battery batt2 = {.joltage = 0, .idx = 0};

  for (unsigned int i = 0; i < banks->M; i++) {
    for (unsigned int j = 0; j < banks->N; j++) {
      int value = *(int *)get_matrix_element(banks, i, j);
      Battery batt_tmp = {.joltage = value, .idx = j};
      int curr = activate_batteries(batt1, batt2);
      int res1 = activate_batteries(batt1, batt_tmp);
      int res2 = activate_batteries(batt2, batt_tmp);

      if (curr > res1 && curr > res2) {
        continue;
      }
      if (res1 > res2) {
        batt2 = batt_tmp;
      } else {
        batt1 = batt_tmp;
      }
    }
    sum += activate_batteries(batt1, batt2);
    batt1.joltage = 0;
    batt1.idx = 0;
    batt2.joltage = 0;
    batt2.idx = 0;
  }

  return sum;
}

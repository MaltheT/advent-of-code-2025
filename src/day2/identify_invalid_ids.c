#include "day2/identify_invalid_ids.h"

int IdentifyInvalidIds(InputIds *input_ids) {
  for (int i = 0; i < input_ids->lenght; i++) {
    char first_digit = input_ids->firstId[i][0];
    if (first_digit == '0') {
      continue;
    }
  }
  return 1;
}

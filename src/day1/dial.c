#include "day1/dial.h"
#include <stdio.h>

void RotateDial(struct Dial *dial, char direction, int distance) {
  distance = distance % 100;

  if (direction == 'L') {
    dial->arrow_position -= distance;
    if (dial->arrow_position < dial->min_position) {
      dial->arrow_position += dial->max_position + 1;
    }
  } else if (direction == 'R') {
    dial->arrow_position += distance;
    if (dial->arrow_position > dial->max_position) {
      dial->arrow_position -= dial->max_position + 1;
    }
  } else {
    printf("direction not specified correctly, use L or R\n");
  }
}

int CalculatePassword(struct Dial *dial, struct InputSequence *input_sequence) {
  int ctr = 0;
  for (int i = 0; i < input_sequence->size; i++) {
    RotateDial(dial, input_sequence->directions[i],
               input_sequence->distances[i]);
    if (dial->arrow_position == 0) {
      ctr++;
    }
  }
  return ctr;
}

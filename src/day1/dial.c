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

int CalculatePasswordPart2(struct Dial *dial,
                           struct InputSequence *input_sequence) {
  int ctr = 0;
  for (int i = 0; i < input_sequence->size; i++) {

    int arrow_position_before = dial->arrow_position;

    RotateDial(dial, input_sequence->directions[i],
               input_sequence->distances[i]);

    int arrow_position_after = dial->arrow_position;

    ctr += input_sequence->distances[i] / 100;
    if (input_sequence->directions[i] == 'L') {
      if (arrow_position_after > arrow_position_before) {
        ctr++;
      }
    }
    if (input_sequence->directions[i] == 'R') {
      if (arrow_position_after < arrow_position_before) {
        ctr++;
      }
    }
  }
  return ctr;
}

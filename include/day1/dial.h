#include "util/dial_sequence_parser.h"
typedef struct Dial {
  const int min_position;
  const int max_position;
  int arrow_position;
} Dial;

void RotateDial(struct Dial *dial, char direction, int distance);

int CalculatePassword(struct Dial *dial, struct InputSequence *input_sequence);

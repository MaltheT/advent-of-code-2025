#include "day1/dial.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  Dial dial = {.max_position = 99, .min_position = 0, .arrow_position = 50};
  InputSequence input_sequence =
      ReadInputSequence("../input/dial_sequence.txt");
  int password = CalculatePassword(&dial, &input_sequence);
  printf("password is: %d", password);
  return EXIT_SUCCESS;
}

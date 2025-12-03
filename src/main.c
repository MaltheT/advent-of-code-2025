#include "day1/dial.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  Dial dial = {.max_position = 99, .min_position = 0, .arrow_position = 50};
  InputSequence input_sequence = ReadInputSequence(
      "/home/mtb/Projects/advent-of-code-2025/input/dial_sequence.txt");
  // int password = CalculatePassword(&dial, &input_sequence);
  // printf("password is: %d\n", password);

  dial.arrow_position = 50;
  int password_part_2 = CalculatePasswordPart2(&dial, &input_sequence);

  printf("password part 2 is: %d\n", password_part_2);
  return EXIT_SUCCESS;
}

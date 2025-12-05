#include "day1/dial.h"
#include "day2/identify_invalid_ids.h"
#include <stdio.h>
#include <stdlib.h>

void Day1Part1(void) {

  Dial dial = {.max_position = 99, .min_position = 0, .arrow_position = 50};
  InputSequence input_sequence = ReadInputSequence(
      "/home/mtb/Projects/advent-of-code-2025/input/dial_sequence.txt");
  int password = CalculatePassword(&dial, &input_sequence);
  printf("Day1 part1 password is: %d\n", password);
  free(input_sequence.distances);
  free(input_sequence.directions);
}

void Day1Part2(void) {

  Dial dial = {.max_position = 99, .min_position = 0, .arrow_position = 50};
  InputSequence input_sequence = ReadInputSequence(
      "/home/mtb/Projects/advent-of-code-2025/input/dial_sequence.txt");
  int password = CalculatePasswordPart2(&dial, &input_sequence);
  printf("Day1 part2 password is: %d\n", password);
  free(input_sequence.distances);
  free(input_sequence.directions);
}

void Day2Part1(void) {
  InputIds input_ids = ReadInputIds(
      "/home/mtb/Projects/advent-of-code-2025/input/invalid_ids.txt");
  int sum = IdentifyInvalidIds(&input_ids);

  printf("%d\n", sum);
}

int main(int argc, char *argv[]) {
  Day1Part1();
  Day1Part2();
  Day2Part1();

  return EXIT_SUCCESS;
}

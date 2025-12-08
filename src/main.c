#include "day1/dial.h"
#include "day2/identify_invalid_ids.h"
#include "day3/battery_activator.h"
#include "util/banks_parser.h"
#include <stdio.h>
#include <stdlib.h>

void day1_part1(void) {

  Dial dial = {.max_position = 99, .min_position = 0, .arrow_position = 50};
  InputSequence input_sequence = ReadInputSequence(
      "/home/mtb/Projects/advent-of-code-2025/input/dial_sequence.txt");
  int password = CalculatePassword(&dial, &input_sequence);
  printf("d1p1 password is: %d\n", password);
  free(input_sequence.distances);
  free(input_sequence.directions);
}

void day1_part2(void) {

  Dial dial = {.max_position = 99, .min_position = 0, .arrow_position = 50};
  InputSequence input_sequence = ReadInputSequence(
      "/home/mtb/Projects/advent-of-code-2025/input/dial_sequence.txt");
  int password = CalculatePasswordPart2(&dial, &input_sequence);
  printf("d1p2 password is: %d\n", password);
  free(input_sequence.distances);
  free(input_sequence.directions);
}

void day2_part1(void) {
  InputIds input_ids = ReadInputIds(
      "/home/mtb/Projects/advent-of-code-2025/input/invalid_ids.txt");
  int sum = IdentifyInvalidIds(&input_ids);

  printf("d2p1 sum of invalid ids: %d\n", sum);
}

void day3_part1(void) {
  Matrix input_banks =
      ReadInputBanks("/home/mtb/Projects/advent-of-code-2025/input/banks.txt");

  int max_joltage = max_joltage_part1(&input_banks);

  printf("d3p1 max joltage from banks: %d\n", max_joltage);
}

int main(int argc, char *argv[]) {
  day1_part1();
  day1_part2();
  day2_part1();
  day3_part1();

  return EXIT_SUCCESS;
}

#include "day1/dial.h"
#include "day2/identify_invalid_ids.h"
#include "util/banks_parser.h"
#include <stdio.h>
#include <stdlib.h>

void Day1Part1(void) {

  Dial dial = {.max_position = 99, .min_position = 0, .arrow_position = 50};
  InputSequence input_sequence = ReadInputSequence(
      "/home/mtb/Projects/advent-of-code-2025/input/dial_sequence.txt");
  int password = CalculatePassword(&dial, &input_sequence);
  printf("d1p1 password is: %d\n", password);
  free(input_sequence.distances);
  free(input_sequence.directions);
}

void Day1Part2(void) {

  Dial dial = {.max_position = 99, .min_position = 0, .arrow_position = 50};
  InputSequence input_sequence = ReadInputSequence(
      "/home/mtb/Projects/advent-of-code-2025/input/dial_sequence.txt");
  int password = CalculatePasswordPart2(&dial, &input_sequence);
  printf("d1p2 password is: %d\n", password);
  free(input_sequence.distances);
  free(input_sequence.directions);
}

void Day2Part1(void) {
  InputIds input_ids = ReadInputIds(
      "/home/mtb/Projects/advent-of-code-2025/input/invalid_ids.txt");
  int sum = IdentifyInvalidIds(&input_ids);

  printf("d2p1 sum of invalid ids: %d\n", sum);
}

void Day3Part1(void) {
  Matrix input_banks =
      ReadInputBanks("/home/mtb/Projects/advent-of-code-2025/input/banks.txt");

  printf("d3p1 max joltage from banks: %d\n",
         *get_matrix_element(&input_banks, 0, 0));
}

int main(int argc, char *argv[]) {
  Day1Part1();
  Day1Part2();
  Day2Part1();
  Day3Part1();

  return EXIT_SUCCESS;
}

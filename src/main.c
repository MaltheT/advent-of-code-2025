#include "day6/ceph_math_problems.h"
#include "day7/teleporter.h"
#include <stdint.h>
#define ARENA_IMPLEMENTATION
#include "util/areana.h"
#undef ARENA_IMPLEMENTATION
#include "day1/dial.h"
#include "day2/identify_invalid_ids.h"
#include "day3/battery_activator.h"
#include "day4/accessible_rolls_of_paper.h"
#define FRESH_INGREDIENTS_IMPLEMENTATION
#include "day5/fresh_ingredients.h"
#define CEPH_MATH_PROBLEMS_IMPLEMENTATION
#include "day6/ceph_math_problems.h"
#undef FRESH_INGREDIENTS_IMPLEMENTATION
#include "util/banks_parser.h"
#define INGREDIENTS_PARSER_IMPLEMENTATION
#include "util/ceph_math_parser.h"
#include "util/ingredients_parser.h"
#include "util/matrix.h"
#include "util/rolls_of_paper_parser.h"
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef PROJECT_ROOT
#define PROJECT_ROOT ".."
#endif
#define INPUT_PATH(file) PROJECT_ROOT "/input/" file

void day1_part1(void) {

  Dial dial = {.max_position = 99, .min_position = 0, .arrow_position = 50};
  InputSequence input_sequence =
      ReadInputSequence(INPUT_PATH("dial_sequence.txt"));
  int password = CalculatePassword(&dial, &input_sequence);
  printf("d1p1 password is: %d\n", password);
  free(input_sequence.distances);
  free(input_sequence.directions);
}

void day1_part2(void) {

  Dial dial = {.max_position = 99, .min_position = 0, .arrow_position = 50};
  InputSequence input_sequence =
      ReadInputSequence(INPUT_PATH("dial_sequence.txt"));
  int password = CalculatePasswordPart2(&dial, &input_sequence);
  printf("d1p2 password is: %d\n", password);
  free(input_sequence.distances);
  free(input_sequence.directions);
}

void day2_part1(void) {
  InputIds input_ids = ReadInputIds(INPUT_PATH("invalid_ids.txt"));
  int sum = IdentifyInvalidIds(&input_ids);

  printf("d2p1 sum of invalid ids: %d\n", sum);
}

void day3_part1(void) {
  Matrix input_banks = ReadInputBanks(INPUT_PATH("banks.txt"));

  int max_joltage = max_joltage_part1(&input_banks);

  printf("d3p1 max joltage from banks: %d\n", max_joltage);
}

void day4_part1(void) {
  Matrix input_rolls_of_paper =
      read_input_rolls_of_paper(INPUT_PATH("rolls_of_paper.txt"));

  printf("d4p1 ....: %d\n", accessible_rolls_of_paper(&input_rolls_of_paper));
}

void day4_part2(void) {
  Matrix input_rolls_of_paper =
      read_input_rolls_of_paper(INPUT_PATH("rolls_of_paper.txt"));

  printf("d4p2 ....: %d\n", removeable_rolls_of_paper(&input_rolls_of_paper));
}

void day5_part1(void) {

  Arena areana = {0};

  ingredient_id_range *ingredient_id_ranges = NULL;
  uint64_t *ingredint_values = NULL;
  size_t ranges_count = 0, values_count = 0;

  read_input_ingredient_data(&areana, INPUT_PATH("ingredients.txt"),
                             &ingredient_id_ranges, &ranges_count,
                             &ingredint_values, &values_count);

  uint64_t fresh_count = count_num_fresh_ingredients(
      ingredient_id_ranges, ranges_count, ingredint_values, values_count);
  printf("d5p1 number of fresh ingredients ....: %llu\n", fresh_count);

  arena_free(&areana);
}
void day6_part1(void) {

  Arena areana = {0};
  ceph_worksheet ceph_worksheet = {0};

  parse_ceph_math_worksheet(&areana, INPUT_PATH("math_work_sheet.txt"),
                            &ceph_worksheet);

  uint64_t result = calcuate_grand_total(ceph_worksheet);

  printf("d6p1 result: %llu\n", result); // 2689251 too low

  arena_free(&areana);
}

void day7_part1(void) {
  char inputdata[MAX_ROW_SIZE][MAX_COL_SIZE];
  load_teleporter_data(INPUT_PATH("teleporter.txt"), inputdata);
  int result = create_beams(inputdata);

  printf("d7p1 result... %d \n", result); // 6189 too high
}

void day8_part1(void) {
  char inputdata[MAX_ROW_SIZE][MAX_COL_SIZE];
  load_teleporter_data(INPUT_PATH("teleporter.txt"), inputdata);
  int result = create_beams(inputdata);

  printf("d7p1 result... %d \n", result); // 6189 too high
}

int main(int argc, char *argv[]) {
  day1_part1();
  day1_part2();
  day2_part1();
  day3_part1();
  day4_part1();
  day4_part2();
  day5_part1();
  // day6_part1();
  day7_part1();
  day8_part1();

  return EXIT_SUCCESS;
}

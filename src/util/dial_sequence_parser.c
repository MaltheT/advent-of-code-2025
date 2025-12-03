#include "util/dial_sequence_parser.h"
#include <stdio.h>
#include <stdlib.h>

InputSequence ReadInputSequence(char *path_to_txt) {
  FILE *fptr;
  fptr = fopen(path_to_txt, "r");
  int size = 0;
  char buff[50];

  while (fgets(buff, 50, fptr)) {
    size++;
  };

  InputSequence input_sequence = {
      .size = size,
      .directions = (char *)malloc(sizeof(char) * size),
      .distances = (int *)malloc(sizeof(int) * size)};

  int i = 0;
  fseek(fptr, 0, SEEK_SET);
  while (fgets(buff, 50, fptr)) {
    input_sequence.directions[i] = buff[0];
    input_sequence.distances[i] = atoi(buff + 1);
    i++;
  };

  fclose(fptr);
  return input_sequence;
}

#include "util/dial_sequence_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int Concat(int a, int b) {

  char s1[20];
  char s2[20];

  // Convert both the integers to string
  sprintf(s1, "%d", a);
  sprintf(s2, "%d", b);

  // Concatenate both strings
  strcat(s1, s2);

  // Convert the concatenated string
  // to integer
  int c = atoi(s1);

  // return the formed integer
  return c;
}

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
    input_sequence.distances[i] =
        Concat(Concat(buff[1] - '0', buff[2] - '0'), buff[3] - '0');
    // printf("direction: %c, distance: %d, buff: %s",
    //        input_sequence.directions[i], input_sequence.distances[i], buff);
    i++;
  };

  fclose(fptr);
  return input_sequence;
}

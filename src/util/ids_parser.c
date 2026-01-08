#include "util/ids_parser.h"
#include "util/string.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

InputIds ReadInputIds(char *path_to_txt) {

  FILE *fptr;
  fptr = fopen(path_to_txt, "r");
  char buff[1024];

  fgets(buff, 1024, fptr);

  fclose(fptr);
  char **ids;
  ids = str_split(buff, ',');

  struct InputIds input_ids;
  input_ids.lenght = 0;
  for (int i = 0; *(ids + i); i++) {
    input_ids.lenght++;
  }
  input_ids.firstId = calloc(input_ids.lenght, sizeof(int *));
  input_ids.lastId = calloc(input_ids.lenght, sizeof(int *));

  for (int i = 0; *(ids + i); i++) {
    char **id_parts = str_split(*(ids + i), '-');
    input_ids.firstId[i] = *(id_parts + 0);
    input_ids.lastId[i] = *(id_parts + 1);
    free(*(ids + i));
    free(id_parts);
  }
  free(ids);

  return input_ids;
}

#include "util/ids_parser.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Source - https://stackoverflow.com/a
// Posted by hmjd, modified by community. See post 'Timeline' for change
// history Retrieved 2025-12-04, License - CC BY-SA 3.0

char **str_split(char *a_str, const char a_delim) {
  char **result = 0;
  size_t count = 0;
  char *tmp = a_str;
  char *last_comma = 0;
  char delim[2];
  delim[0] = a_delim;
  delim[1] = 0;

  /* Count how many elements will be extracted. */
  while (*tmp) {
    if (a_delim == *tmp) {
      count++;
      last_comma = tmp;
    }
    tmp++;
  }

  /* Add space for trailing token. */
  count += last_comma < (a_str + strlen(a_str) - 1);

  /* Add space for terminating null string so caller
     knows where the list of returned strings ends. */
  count++;

  result = malloc(sizeof(char *) * count);

  if (result) {
    size_t idx = 0;
    char *token = strtok(a_str, delim);

    while (token) {
      assert(idx < count);
      *(result + idx++) = strdup(token);
      token = strtok(0, delim);
    }
    assert(idx == count - 1);
    *(result + idx) = 0;
  }

  return result;
}

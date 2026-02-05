#ifndef JUNCTION_BOXES_H
#define JUNCTION_BOXES_H

#include <stdio.h>
#include <string.h>

typedef struct {
  int x, y, z;
} Pos;

#define POW(x) ((x) * (x))

#define EUCLIDEAN_DISTANCE_3D_SQUARED(pos1, pos2)                              \
  ((POW(pos1.x - pos2.x)) + (POW(pos1.y - pos2.y)) + (POW(pos1.z - pos2.z)))

#define MAX_INPUT_LEN 512

void load_junction_box_data(char *path_to_txt, Pos inputdata[MAX_INPUT_LEN],
                            int *input_len);

//=== IMPL ===

void load_junction_box_data(char *path_to_txt, Pos inputdata[MAX_INPUT_LEN],
                            int *input_len) {
  FILE *fptr;
  int max_line_len = 128;
  fptr = fopen(path_to_txt, "r");
  if (!fptr)
    return;

  char buff[max_line_len];
  int i = 0;
  while (fgets(buff, max_line_len, fptr)) {
    char *token = strtok(buff, ",");
    inputdata[i].x = token[0];
    inputdata[i].y = token[1];
    inputdata[i].z = token[2];
    i++;
  }
  *input_len = i + 1;
  fclose(fptr);
}
#endif // JUNCTION_BOXES_H

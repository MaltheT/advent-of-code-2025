#ifndef JUNCTION_BOXES_H
#define JUNCTION_BOXES_H

#include "util/areana.h"
#include "util/types.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POW(x) ((x) * (x))

#define EUCLIDEAN_DISTANCE_3D_SQUARED(pos1, pos2)                              \
  ((POW(pos1.x - pos2.x)) + (POW(pos1.y - pos2.y)) + (POW(pos1.z - pos2.z)))

#define MAX_INPUT_LEN 1024
#define MAX_ELEMS_IN_CIRCUIT 100
#define MAX_CIRCUITS 1000

typedef struct {
  i64 x, y, z;
  b32 is_connected;
  i32 circuit_id;
} JunctionBox;

int load_junction_box_data(char *path_to_txt,
                           JunctionBox inputdata[MAX_INPUT_LEN],
                           int *input_len);

b32 connect_junction_boxes(JunctionBox inputdata[MAX_INPUT_LEN], i32 input_len,
                           i32 *num_circuits, i32 *circuit_elems_counter);

i32 find_product_n_largest_circuits(i32 n, i32 num_circuits,
                                    i32 circuit_elems_counter[MAX_INPUT_LEN]);

//=== IMPL ===

b32 load_junction_box_data(char *path_to_txt,
                           JunctionBox inputdata[MAX_INPUT_LEN],
                           int *input_len) {
  FILE *fptr;
  i32 max_line_len = 128;
  fptr = fopen(path_to_txt, "r");
  if (!fptr)
    return 0;

  char buff[max_line_len];
  i32 i = 0;
  while (fgets(buff, max_line_len, fptr)) {
    sscanf(buff, "%lld,%lld,%lld", &inputdata[i].x, &inputdata[i].y,
           &inputdata[i].z);
    inputdata[i].is_connected = 0;
    inputdata[i].circuit_id = -1;
    i++;
  }
  *input_len = i;
  fclose(fptr);
  return 1;
}
b32 connect_junction_boxes(JunctionBox inputdata[MAX_INPUT_LEN], i32 input_len,
                           i32 *num_circuits, i32 *circuit_elems_counter) {

  for (i32 i = 0; i < MAX_INPUT_LEN; i++) {
    circuit_elems_counter[i] = 0;
  }

  i32 circuit_counter = 0;
  for (i32 i = 0; i < input_len; i++) {
    if (inputdata[i].is_connected)
      continue;

    i64 shortest_dist = INT64_MAX;
    i32 idx = -1;
    for (i32 j = 0; j < input_len; j++) {
      if (j == i)
        continue;
      i64 value = EUCLIDEAN_DISTANCE_3D_SQUARED(inputdata[i], inputdata[j]);
      if (value < shortest_dist) {
        shortest_dist = value;
        idx = j;
      }
    }

    if (idx == -1) {
      printf("Shortest distance could not be found for JunctionBox at index "
             "%d\n",
             i);
      return 0;
    }

    if (inputdata[idx].is_connected) {
      // add to circuit
      i32 circuit_id = inputdata[idx].circuit_id;
      inputdata[i].is_connected = 1;
      inputdata[i].circuit_id = circuit_id;
      circuit_elems_counter[circuit_id]++;
    } else {
      // create new circuit
      inputdata[idx].is_connected = 1;
      inputdata[idx].circuit_id = circuit_counter;
      inputdata[i].is_connected = 1;
      inputdata[i].circuit_id = circuit_counter;
      circuit_elems_counter[circuit_counter] += 2;
      circuit_counter++;
    }
    *num_circuits = circuit_counter;
  }
  return 1;
}

i32 find_product_n_largest_circuits(i32 n, i32 num_circuits,
                                    i32 circuit_elems_counter[MAX_INPUT_LEN]) {

  i32 result = 1;

  while (n) {
    if (num_circuits < n)
      break;

    i32 largest_circuit_size = 0;
    i32 idx;
    for (i32 i = 0; i < num_circuits; i++) {
      i32 value = circuit_elems_counter[i];
      if (largest_circuit_size < value) {
        largest_circuit_size = value;
        idx = i;
      }
    }
    if (largest_circuit_size != 0)
      result *= largest_circuit_size;

    largest_circuit_size = 0;
    circuit_elems_counter[idx] = 0;
    idx = 0;
    n--;
  }
  return result;
}
#endif // JUNCTION_BOXES_H

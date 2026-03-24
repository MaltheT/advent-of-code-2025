#pragma once

#include "../util/types.h"
#include <stdint.h>
#include <stdio.h>

#define MAX_INPUT_LEN 1024

typedef struct {
  u32 x, y;
} RedTile;

typedef struct {
  RedTile tiles[MAX_INPUT_LEN];
  u32 len;
} RedTileData;

//=== DECLARATION ===

b32 load_red_tiles_data(char *path_to_txt, RedTileData *red_tile_data);
u64 size_of_rectangle(RedTile red_tile_1, RedTile red_tile_2);
u64 size_of_biggest_rectangle(RedTileData red_tile_data);

//=== IMPLEMENTATION ===

b32 load_red_tiles_data(char *path_to_txt, RedTileData *red_tile_data) {
  FILE *fptr;
  u8 max_line_len = 128;
  fptr = fopen(path_to_txt, "r");

  if (fptr == NULL) {
    printf("Failed to open file at: %s", path_to_txt);
    return 1;
  }

  char buff[max_line_len];
  u32 i = 0;
  RedTile tile;
  while (fgets(buff, max_line_len, fptr)) {
    sscanf(buff, "%u,%u", &tile.x, &tile.y);
    red_tile_data->tiles[i] = tile;
    i++;
  }
  red_tile_data->len = i;
  fclose(fptr);
  return 0;
}

u64 size_of_rectangle(RedTile red_tile_1, RedTile red_tile_2) {
  u64 x_len = (red_tile_1.x > red_tile_2.x) ? red_tile_1.x - red_tile_2.x
                                            : red_tile_2.x - red_tile_1.x;

  u64 y_len = (red_tile_1.y > red_tile_2.y) ? red_tile_1.y - red_tile_2.y
                                            : red_tile_2.y - red_tile_1.y;
  x_len += 1;
  y_len += 1;
  u64 area = x_len * y_len;
  return area;
}

u64 size_of_biggest_rectangle(RedTileData red_tile_data) {
  u64 biggest_area = 0;
  for (u32 i = 0; i < red_tile_data.len; i++) {
    for (u32 j = i + 1; j < red_tile_data.len; j++) {
      u64 value =
          size_of_rectangle(red_tile_data.tiles[i], red_tile_data.tiles[j]);
      if (value > biggest_area) {
        biggest_area = value;
      }
    }
  }
  return biggest_area;
}

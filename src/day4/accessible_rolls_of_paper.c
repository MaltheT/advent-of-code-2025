#include "util/matrix.h"
#include <stddef.h>

#define ROLL '@'
#define N_ADJACENT 8

int accessible_rolls_of_paper(Matrix *rolls_of_paper) {
  int result = 0;

  // directions for 8 neighbors (dx, dy)
  int dirs[N_ADJACENT][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                             {0, 1},   {1, -1}, {1, 0},  {1, 1}};

  for (size_t i = 0; i < rolls_of_paper->M; i++) {
    for (size_t j = 0; j < rolls_of_paper->N; j++) {
      char center = *(char *)get_matrix_element(rolls_of_paper, i, j);
      if (center != ROLL)
        continue;

      int neighbor_rolls = 0;

      // count neighboring rolls
      for (int d = 0; d < N_ADJACENT; d++) {
        int ni = (int)i + dirs[d][0];
        int nj = (int)j + dirs[d][1];

        // skip out-of-bounds neighbors
        if (ni < 0 || nj < 0 || ni >= (int)rolls_of_paper->M ||
            nj >= (int)rolls_of_paper->N)
          continue;

        char neighbor = *(char *)get_matrix_element(rolls_of_paper, ni, nj);
        if (neighbor == ROLL)
          neighbor_rolls++;
      }

      if (neighbor_rolls < 4)
        result++;
    }
  }

  return result;
}
// 5527 is too high

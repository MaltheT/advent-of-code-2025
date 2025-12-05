typedef struct InputSequence {
  int size;
  int *distances;
  char *directions;
} InputSequence;

InputSequence ReadInputSequence(char *path_to_txt);

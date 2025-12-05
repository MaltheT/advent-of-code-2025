typedef struct InputIds {
  int lenght;
  char **firstId;
  char **lastId;
} InputIds;

InputIds ReadInputIds(char *path_to_txt);
char **str_split(char *a_str, const char a_delim);

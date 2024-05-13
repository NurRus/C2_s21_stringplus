#include "s21_string.h"

void *s21_insert(const char *src, const char *str, size_t start_index) {
  int flag_error = 0;
  char *new_str = s21_NULL;
  int src_len = 0;
  if (src != s21_NULL) src_len = (int)s21_strlen(src);
  int str_len = 0;
  if (str != s21_NULL) str_len = (int)s21_strlen(str);
  int new_str_len = src_len + str_len;

  new_str = (char *)malloc(sizeof(char) * (new_str_len + 2));
  for (int i = 0; i <= (int)new_str_len; i++) {
    new_str[i] = '\0';
  }

  if (src == s21_NULL || str == s21_NULL || (int)start_index < 0 ||
      (int)start_index > src_len) {
    flag_error = 1;
    free(new_str);
    new_str = s21_NULL;
  }

  if (flag_error == 0) {
    int j = 0;
    for (int i = 0; i <= src_len; i++) {
      while (j >= (int)start_index && j < (int)(start_index + str_len)) {
        new_str[j] = str[j - start_index];
        j++;
      }
      new_str[j] = src[i];
      j++;
    }
    new_str[new_str_len] = '\0';
  }
  return (void *)new_str;
}

#include "s21_string.h"

void *s21_to_upper(const char *str) {
  int flag_error = 0;
  char *new_str = s21_NULL;

  int str_len = 0;
  if (str != s21_NULL) str_len = (int)s21_strlen(str);

  new_str = (char *)malloc(sizeof(char) * (str_len + 1));
  for (int i = 0; i <= (int)str_len; i++) {
    new_str[i] = '\0';
  }

  if (str == s21_NULL) {
    flag_error = 1;
    free(new_str);
    new_str = s21_NULL;
  }

  if (flag_error == 0) {
    for (int i = 0; i < (int)str_len; i++) {
      if (str[i] >= 97 && str[i] <= 122) {
        new_str[i] = str[i] - 32;
      } else {
        new_str[i] = str[i];
      }
    }
    new_str[str_len] = '\0';
  }
  return (void *)new_str;
}
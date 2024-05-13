#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  int flag_error = 0;
  char *ptr = s21_NULL;

  if (str == s21_NULL || c < 0 || c > 127) {
    flag_error = 1;
  }

  if (flag_error == 0) {
    int i = (int)s21_strlen(str);
    int flag_chr = 0;
    while (i >= 0 && flag_chr == 0) {
      if (str[i] == c) {
        ptr = &((char *)str)[i];
        flag_chr = 1;
      }
      i--;
    }
    if (str[0] == '\0' && c == 0) ptr = (char *)str;
  }

  return ptr;
}

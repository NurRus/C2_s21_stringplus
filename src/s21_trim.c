#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  int flag_error = 0;
  char *new_str = s21_NULL;
  int src_len = 0;
  if (src != s21_NULL) src_len = (int)s21_strlen(src);
  new_str = (char *)malloc(sizeof(char) * (src_len + 1));
  if (src != s21_NULL) {
    for (int i = 0; i <= (int)src_len; i++) {
      new_str[i] = src[i];
    }
  }
  if (src == s21_NULL || trim_chars == s21_NULL) {
    flag_error = 1;
    free(new_str);
    new_str = s21_NULL;
  }
  if (flag_error == 0) {
    int trim_chars_len = (int)s21_strlen(trim_chars);
    int i, j, flag_trim, k;
    for (j = 0; j < trim_chars_len; j++) {
      flag_trim = 0;
      i = 0;
      while (i < src_len && flag_trim == 0) {
        if (new_str[i] == trim_chars[j]) {
          flag_trim = 1;
          for (; i < src_len; i++) {
            new_str[i] = new_str[i + 1];
          }
          src_len--;
        }
        i++;
      }
    }
    for (j = 0; j < trim_chars_len; j++) {
      flag_trim = 0;
      k = src_len - 1;
      while (k >= 0 && flag_trim == 0) {
        if (new_str[k] == trim_chars[j]) {
          flag_trim = 1;
          for (; k < src_len; k++) {
            new_str[k] = new_str[k + 1];
          }
          src_len--;
        }
        k--;
      }
    }
  }
  return (void *)new_str;
}

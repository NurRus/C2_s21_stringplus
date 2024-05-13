
#include "s21_string.h"

static char *lastToken = s21_NULL;

char *s21_strtok(char *str, const char *delim) {
  char *ptr_begin;
  int flag_error = 0;
  if (str != s21_NULL) {
    ptr_begin = str;
  } else {
    if (lastToken == s21_NULL) {
      flag_error = 1;
      ptr_begin = s21_NULL;
    }
    ptr_begin = lastToken;
  }
  if (delim == s21_NULL) {
    flag_error = 1;
    ptr_begin = s21_NULL;
  }
  if (flag_error == 0) {
    int str_len = (int)s21_strlen(ptr_begin);
    int delim_len = (int)s21_strlen(delim);
    int i = 0, j, flag_tok_begin = 0, k;
    while (i < str_len && flag_tok_begin == 0) {
      j = 0;
      k = 0;
      while (j < delim_len) {
        if (ptr_begin[i] != delim[j]) {
          k++;
        }
        j++;
      }
      if (k == delim_len) {
        flag_tok_begin = 1;
        ptr_begin = &ptr_begin[i];
      }
      i++;
    }
    if (flag_tok_begin == 1) {
      int flag_tok_end = 0;
      i = 0;
      while (i < str_len && flag_tok_end == 0) {
        j = 0;
        while (j < delim_len && flag_tok_end == 0) {
          if (ptr_begin[i] == delim[j]) {
            flag_tok_end = 1;
            ptr_begin[i] = '\0';
            lastToken = &ptr_begin[i + 1];
          }
          j++;
        }
        i++;
      }
      if (flag_tok_end == 0) lastToken = s21_NULL;
    } else
      ptr_begin = s21_NULL;
  }
  return ptr_begin;
}

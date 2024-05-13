#include "s21_string.h"

char *s21_strstr(char *str1, char *str2) {
  char *ptr_begin = s21_NULL;

  int flag_error = 0;

  int str1_len = 0;
  if (str1 != s21_NULL) str1_len = (int)s21_strlen(str1);

  int str2_len = 0;
  if (str2 != s21_NULL) str2_len = (int)s21_strlen(str2);

  if (str1 == s21_NULL || str2 == s21_NULL || str1_len < str2_len)
    flag_error = 1;

  if (flag_error == 0) {
    char *ptr_end = str1;

    int i = 0, j = 0, k = 0, flag = 0;

    while (i <= str1_len && flag == 0) {
      j = 0;
      k = 0;
      while (j < str2_len && (i + j) <= str1_len) {
        if (str1[i + j] == str2[j]) {
          k++;
          if (k == 1) ptr_begin = ptr_end;
        }
        j++;
      }
      if (k == j) flag = 1;
      ptr_end++;
      i++;
    }

    if (flag == 0) ptr_begin = s21_NULL;

    if (str2[0] == '\0' || (str1[0] == '\0' && str2[0] == '\0'))
      ptr_begin = str1;
  }

  return ptr_begin;
}
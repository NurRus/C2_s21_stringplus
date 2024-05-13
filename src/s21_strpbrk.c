
#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *ptr = s21_NULL;

  int flag_error = 0;

  if (str1 == s21_NULL || str2 == s21_NULL) {
    flag_error = 1;
  }

  if (flag_error == 0) {
    int str1_len = (int)s21_strlen(str1);

    int str2_len = (int)s21_strlen(str2);

    int i, j, flag_pbrk;
    i = 0;
    flag_pbrk = 0;
    while (i < str1_len && flag_pbrk == 0) {
      j = 0;
      while (j < str2_len && flag_pbrk == 0) {
        if (str1[i] == str2[j]) {
          flag_pbrk = 1;
          ptr = &((char *)str1)[i];
        }
        j++;
      }
      i++;
    }
  }
  return ptr;
}

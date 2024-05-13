#include "s21_string.h"

int s21_strncmp(const char* src, const char* str, size_t n) {
  int result = 0;
  int i = 0;
  int flag = 0;
  int n_copy = n;

  if (s21_strlen(src) == s21_strlen(str)) n_copy = (int)s21_strlen(src);

  /*if((int)n < 0) {  //Сега
        char *s = NULL;
        printf("%c", s[0]);
    }*/

  while (n_copy > 0 && flag == 0) {
    if (src[i] != str[i]) flag = 1;
    n_copy--;
    i++;
  }
  i--;
  if (flag == 1) {
    result = src[i] - str[i];
  }
  return result;
}
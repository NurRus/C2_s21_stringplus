#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  int i = 0;
  while (n > 0) {
    ((unsigned char *)str)[i] = (unsigned char)c;
    n--;
    i++;
  }
  return str;
}
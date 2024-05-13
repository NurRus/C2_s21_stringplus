#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  int flag_error = 0;

  if (src == s21_NULL || dest == s21_NULL || (int)n < 0) {
    flag_error = 1;
    dest = s21_NULL;
  }

  if (flag_error == 0) {
    for (int i = 0; i < (int)n; i++) {
      ((char *)dest)[i] = ((char *)src)[i];
    }
    ((char *)dest)[n] = '\0';
  }
  return dest;
}

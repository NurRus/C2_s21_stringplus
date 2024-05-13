#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *pointer1 = (const unsigned char *)str1;
  const unsigned char *pointer2 = (const unsigned char *)str2;

  int result = 0;

  while (n > 0 && *pointer1 == *pointer2) {
    pointer1++;
    pointer2++;
    n--;
  }

  if (n > 0) {
    result = *pointer1 - *pointer2;
  }
  return result;
}
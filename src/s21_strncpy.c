#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, size_t n) {
  size_t i;
  char *dest_start = dest;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    *dest = src[i];
    dest++;
  }
  for (; i < n; i++) {
    *dest = '\0';
    dest++;
  }
  return dest_start;
}

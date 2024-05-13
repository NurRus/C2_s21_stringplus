
#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  const char *curr;
  for (; *str1 != '\0'; str1++) {
    curr = str2;
    int match = 0;
    for (; *curr != '\0'; curr++)
      if (*curr == *str1) {
        match = 1;
        break;
      }
    if (match == 0)
      count++;
    else
      break;
  }
  return count;
}
#ifndef S21_STRING_H
#define S21_STRING_H

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define N 2048
#define s21_INT_MAX 2147483647
#define s21_INT_MIN -2147483647
#define s21_LONG_INT_MAX 9223372036854775807
#define s21_LONG_INT_MIN -9223372036854775807
#define S21_UNSIGNED_SHOT_INT 65535
#define S21_UNSIGNED_INT 294967295
#define S21_UNSIGNED_LONG_INT 4294967295
#define S21_UNSIGNED_LONG_LONG_INT 18446744073709551615
#define S21_FLOAT_MIN 3.4e-38
#define S21_FLOAT_MAX 3.4e+38
#define S21_DOUBLE_MIN 1.7e-308
#define S21_DOUBLE_MAX 1.7e+308
#define S21_LONG_DOUBLE_MIN 3.4e-4932
#define S21_LONG_DOUBLE_MAX 3.4e+4932

#define s21_NULL ((void *)0)

typedef unsigned long s21_size_t;

struct data_flags {
  int percent;
  int accuracy;
  int space;
  int error;
  int end;
  int alignment;
  int sign;
};

struct data_format {
  int value_accuracy;
  int value_width;
  int lf;
  int ld;
  int hd;
  int hu;
  int lu;
  int f;
  int c;
  int d;
  int s;
  int u;
};

char *s21_strstr(char *str1, char *str2);
char *s21_strchr(const char *str, int ch);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t num);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strrchr(const char *str, int ch);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
char *s21_strerror(int errnum);

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

s21_size_t s21_strcspn(const char *str1, const char *str2);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strtok(char *str, const char *delim);

int s21_sprintf(char *buff, const char *str_form, ...);
int WriteSimv(char simv, char *wr_buff, int wr_count);
int WriteInt(long int d, char *wr_buff, int wr_count, struct data_flags *flg);
int WriteDouble(double f, char *wrf_buff, int wrf_count,
                struct data_flags *fflg, int wrf_value_accuracy);
int WriteStr(char *d_str, char *wr_buff, int wr_count);
char *ParsingFlags(char *p, struct data_flags *flg, struct data_format *frmt,
                   char c);
char *ParsingFormat(char *p, struct data_flags *flg, struct data_format *frmt,
                    char c);
int WriteData(va_list wrd_format_ptr, char *wrd_buff, int wrd_count,
              struct data_flags *wrd_flg, struct data_format *wrd_frmt);
int WriteIntNull(char *wr_buff, struct data_flags *flg,
                 struct data_format *frmt, int wr_count, int wr_prev_count);
int WriteSpace(char *wr_buff, struct data_flags *flg, int wr_value_width,
               int wr_count, int wr_prev_count);
void ZeroingParameters(struct data_flags *flg, struct data_format *frmt);
int WriteUnsignedInt(long unsigned int d, char *wr_buff, int wr_count);
#endif
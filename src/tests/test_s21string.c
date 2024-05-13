#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

START_TEST(s21_strlen_f) {
  char str1[] = "Pourquoi";
  char str2[] = "";
  char str3[] = " 1 ";
  char str4[] = "dans les embouteillages";
  char str5[] = "1234 +_)?>   ";
  ck_assert_int_eq(s21_strlen(str1), strlen(str1));
  ck_assert_int_eq(s21_strlen(str2), strlen(str2));
  ck_assert_int_eq(s21_strlen(str3), strlen(str3));
  ck_assert_int_eq(s21_strlen(str4), strlen(str4));
  ck_assert_int_eq(s21_strlen(str5), strlen(str5));
}
END_TEST

START_TEST(s21_strcspn_f) {
  char str1[] = "Pourquoi";
  char str2[] = "";
  char str3[] = " 1 ";
  char str4[] = "dans les embouteillages";
  char str5[] = "1234 +_)?>   ";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
  ck_assert_int_eq(s21_strcspn(str3, str4), strcspn(str3, str4));
  ck_assert_int_eq(s21_strcspn(str5, str5), strcspn(str5, str5));
}
END_TEST

START_TEST(s21_strpbrk_f) {
  char str1_1[] = "";
  char str1_3[] = "ewf @#$nweo &!@# $$)*^2325";
  char str2_1[] = "";
  char str2_3[] = "!&#@";
  char *str2_4 = s21_NULL;

  char *str_pbrk1 = s21_strpbrk(str1_1, str2_1);
  char *str_true1 = strpbrk(str1_1, str2_1);

  char *str_pbrk2 = s21_strpbrk(str1_3, str2_1);
  char *str_true2 = strpbrk(str1_3, str2_1);

  char *str_pbrk3 = s21_strpbrk(str1_3, str2_3);
  char *str_true3 = strpbrk(str1_3, str2_3);

  char *str_pbrk4 = s21_strpbrk(str1_1, str2_3);
  char *str_true4 = strpbrk(str1_1, str2_3);

  char *str_pbrk5 = s21_strpbrk(str1_3, str2_4);

  ck_assert_ptr_eq(str_pbrk1, str_true1);
  ck_assert_ptr_eq(str_pbrk2, str_true2);
  ck_assert_ptr_eq(str_pbrk3, str_true3);
  ck_assert_ptr_eq(str_pbrk4, str_true4);
  ck_assert_ptr_eq(str_pbrk5, s21_NULL);
}
END_TEST

START_TEST(s21_strerror_f) {
  for (int i = -3; i < 300; i++) {
    ck_assert_pstr_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

START_TEST(s21_strtok_f) {
  char str1[] = "test1/test2//test3////test4/t";
  char delim1[] = "/t";
  char *delim2 = s21_NULL;

  char *str_tok1 = s21_strtok(str1, delim1);
  char *str_tok2 = s21_strtok(NULL, delim1);
  char *str_tok3 = s21_strtok(NULL, delim1);
  char *str_tok4 = s21_strtok(NULL, delim1);
  char *str_tok5 = s21_strtok(NULL, delim1);
  char *str_tok6 = s21_strtok(NULL, delim1);
  char *str_tok7 = s21_strtok(NULL, delim1);
  char *str_tok8 = s21_strtok(NULL, delim1);
  char *str_tok9 = s21_strtok(NULL, delim1);
  char *str_tok10 = s21_strtok(str1, delim2);

  ck_assert_str_eq(str_tok1, "es");
  ck_assert_str_eq(str_tok2, "1");
  ck_assert_str_eq(str_tok3, "es");
  ck_assert_str_eq(str_tok4, "2");
  ck_assert_str_eq(str_tok5, "es");
  ck_assert_str_eq(str_tok6, "3");
  ck_assert_str_eq(str_tok7, "es");
  ck_assert_str_eq(str_tok8, "4");
  ck_assert_ptr_eq(str_tok9, s21_NULL);
  ck_assert_ptr_eq(str_tok10, s21_NULL);
}
END_TEST

START_TEST(s21_sprintf_f) {
  char str[] = "fgwgfergd";
  char buffer1[N] = {'\0'};
  char prov_str1[N] = {'\0'};
  char buffer2[N] = {'\0'};
  char prov_str2[N] = {'\0'};
  char buffer3[N] = {'\0'};
  char buffer4[N] = {'\0'};
  char prov_str4[N] = {'\0'};
  char buffer5[N] = {'\0'};
  char prov_str5[N] = {'\0'};

  int x1 =
      s21_sprintf(buffer1,
                  "%c ergergf %20.20u dfgdfg, %20.10d dfgdf %%c -> %+-20.10f "
                  "- > : efewf -> %s",
                  'A', -76709, -321, 123.5406300035, str);
  int y1 =
      sprintf(prov_str1,
              "%c ergergf %20.20u dfgdfg, %20.10d dfgdf %%c -> %+-20.10f - > "
              ": efewf -> %s",
              'A', -76709, -321, 123.5406300035, str);
  int x2 = s21_sprintf(buffer2,
                       "ergergfdfgdfg, % d dfgdf %%c -> % f "
                       "- > : efewf -> %s",
                       321, 123.5406300035, str);
  int y2 = sprintf(prov_str2,
                   "ergergfdfgdfg, % d dfgdf %%c -> % f "
                   "- > : efewf -> %s",
                   321, 123.5406300035, str);
  int x3 = s21_sprintf(buffer3,
                       "ergergfdfgdfg, % %  d dfgdf %%c -> %  f "
                       "- > : efewf -> %s",
                       -321, 123.5406300035, str);

  int x4 = s21_sprintf(buffer4, "Unknown error %d", -3);
  int y4 = sprintf(prov_str4, "Unknown error %d", -3);

  int x5 =
      s21_sprintf(buffer5, "%lu, %hu, %ld, %hd, %lf", -2147483648, 2147483647,
                  9223372036854775807, 2147483647, 2147483647.3242342323);
  int y5 =
      sprintf(prov_str5, "%lu, %hu, %ld, %hd, %lf", -2147483648, 2147483647,
              9223372036854775807, 2147483647, 2147483647.3242342323);

  ck_assert_pstr_eq(buffer1, prov_str1);
  ck_assert_int_eq(x1, y1);
  ck_assert_pstr_eq(buffer2, prov_str2);
  ck_assert_int_eq(x2, y2);
  ck_assert_int_eq(x3, 0);
  ck_assert_pstr_eq(buffer4, prov_str4);
  ck_assert_int_eq(x4, y4);
  ck_assert_pstr_eq(buffer5, prov_str5);
  ck_assert_int_eq(x5, y5);
}
END_TEST

START_TEST(s21_strstr_f) {
  char str1_1[] = "dfsdfdsssfredqwsf29t";
  char str1_2[] = "29t";
  char str2_1[] = "9tr";
  char str3_1[] = "dfs";
  char str4_1[] = "dfs2";
  char str5_1[] = "sss";
  char str6_1[] = "dfsdfdsssfredqwsf29t1";
  char str7_1[] = "";
  char str8_1[] = "";

  char *str_str1_1 = strstr(str1_1, str1_2);
  char *str_str1_2 = s21_strstr(str1_1, str1_2);

  char *str_str2_1 = strstr(str1_1, str2_1);
  char *str_str2_2 = s21_strstr(str1_1, str2_1);

  char *str_str3_1 = strstr(str1_1, str3_1);
  char *str_str3_2 = s21_strstr(str1_1, str3_1);

  char *str_str4_1 = strstr(str1_1, str4_1);
  char *str_str4_2 = s21_strstr(str1_1, str4_1);

  char *str_str5_1 = strstr(str1_1, str5_1);
  char *str_str5_2 = s21_strstr(str1_1, str5_1);

  char *str_str6_1 = strstr(str1_1, str6_1);
  char *str_str6_2 = s21_strstr(str1_1, str6_1);

  char *str_str7_1 = strstr(str7_1, str8_1);
  char *str_str7_2 = s21_strstr(str7_1, str8_1);

  char *str_str8_1 = strstr(str1_1, str8_1);
  char *str_str8_2 = s21_strstr(str1_1, str8_1);

  char *str_str9_1 = strstr(str8_1, str1_1);
  char *str_str9_2 = s21_strstr(str8_1, str1_1);

  ck_assert_pstr_eq(str_str1_1, str_str1_2);
  ck_assert_pstr_eq(str_str2_1, str_str2_2);
  ck_assert_pstr_eq(str_str3_1, str_str3_2);
  ck_assert_pstr_eq(str_str4_1, str_str4_2);
  ck_assert_pstr_eq(str_str5_1, str_str5_2);
  ck_assert_pstr_eq(str_str6_1, str_str6_2);
  ck_assert_pstr_eq(str_str7_1, str_str7_2);
  ck_assert_pstr_eq(str_str8_1, str_str8_2);
  ck_assert_pstr_eq(str_str9_1, str_str9_2);
}
END_TEST

START_TEST(s21_strncpy_f) {
  char s1_1[20] = "Hello, cucumber!";
  char s2_1[20] = "Hello, cucumber!";
  char s3_1[] = "lol";
  char s1_2[20] = "Hello, cucumber!";
  char s2_2[20] = "Hello, cucumber!";
  char s3_2[] = "\0";
  s21_size_t n1 = 5;
  s21_size_t n2 = 1;
  ck_assert_pstr_eq(strncpy(s1_1, s3_1, n1), s21_strncpy(s2_1, s3_1, n1));
  ck_assert_pstr_eq(strncpy(s1_2, s3_2, n2), s21_strncpy(s2_2, s3_2, n2));
}
END_TEST

START_TEST(s21_insert_f) {
  char src1[] = "12345 11 12 13 14 15";
  char src2[] = "";
  char *src3 = s21_NULL;
  char str1[] = "6789 10";
  char *str2 = s21_NULL;
  char str3[] = "";

  char insert_true1[] = "12345 6789 1011 12 13 14 15";
  void *insert1 = s21_insert(src1, str1, 6);

  char insert_true2[] = "6789 1012345 11 12 13 14 15";
  void *insert2 = s21_insert(src1, str1, 0);

  void *insert3 = s21_insert(src1, str1, -1);

  void *insert4 = s21_insert(src1, str1, 22);

  char insert_true5[] = "12345 11 12 13 14 156789 10";
  void *insert5 = s21_insert(src1, str1, 20);

  char insert_true6[] = "6789 10";
  void *insert6 = s21_insert(src2, str1, 0);

  void *insert7 = s21_insert(src3, str1, 0);

  void *insert8 = s21_insert(src1, str2, 0);

  char insert_true9[] = "";
  void *insert9 = s21_insert(src2, str3, 0);

  ck_assert_pstr_eq(insert1, insert_true1);
  ck_assert_pstr_eq(insert2, insert_true2);
  ck_assert_ptr_eq(insert3, s21_NULL);
  ck_assert_ptr_eq(insert4, s21_NULL);
  ck_assert_pstr_eq(insert5, insert_true5);
  ck_assert_pstr_eq(insert6, insert_true6);
  ck_assert_ptr_eq(insert7, s21_NULL);
  ck_assert_ptr_eq(insert8, s21_NULL);
  ck_assert_pstr_eq(insert9, insert_true9);

  if (insert1) free(insert1);
  if (insert2) free(insert2);
  if (insert3) free(insert3);
  if (insert4) free(insert4);
  if (insert5) free(insert5);
  if (insert6) free(insert6);
  if (insert7) free(insert7);
  if (insert8) free(insert8);
  if (insert9) free(insert9);
}
END_TEST

START_TEST(s21_strncat_f) {
  char s1[10] = "000";
  char s2[10] = "000";
  char s3[] = "12345";
  s21_size_t n1 = 3;
  ck_assert_pstr_eq(strncat(s1, s3, n1), s21_strncat(s2, s3, n1));
}
END_TEST

START_TEST(s21_memchr_f) {
  char str1[] = "¡Hola, guapa! :)";
  int c1 = '\0';
  char str2[] = "¡Hola, guapa! :)";
  int c2 = '!';
  s21_size_t n2 = strlen(str2);
  s21_size_t n1 = strlen(str1);
  ck_assert_ptr_eq(memchr(str1, c1, n1), s21_memchr(str1, c1, n1));
  ck_assert_ptr_eq(memchr(str2, c2, n2), s21_memchr(str2, c2, n2));
}
END_TEST

START_TEST(s21_memcpy_f) {
  unsigned char src1[] = "dfgdgag ! 0dssd";
  unsigned char *src2 = s21_NULL;
  unsigned char src3[] = "";
  unsigned char dest1[] = "";
  unsigned char dest2[30] = "";
  unsigned char *dest3 = s21_NULL;

  ck_assert_pstr_eq(s21_memcpy(dest1, src1, 0), memcpy(dest1, src1, 0));
  ck_assert_pstr_eq(s21_memcpy(dest1, src1, 7), memcpy(dest1, src1, 7));
  ck_assert_pstr_eq(s21_memcpy(dest1, src1, 20), memcpy(dest1, src1, 20));
  ck_assert_pstr_eq(s21_memcpy(dest2, src1, 20), memcpy(dest2, src1, 20));
  ck_assert_pstr_eq(s21_memcpy(dest2, src3, 20), memcpy(dest2, src3, 20));
  ck_assert_pstr_eq(s21_memcpy(dest2, src1, 0), memcpy(dest2, src1, 0));

  ck_assert_ptr_eq(s21_memcpy(dest1, src2, 3), s21_NULL);
  ck_assert_ptr_eq(s21_memcpy(dest3, src1, 3), s21_NULL);
  ck_assert_ptr_eq(s21_memcpy(dest1, src1, -1), s21_NULL);
}
END_TEST

START_TEST(s21_memcmp_f) {
  char str1_1[] = "dfgdgag ! 0dssd";
  char str2_1[] = "dfgdgag ! 0dssd";
  char str1_2[] = "123456789 10 11 12 13 14 15";
  char str2_2[] = "1 3456789 10 11 12 13 14 15";
  char str1_3[] = "123 56789 10 11 12 13 14 15";
  char str2_3[] = "123456789 10 11 12 13 14 15";

  s21_size_t k1 = 17;
  s21_size_t k2 = 3;
  s21_size_t k3 = 20;

  int n1_1 = memcmp(str1_1, str2_1, k1);
  int n2_1 = s21_memcmp(str1_1, str2_1, k1);
  int n1_2 = memcmp(str1_2, str2_2, k1);
  int n2_2 = s21_memcmp(str1_2, str2_2, k1);
  int n1_3 = memcmp(str1_3, str2_3, k1);
  int n2_3 = s21_memcmp(str1_3, str2_3, k1);
  int n1_4 = memcmp(str1_1, str2_1, k2);
  int n2_4 = s21_memcmp(str1_1, str2_1, k2);
  int n1_5 = memcmp(str1_1, str2_1, k3);
  int n2_5 = s21_memcmp(str1_1, str2_1, k3);

  ck_assert_int_eq(n1_1, n2_1);
  ck_assert_int_eq(n1_2, n2_2);
  ck_assert_int_eq(n1_3, n2_3);
  ck_assert_int_eq(n1_4, n2_4);
  ck_assert_int_eq(n1_5, n2_5);
}
END_TEST

START_TEST(s21_memset_f) {
  char str[] = "dfgdgag ! 0dssd";
  int c = '*';
  s21_size_t n1 = 5;
  s21_size_t n2 = 20;
  s21_size_t n3 = 0;

  ck_assert_str_eq(memset(str, c, n1), s21_memset(str, c, n1));
  ck_assert_str_eq(memset(str, c, n2), s21_memset(str, c, n2));
  ck_assert_str_eq(memset(str, c, n3), s21_memset(str, c, n3));
}
END_TEST

START_TEST(s21_strchr_f) {
  char str1[] = "";
  char *str2 = s21_NULL;
  char str3[] = "ewf @#$nweo &!@# $$)*^2325";
  int c1 = 0;
  int c2 = -1;
  int c3 = 128;
  int c4 = (int)'@';

  char *str_chr1 = s21_strchr(str1, c4);
  char *str_true1 = strchr(str1, c4);

  char *str_chr2 = s21_strchr(str1, c1);
  char *str_true2 = strchr(str1, c1);

  char *str_chr3 = s21_strchr(str2, c4);

  char *str_chr4 = s21_strchr(str3, c3);
  char *str_true4 = strchr(str3, c3);

  char *str_chr5 = s21_strchr(str3, c4);
  char *str_true5 = strchr(str3, c4);

  char *str_chr6 = s21_strchr(str3, c2);
  char *str_true6 = strchr(str3, c2);

  ck_assert_ptr_eq(str_chr1, str_true1);
  ck_assert_ptr_eq(str_chr2, str_true2);
  ck_assert_ptr_eq(str_chr3, s21_NULL);
  ck_assert_ptr_eq(str_chr4, str_true4);
  ck_assert_ptr_eq(str_chr5, str_true5);
  ck_assert_ptr_eq(str_chr6, str_true6);
}
END_TEST

START_TEST(s21_strrchr_f) {
  char str1[] = "";
  char *str2 = s21_NULL;
  char str3[] = "ewf @#$nweo &!@# $$)*^2325";
  int c1 = 0;
  int c2 = -1;
  int c3 = 128;
  int c4 = (int)'@';

  char *str_chr1 = s21_strrchr(str1, c4);
  char *str_true1 = strrchr(str1, c4);

  char *str_chr2 = s21_strrchr(str1, c1);
  char *str_true2 = strrchr(str1, c1);

  char *str_chr3 = s21_strrchr(str2, c4);

  char *str_chr4 = s21_strrchr(str3, c3);
  char *str_true4 = strrchr(str3, c3);

  char *str_chr5 = s21_strrchr(str3, c4);
  char *str_true5 = strrchr(str3, c4);

  char *str_chr6 = s21_strrchr(str3, c2);
  char *str_true6 = strrchr(str3, c2);

  ck_assert_ptr_eq(str_chr1, str_true1);
  ck_assert_ptr_eq(str_chr2, str_true2);
  ck_assert_ptr_eq(str_chr3, s21_NULL);
  ck_assert_ptr_eq(str_chr4, str_true4);
  ck_assert_ptr_eq(str_chr5, str_true5);
  ck_assert_ptr_eq(str_chr6, str_true6);
}
END_TEST

START_TEST(s21_strncmp_f) {
  char str1_1[] = "lkdnvkdvlfd ojfsdejr0439tnv";
  char str1_2[] = "lkdnvkdv940";
  char str2_1[] = "ldfds";
  char str2_2[] = "ldfds52352";
  char str3_1[] = "lkdnvkdvlfd ojfsdejr0439tnv";
  char str3_2[] = "lkdnvkdvlfd ojfsdejr0439tnv";

  ck_assert_int_eq(strncmp(str1_1, str1_2, 0), s21_strncmp(str1_1, str1_2, 0));
  ck_assert_int_eq(strncmp(str1_1, str1_2, 8), s21_strncmp(str1_1, str1_2, 8));
  ck_assert_int_eq(strncmp(str1_1, str1_2, 9), s21_strncmp(str1_1, str1_2, 9));
  ck_assert_int_eq(strncmp(str1_1, str1_2, 30),
                   s21_strncmp(str1_1, str1_2, 30));
  ck_assert_int_eq(strncmp(str2_1, str2_2, 5), s21_strncmp(str2_1, str2_2, 5));
  ck_assert_int_eq(strncmp(str2_1, str2_2, 6), s21_strncmp(str2_1, str2_2, 6));
  ck_assert_int_eq(strncmp(str2_1, str2_2, 30),
                   s21_strncmp(str2_1, str2_2, 30));
  ck_assert_int_eq(strncmp(str3_1, str3_2, 27),
                   s21_strncmp(str3_1, str3_2, 27));
  ck_assert_int_eq(strncmp(str3_1, str3_2, 28),
                   s21_strncmp(str3_1, str3_2, 28));
  ck_assert_int_eq(strncmp(str3_1, str3_2, 40),
                   s21_strncmp(str3_1, str3_2, 40));
}
END_TEST

START_TEST(s21_to_upper_f) {
  char str1[] = "";
  char *str2 = s21_NULL;
  char str3[] = "ABcdIFg342az";
  char str_true3[] = "ABCDIFG342AZ";

  void *str_upper1 = s21_to_upper(str1);
  void *str_upper2 = s21_to_upper(str2);
  void *str_upper3 = s21_to_upper(str3);

  ck_assert_pstr_eq((char *)str_upper1, str1);
  ck_assert_ptr_eq(str_upper2, s21_NULL);
  ck_assert_pstr_eq((char *)str_upper3, str_true3);

  if (str_upper1) free(str_upper1);
  if (str_upper2) free(str_upper2);
  if (str_upper3) free(str_upper3);
}
END_TEST

START_TEST(s21_to_lower_f) {
  char str1[] = "";
  char *str2 = s21_NULL;
  char str3[] = "ABcdIFg342AZ";
  char str_true3[] = "abcdifg342az";

  void *str_lower1 = s21_to_lower(str1);
  void *str_lower2 = s21_to_lower(str2);
  void *str_lower3 = s21_to_lower(str3);

  ck_assert_pstr_eq((char *)str_lower1, str1);
  ck_assert_ptr_eq(str_lower2, s21_NULL);
  ck_assert_pstr_eq((char *)str_lower3, str_true3);

  if (str_lower1) free(str_lower1);
  if (str_lower2) free(str_lower2);
  if (str_lower3) free(str_lower3);
}
END_TEST

START_TEST(s21_trim_f) {
  char src1[] = "";
  char *src2 = s21_NULL;
  char src3[] = "wlfklnlas35ewfmd";
  char trim_chars1[] = "";
  char *trim_chars2 = s21_NULL;
  char trim_chars3[] = "fjbcmlw";
  char str_true3[] = "klnas35ed";

  void *str_trim1 = s21_trim(src1, trim_chars3);
  void *str_trim2 = s21_trim(src2, trim_chars3);
  void *str_trim3 = s21_trim(src3, trim_chars3);
  void *str_trim4 = s21_trim(src3, trim_chars2);
  void *str_trim5 = s21_trim(src1, trim_chars1);
  void *str_trim6 = s21_trim(src3, trim_chars1);

  ck_assert_pstr_eq((char *)str_trim1, src1);
  ck_assert_ptr_eq(str_trim2, s21_NULL);
  ck_assert_pstr_eq((char *)str_trim3, str_true3);
  ck_assert_ptr_eq((char *)str_trim4, s21_NULL);
  ck_assert_pstr_eq((char *)str_trim5, src1);
  ck_assert_pstr_eq((char *)str_trim6, src3);

  if (str_trim1) free(str_trim1);
  if (str_trim2) free(str_trim2);
  if (str_trim3) free(str_trim3);
  if (str_trim4) free(str_trim4);
  if (str_trim5) free(str_trim5);
  if (str_trim6) free(str_trim6);
}

END_TEST

Suite *lib_suite(void) {
  Suite *s;
  s = suite_create("Func Check");

  TCase *tc_sprintf;
  TCase *tc_strstr;
  TCase *tc_strlen;
  TCase *tc_strcspn;
  TCase *tc_strpbrk;
  TCase *tc_strerror;
  TCase *tc_strtok;
  TCase *tc_strncpy;
  TCase *tc_insert;
  TCase *tc_strncat;
  TCase *tc_memchr;
  TCase *tc_memcpy;
  TCase *tc_memcmp;
  TCase *tc_memset;
  TCase *tc_strchr;
  TCase *tc_strrchr;
  TCase *tc_strncmp;
  TCase *tc_to_upper;
  TCase *tc_to_lower;
  TCase *tc_trim;

  tc_sprintf = tcase_create("Sprintf func testing");
  suite_add_tcase(s, tc_sprintf);
  tcase_add_test(tc_sprintf, s21_sprintf_f);

  tc_strstr = tcase_create("Strstr func testing");
  suite_add_tcase(s, tc_strstr);
  tcase_add_test(tc_strstr, s21_strstr_f);

  tc_strlen = tcase_create("Strlen func testing");
  suite_add_tcase(s, tc_strlen);
  tcase_add_test(tc_strlen, s21_strlen_f);

  tc_strcspn = tcase_create("Strcspn func testing");
  suite_add_tcase(s, tc_strcspn);
  tcase_add_test(tc_strcspn, s21_strcspn_f);

  tc_strpbrk = tcase_create("Strpbrk func testing");
  suite_add_tcase(s, tc_strpbrk);
  tcase_add_test(tc_strpbrk, s21_strpbrk_f);

  tc_strerror = tcase_create("Strerror func testing");
  suite_add_tcase(s, tc_strerror);
  tcase_add_test(tc_strerror, s21_strerror_f);

  tc_strtok = tcase_create("Strtok func testing");
  suite_add_tcase(s, tc_strtok);
  tcase_add_test(tc_strtok, s21_strtok_f);

  tc_strncpy = tcase_create("Strncpy func testing");
  suite_add_tcase(s, tc_strncpy);
  tcase_add_test(tc_strncpy, s21_strncpy_f);

  tc_insert = tcase_create("Insert func testing");
  suite_add_tcase(s, tc_insert);
  tcase_add_test(tc_insert, s21_insert_f);

  tc_strncat = tcase_create("Strncat func testing");
  suite_add_tcase(s, tc_strncat);
  tcase_add_test(tc_strncat, s21_strncat_f);

  tc_memchr = tcase_create("Memchr func testing");
  suite_add_tcase(s, tc_memchr);
  tcase_add_test(tc_memchr, s21_memchr_f);

  tc_memcpy = tcase_create("Memcpy func testing");
  suite_add_tcase(s, tc_memcpy);
  tcase_add_test(tc_memcpy, s21_memcpy_f);

  tc_memcmp = tcase_create("Memcmp func testing");
  suite_add_tcase(s, tc_memcmp);
  tcase_add_test(tc_memcmp, s21_memcmp_f);

  tc_memset = tcase_create("Memset func testing");
  suite_add_tcase(s, tc_memset);
  tcase_add_test(tc_memset, s21_memset_f);

  tc_strchr = tcase_create("Strchr func testing");
  suite_add_tcase(s, tc_strchr);
  tcase_add_test(tc_strchr, s21_strchr_f);

  tc_strrchr = tcase_create("Strrchr func testing");
  suite_add_tcase(s, tc_strrchr);
  tcase_add_test(tc_strrchr, s21_strrchr_f);

  tc_strncmp = tcase_create("Strncmp func testing");
  suite_add_tcase(s, tc_strncmp);
  tcase_add_test(tc_strncmp, s21_strncmp_f);

  tc_to_upper = tcase_create("To_upper func testing");
  suite_add_tcase(s, tc_to_upper);
  tcase_add_test(tc_to_upper, s21_to_upper_f);

  tc_to_lower = tcase_create("To_lower func testing");
  suite_add_tcase(s, tc_to_lower);
  tcase_add_test(tc_to_lower, s21_to_lower_f);

  tc_trim = tcase_create("Trim func testing");
  suite_add_tcase(s, tc_trim);
  tcase_add_test(tc_trim, s21_trim_f);

  return s;
}

int main(void) {
  Suite *s;
  SRunner *sr;

  s = lib_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_VERBOSE);
  srunner_free(sr);
  return 0;
}

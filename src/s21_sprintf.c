#include "s21_string.h"

int s21_sprintf(char *buff, const char *str_form, ...) {
  int count = 0;
  int prev_count = 0;
  char c_ptr;
  va_list format_ptr;
  va_start(format_ptr, str_form);
  char *ptr = (char *)str_form;
  struct data_flags flags = {0, 0, 0, 0, 0, 0, 0};
  struct data_format format = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  while (*ptr && flags.error == 0) {
    while (*ptr && *ptr != '%') {
      count = WriteSimv(*ptr, buff, count);
      ptr++;
    }
    if (*ptr == '%' && flags.percent == 0) {
      ptr++;
      flags.percent = 1;
      if (*ptr == '%') {
        count = WriteSimv(*ptr, buff, count);
        flags.end = 1;
        flags.percent = 0;
      }
    }
    c_ptr = *ptr;
    while (*ptr && flags.error == 0 && *ptr <= '9' && *ptr != '%') {
      ptr = ParsingFlags(ptr, &flags, &format, c_ptr);
    }
    ptr = ParsingFormat(ptr, &flags, &format, c_ptr);
    prev_count = count;
    count = WriteData(format_ptr, buff, count, &flags, &format);
    count = WriteIntNull(buff, &flags, &format, count, prev_count);
    count = WriteSpace(buff, &flags, format.value_width, count, prev_count);
    ZeroingParameters(&flags, &format);
    ptr++;
  }
  buff[count] = '\0';
  if (flags.error == 1) {
    buff = s21_NULL;
    count = 0;
  }
  va_end(format_ptr);
  return count;
}

int WriteSimv(char simv, char *wr_buff, int wr_count) {
  wr_buff[wr_count] = simv;
  wr_count++;
  return wr_count;
}

int WriteInt(long int d, char *wr_buff, int wr_count, struct data_flags *flg) {
  if (flg->space == 1 && d >= 0 && flg->sign == 0) {
    wr_buff[wr_count] = ' ';
    wr_count++;
  }
  int n = 0, nn = 0;
  long int dw = labs(d);
  int m = wr_count;
  int mass_int[40];
  for (int i = 0; i < 40; i++) {
    mass_int[i] = 0;
  }
  long double f = dw;
  do {
    dw = dw / 10;
    f = f / 10;
    mass_int[n] = f * 10 - dw * 10;
    n++;
  } while (dw >= 1);
  if (d < 0 || flg->sign == 1) {
    if (d < 0) wr_buff[m] = '-';
    if (d > 0) wr_buff[m] = '+';
    for (int i = n; i > 0; i--) {
      mass_int[i] = mass_int[i - 1];
    }
    mass_int[0] = 0;
    nn = 1;
  }
  for (int i = 0; i < n; i++) {
    wr_buff[m + nn + i] = mass_int[n - 1 + nn - i] + '0';
    wr_count++;
  }
  return wr_count + nn;
}

int WriteDouble(double f, char *wrf_buff, int wrf_count,
                struct data_flags *fflg, int wrf_value_accuracy) {
  if (fflg->space == 1 && f >= 0 && fflg->sign == 0) {
    wrf_buff[wrf_count] = ' ';
    wrf_count++;
  }
  int n = 6;
  int fi = f;
  long double fw = fabs(f) - fi;
  if (fflg->accuracy == 1) {
    n = wrf_value_accuracy;
  }
  fw = fw * pow(10, n);
  if (fw - (int)fw >= 0.5) {
    fw++;
  }
  fflg->space = 0;
  wrf_count = WriteInt(fi, wrf_buff, wrf_count, fflg);
  if (fw != 0) {
    wrf_buff[wrf_count] = '.';
    wrf_count++;
    fflg->sign = 0;
    wrf_count = WriteInt(fw, wrf_buff, wrf_count, fflg);
  }
  return wrf_count;
}

int WriteStr(char *d_str, char *wr_buff, int wr_count) {
  for (unsigned i = 0; i < s21_strlen(d_str); i++) {
    wr_buff[wr_count] = d_str[i];
    wr_count++;
  }
  return wr_count;
}

char *ParsingFlags(char *p, struct data_flags *flg, struct data_format *frmt,
                   char c) {
  if (c != '%' && flg->percent == 1 && *p) {
    if (*p == '-') {
      flg->alignment++;
      p++;
    }
    if (*p == '+' && flg->space == 0) {
      flg->sign++;
      p++;
    } else if (*p == '+' && flg->space > 0)
      flg->error = 1;
    if (*p == ' ' && flg->sign == 0 && flg->percent == 1) {
      flg->space++;
      p++;
    } else if (*p == ' ' && flg->sign == 1)
      flg->error = 1;
    while (*p >= '0' && *p <= '9' && flg->accuracy == 0) {
      frmt->value_width = frmt->value_width * 10 + (*p - '0');
      p++;
    }
    if (*p == '.') {
      flg->accuracy++;
      p++;
      while (*p >= '0' && *p <= '9') {
        frmt->value_accuracy = frmt->value_accuracy * 10 + (*p - '0');
        p++;
      }
    }
  }
  if (flg->sign > 1 || flg->accuracy > 1 || flg->space > 1 ||
      flg->alignment > 1)
    flg->error = 1;
  return p;
}

char *ParsingFormat(char *p, struct data_flags *flg, struct data_format *frmt,
                    char c) {
  if (c != '%' && flg->percent == 1 && *p && flg->error == 0) {
    if (*p == 'f') frmt->f = 1;
    if (*p == 'd') frmt->d = 1;
    if (*p == 'c') frmt->c = 1;
    if (*p == 's') frmt->s = 1;
    if (*p == 'u') frmt->u = 1;
    if (*p == 'l' && flg->end == 0) {
      p++;
      if (*p == 'f')
        frmt->lf = 1;
      else if (*p == 'd')
        frmt->ld = 1;
      else if (*p == 'u')
        frmt->lu = 1;
      else
        flg->error = 1;
    }
    if (*p == 'h' && flg->end == 0) {
      p++;
      if (*p == 'd')
        frmt->hd = 1;
      else if (*p == 'u')
        frmt->hu = 1;
      else
        flg->error = 1;
    }
    if (frmt->f + frmt->d + frmt->c + frmt->s + frmt->lf + frmt->ld + frmt->hd +
            frmt->u + frmt->lu + frmt->hu >
        0)
      flg->end = 1;
    else
      flg->error = 1;
  }
  return p;
}

int WriteData(va_list wrd_format_ptr, char *wrd_buff, int wrd_count,
              struct data_flags *wrd_flg, struct data_format *wrd_frmt) {
  if (wrd_frmt->d == 1 && wrd_flg->error == 0) {
    int i_d = va_arg(wrd_format_ptr, int);
    if (i_d <= s21_INT_MAX && i_d >= s21_INT_MIN)
      wrd_count = WriteInt(i_d, wrd_buff, wrd_count, wrd_flg);
    else
      wrd_flg->error = 1;
  }
  if (wrd_frmt->hd == 1 && wrd_flg->error == 0) {
    int h_d = (short int)(va_arg(wrd_format_ptr, int));
    if (h_d <= s21_INT_MAX && h_d >= s21_INT_MIN)
      wrd_count = WriteInt(h_d, wrd_buff, wrd_count, wrd_flg);
    else
      wrd_flg->error = 1;
  }
  if (wrd_frmt->ld == 1 && wrd_flg->error == 0) {
    long int l_d = (long int)(va_arg(wrd_format_ptr, long int));
    if ((l_d > s21_INT_MAX && l_d <= s21_LONG_INT_MAX) ||
        (l_d < s21_INT_MIN && l_d >= s21_LONG_INT_MIN))
      wrd_count = WriteInt(l_d, wrd_buff, wrd_count, wrd_flg);
    else
      wrd_flg->error = 1;
  }
  if ((wrd_frmt->f == 1 || wrd_frmt->lf == 1) && wrd_flg->error == 0) {
    double f_d = va_arg(wrd_format_ptr, double);
    wrd_count = WriteDouble(f_d, wrd_buff, wrd_count, wrd_flg,
                            wrd_frmt->value_accuracy);
  }
  if (wrd_frmt->c == 1 && wrd_flg->error == 0)
    wrd_count =
        WriteSimv((char)(va_arg(wrd_format_ptr, int)), wrd_buff, wrd_count);
  if (wrd_frmt->s == 1 && wrd_flg->error == 0)
    wrd_count =
        WriteStr((char *)(va_arg(wrd_format_ptr, char *)), wrd_buff, wrd_count);
  if (wrd_frmt->u == 1 && wrd_flg->error == 0) {
    unsigned int u_d = (unsigned int)(va_arg(wrd_format_ptr, int));
    wrd_count = WriteInt(u_d, wrd_buff, wrd_count, wrd_flg);
  }
  if (wrd_frmt->hu == 1 && wrd_flg->error == 0) {
    unsigned short int uh_d = (unsigned short int)(va_arg(wrd_format_ptr, int));
    wrd_count = WriteUnsignedInt(uh_d, wrd_buff, wrd_count);
  }
  if (wrd_frmt->lu == 1 && wrd_flg->error == 0) {
    unsigned long int ul_d =
        (unsigned long int)(va_arg(wrd_format_ptr, long int));
    wrd_count = WriteUnsignedInt(ul_d, wrd_buff, wrd_count);
  }
  return wrd_count;
}

int WriteIntNull(char *wr_buff, struct data_flags *flg,
                 struct data_format *frmt, int wr_count, int wr_prev_count) {
  int frmt_int = frmt->d + frmt->u + frmt->ld + frmt->lu + frmt->hd + frmt->hu;
  int line_length = wr_count - wr_prev_count;
  int nn = 0;
  if (wr_buff[wr_prev_count] == '+' || wr_buff[wr_prev_count] == '-') {
    nn = 1;
  }
  int n = frmt->value_accuracy - line_length;
  if (flg->error == 0 && frmt_int == 1 && n >= 0) {
    int k = n + nn;
    int m = wr_count - 1;
    for (int i = 0; i < line_length; i++) {
      wr_buff[m + k] = wr_buff[m - i];
      k--;
    }
    for (int i = nn; i < n + nn * 2; i++) {
      wr_buff[wr_prev_count + i] = '0';
    }
    wr_count = wr_count + n + nn;
  }
  return wr_count;
}

int WriteSpace(char *wr_buff, struct data_flags *flg, int wr_value_width,
               int wr_count, int wr_prev_count) {
  int line_length = wr_count - wr_prev_count;
  int n = wr_value_width - line_length;
  if (flg->error == 0 && flg->end == 1 && n > 0) {
    if (flg->alignment == 1) {
      for (int i = 0; i < n; i++) {
        wr_buff[wr_count] = ' ';
        wr_count++;
      }
    } else if (flg->alignment == 0) {
      int k = n;
      int m = wr_count - 1;
      for (int i = 0; i < line_length; i++) {
        wr_buff[m + k] = wr_buff[m - i];
        k--;
      }
      for (int i = wr_prev_count; i < n + wr_prev_count; i++) {
        wr_buff[i] = ' ';
      }
      wr_count = wr_count + n;
    }
  }
  return wr_count;
}

void ZeroingParameters(struct data_flags *flg, struct data_format *frmt) {
  flg->percent = 0;
  flg->accuracy = 0;
  flg->space = 0;
  flg->end = 0;
  flg->alignment = 0;
  flg->sign = 0;

  frmt->value_accuracy = 0;
  frmt->value_width = 0;
  frmt->lf = 0;
  frmt->ld = 0;
  frmt->lu = 0;
  frmt->hd = 0;
  frmt->hu = 0;
  frmt->f = 0;
  frmt->c = 0;
  frmt->d = 0;
  frmt->s = 0;
  frmt->u = 0;
}

int WriteUnsignedInt(long unsigned int d, char *wr_buff, int wr_count) {
  int n = 0, nn = 0;
  long unsigned int dw = d;
  int m = wr_count;
  int mass_int[20];
  for (int i = 0; i < 20; i++) {
    mass_int[i] = 0;
  }
  long double f = dw;
  do {
    dw = dw / 10;
    f = f / 10;
    mass_int[n] = f * 10 - dw * 10;
    n++;
  } while (dw >= 1);
  for (int i = 0; i < n; i++) {
    wr_buff[m + nn + i] = mass_int[n - 1 + nn - i] + '0';
    wr_count++;
  }
  return wr_count + nn;
}
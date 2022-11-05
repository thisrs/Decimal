#include "s21_decimal.h"
#include "s21_dbinary.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal one = { 0};

  *result = s21_rescale(value, 0);

  if (value.bits8[15] == 1) {
    result->bits8[15] = 0;
    *result = s21_binadd(*result, one);
    result->bits8[15] = 1;
  }

  return 0;
}

#include "s21_decimal.h"
#include "s21_dbinary.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = s21_binmul(value_1, value_2);
  result->bits8[14] = value_1.bits8[14] + value_2.bits8[14];
  *result = s21_normalize(*result);
  return s21_type(*result);
}

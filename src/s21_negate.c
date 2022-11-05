#include "s21_decimal.h"

uint32_t s21_get_sign(const s21_decimal *value) {
    return (value->bits8[15] & SIGN_MASK) != 0;
}

void s21_set_sign(s21_decimal *value, int sign_value) {
    sign_value ? (value->bits8[15] |= SIGN_MASK) :
                 (value->bits8[15] &= ~SIGN_MASK);
}

void s21_decimal_copy(s21_decimal* dst, s21_decimal* src) {
    dst->bits64[0] = src->bits64[0];
    dst->bits64[1] = src->bits64[1];
}

int s21_negate(s21_decimal value, s21_decimal *result) {
    if (s21_get_sign(&value))
        s21_set_sign(&value, 0);
    else
        s21_set_sign(&value, 1);

    s21_decimal_copy(result, &value);

    return 0;
}


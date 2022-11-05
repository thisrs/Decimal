#include "s21_decimal.h"
#include "s21_dbinary.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (s21_iszero(value_2))
        return 3;
    if (!(s21_div(value_1, value_2, result) && s21_truncate(*result, result) &&
          s21_mul(value_2, *result, result) && s21_sub(value_1, *result, result)))
                    return 1;
    return 0;
}
/* long double i = s21_trunc(x/y);
    if (isinf(y) && isfinite(x))
        return x;
    return x - i*y; */

#include "s21_decimal.h"
#include "s21_dbinary.h"
#include "s21_dconst.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    int count, exp = value.bits8[14];
    while (exp > 0) {
        if (exp == 1)
            count = (s21_binmod(value, S21_DECIMAL_TEN).bits32[0]) >= 5 ? 1 : 0;
        value = s21_bindiv(value, S21_DECIMAL_TEN);
        exp--;
    }
    *result = value;
    result->bits32[0] += count;
    return 0;
}

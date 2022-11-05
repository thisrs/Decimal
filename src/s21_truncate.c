#include "s21_decimal.h"
#include "s21_dbinary.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    if (s21_type(value))
        return 1;
    *result = s21_rescale(value, 0);
    return 0;
}

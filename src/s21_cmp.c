#include "s21_decimal.h"
#include "s21_dbinary.h"

int s21_is_less(s21_decimal a, s21_decimal b) {
    a = s21_conjugate(s21_normalize(a));
    b = s21_conjugate(s21_normalize(b));
    if (a.bits8[14] > b.bits8[14])
        return 1;
    if (s21_bincmp(a, b) < 0)
        return 1;
    return 0;
}
int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
    a = s21_conjugate(s21_normalize(a));
    b = s21_conjugate(s21_normalize(b));
    if (a.bits8[14] > b.bits8[14])
        return 1;
    if (s21_bincmp(a, b) <= 0)
        return 1;
    return 0;
}
int s21_is_greater(s21_decimal a, s21_decimal b) {
    return !s21_is_less_or_equal(a, b);
}
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
    return !s21_is_less(a, b);
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
    a = s21_normalize(a);
    b = s21_normalize(b);
    if (!s21_bincmp(a, b) && a.bits8[15] == b.bits8[15] && a.bits8[14] == b.bits8[14])
        return 1;
    return 0;
}
int s21_is_not_equal(s21_decimal a, s21_decimal b) {
    return !s21_is_equal(a, b);
}

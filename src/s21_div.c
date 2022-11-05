#include "s21_decimal.h"
#include "s21_dbinary.h"

void set_to_inf(s21_decimal value_1, s21_decimal value_2, s21_decimal *inf) {
    *inf = S21_DECIMAL_INF;
    inf->bits8[15] = value_2.bits8[15] ^ value_1.bits8[15];
}

s21_decimal round_even(s21_decimal n, s21_decimal last) {
    s21_decimal min1 = s21_binsub(S21_DECIMAL_MAX, S21_DECIMAL_ONE);
    if (((n.bits8[0] & 1) && last.bits8[0] >= 5) || (!(n.bits8[0] & 1) && last.bits8[0] > 5)) {
        if (s21_bincmp(n, min1) > 0)
            return S21_DECIMAL_INF;
        return s21_binadd(n, S21_DECIMAL_ONE);
    }
    return n;
}
void addscale(s21_decimal* n, char scale) {
    if (n->bits8[14] + scale > 28)
        *n = s21_rescale(*n, n->bits8[14] - scale);
    n->bits8[14] += scale;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    set_to_inf(value_1, value_2, result);
    if (s21_iszero(value_2))
        return 3;
    s21_decimal r = s21_binmod(value_1, value_2), q = s21_bindiv(value_1, value_2);
    q.bits8[14] = 0;
    while (!s21_iszero(r) && q.bits8[14] < 28) {
        while (s21_bincmp(r, value_2) < 0) {
            r = s21_binmul(r, S21_DECIMAL_TEN);
            q = s21_binmul(q, S21_DECIMAL_TEN);
            q.bits8[14]++;
        }
        if (s21_bincmp(q, s21_binsub(S21_DECIMAL_MAX, s21_bindiv(r, value_2))) < 0)
            q = s21_binadd(q, s21_bindiv(r, value_2));
        else
            break;
        r = s21_binmod(r, value_2);
    }
    if (!s21_iszero(r))
        q = round_even(q, s21_bindiv(r, value_2));
    result = s21_bincpy(result, &q);
    addscale(result, value_1.bits8[14] - value_2.bits8[14]);
    result->bits8[15] = value_2.bits8[15] ^ value_1.bits8[15];
    return 0;
}

#include "s21_decimal.h"
#include "s21_dbinary.h"
#include "s21_dconst.h"
#include <stdio.h>

#define MAX 4294967295

int flag(int a) {
    return a ? 1 : 0;
}

void bin_output(s21_decimal a) {
    for (int i = 2; i >= 0; i--)
        for (int j = 31; j >= 0; j--)
            printf("%d", flag(a.bits32[i] & (1U << j)));
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int exp1 = value_1.bits8[14], exp2 = value_2.bits8[14], flag = 0;
    if (value_1.bits8[14] + value_2.bits8[14] >= 28 &&
        (value_1.bits32[2] > MAX / 10 &&
        value_2.bits32[2] > MAX / 10)) {
        value_1.bits8[14] = 1;
        s21_round(value_1, &value_1);
        value_1.bits8[14] = exp1 - 1;
        value_2.bits8[14] = 1;
        s21_round(value_2, &value_2);
        value_2.bits8[14] = exp2 - 1;
        result->bits32[0] = 0;
        result->bits32[1] = 0;
        result->bits32[2] = 0;
        s21_add(value_1, value_2, result);
        exp1--;
        exp2--;
    } else if (!value_1.bits8[15] && !value_2.bits8[15]) {
        if (value_1.bits8[14] != value_2.bits8[14])
            s21_exp_equalize(&value_1, &value_2);
        for (int i = 0; i < 3; i++) {
            uint32_t max_int = MAX;
            if (MAX - value_1.bits32[i] - value_2.bits32[i] - result->bits32[i] >= 0) {
                result->bits32[i] += value_1.bits32[i] + value_2.bits32[i];
            } else {
                if (value_1.bits32[i] > value_2.bits32[i]) {
                    max_int -= value_1.bits32[i];
                    value_2.bits32[i] -= max_int;
                    result->bits32[i] += value_2.bits32[i] - 1;
                } else {
                    max_int -= value_2.bits32[i];
                    value_1.bits32[i] -= max_int;
                    result->bits32[i] += value_1.bits32[i] - 1;
                }
                if (i <= 1 && result->bits32[i + 1] != MAX)
                    result->bits32[i + 1]++;
                else
                    flag = 1;
            }
        }
        result->bits8[14] = exp1;
    } else if ((!value_1.bits8[15] && value_2.bits8[15]) && (value_1.bits8[15] && !value_2.bits8[15])) {
        if (value_1.bits8[15]) {
            s21_sub(value_2, value_1, result);
            value_1.bits8[15] = 0;
        } else {
            s21_sub(value_1, value_2, result);
            value_2.bits8[15] = 0;
        }
    } else if (value_1.bits8[15] && value_2.bits8[15]) {
        value_1.bits8[15] = 0;
        value_2.bits8[15] = 0;
        if (s21_add(value_1, value_2, result) == 1)
            flag = 2;
    }
    return flag;
}

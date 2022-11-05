#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int schet = 0;
    if (src < 0) {
        src *= -1;
        dst->bits8[15] = 1;
    }
    while (src != 0) {
        int temp = src % 256;
        dst->bits8[schet++] = temp >= 127 ? temp - 256 : temp;
        src /= 256;
    }
    return  0;
}

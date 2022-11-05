#include "s21_decimal.h"
#include "s21_dbinary.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    *dst = 0;
    src = s21_rescale(src, 0);
    if (src.bits32[1] && src.bits32[2] && src.bits32[0] > 2147483648u) {
        *dst = INT32_MAX + src.bits8[15];
        return 1;
    } else if (src.bits32[0] == 2147483648u) {
        *dst = INT32_MIN;
    }
    *dst = -(src.bits8[15] >> 7)*src.bits32[0];
    return 0;
}

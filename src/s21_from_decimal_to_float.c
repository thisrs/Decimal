#include "s21_decimal.h"
#include "s21_dbinary.h"
#include "s21_dconst.h"
#include <math.h>
#define MAX 4294967295

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    *dst = 0.0;
    int q = 0, flag = 0;
    if (!s21_type(src)) {
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 32; i++) {
                if (src.bits32[j] & (1 << i))
                    *dst += pow(2, q);
                q++;
            }
        }
        while (src.bits8[14] != 0) {
            *dst /= 10;
            src.bits8[14]--;
        }
        if (src.bits8[15]) *dst = -*dst;
    } else {
        flag = 1;
        *dst = 0.0;
    }
    return flag;
}

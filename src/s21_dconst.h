#ifndef SRC_S21_DCONST_H_
#define SRC_S21_DCONST_H_
#include <stdint.h>
// mantissa * 10^(exp)
typedef union {
    uint64_t bits64[2];
    uint32_t bits32[4];
    uint16_t bits16[8];
    uint8_t bits8[16];
    int32_t bits[4];
} s21_decimal;

#define SIGN_MASK 0x80

#define S21_DECIMAL_ZERO ((s21_decimal){{0, 0}})
#define S21_DECIMAL_ONE ((s21_decimal){{1, 0}})
#define S21_DECIMAL_TEN ((s21_decimal){{10, 0}})
#define S21_DECIMAL_MAX ((s21_decimal){{-1, 0xFFFFFFFF}})
#define S21_DECIMAL_MIN ((s21_decimal){{-1, 0x80000000FFFFFFFF}})
#define S21_DECIMAL_INF ((s21_decimal){{0, 0xFF000000000000}})
#define S21_DECIMAL_NAN ((s21_decimal){{0, 0x1D000000000000}})
#endif  // ! SRC_S21_DCONST_H_

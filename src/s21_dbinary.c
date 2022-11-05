#include "s21_dbinary.h"

char absd(char a, char b) {
    if (a - b < 0)
        return b - a;
    return a - b;
}

s21_decimal pow10d(unsigned char n) {
    if (n) {
        s21_decimal ten = S21_DECIMAL_TEN;
        n--;
        while (n > 0) {
            if (n%2) {
                ten = s21_binmul(ten, S21_DECIMAL_TEN);
                n--;
            } else {
                ten = s21_binmul(ten, ten);
                n /= 2;
            }
        }
        return ten;
    }
    return S21_DECIMAL_ONE;
}

int s21_exp_equalize(s21_decimal *value_1, s21_decimal *value_2) {
    s21_decimal *biggest_exp;
    s21_decimal *smaller_exp;
    if (value_1->bits8[14] > value_2->bits8[14]) {
        biggest_exp = value_1;
        smaller_exp = value_2;
    } else {
        biggest_exp = value_2;
        smaller_exp = value_1;
    }
    s21_decimal tmp = S21_DECIMAL_ZERO;
    while (value_1->bits8[14] != value_2->bits8[14]) {
        if (smaller_exp->bits32[2] < INT32_MAX / 10) {
            s21_decimal tmp1 = s21_lshift(*smaller_exp, 1), tmp2 = s21_lshift(*smaller_exp, 3);
            tmp = s21_binadd(tmp1, tmp2);
            *smaller_exp = tmp;
            smaller_exp->bits8[14]++;
        } else {
            tmp = s21_bindiv(*biggest_exp, S21_DECIMAL_TEN);
            *biggest_exp = tmp;
            biggest_exp->bits8[14]--;
        }
    }
    return biggest_exp->bits8[14];
}
s21_decimal s21_rescale(s21_decimal old, unsigned char scale) {
    if (scale > 28)
        return old;
    s21_decimal tenpow = pow10d(absd(scale, old.bits8[14]));
    if (absd(scale, old.bits8[14]) > 0)
        old = s21_bindiv(old, tenpow);
    else if (absd(scale, old.bits8[14]) < 0)
        old = s21_binmul(old, tenpow);
    old.bits8[14] = scale;
    return old;
}
s21_decimal s21_normalize(s21_decimal n) {
    while (s21_iszero(s21_binmod(n, S21_DECIMAL_TEN)) && n.bits8[14]) {
        n = s21_bindiv(n, S21_DECIMAL_TEN);
        n.bits8[14]--;
    }
    return n;
}
s21_decimal s21_conjugate(s21_decimal n) {
    if (!n.bits8[15])
        return n;
    n.bits8[15] = 0;
    return s21_binadd(s21_not(n), S21_DECIMAL_ONE);
}

void* s21_bincpy(void* dest, void* src) {
    unsigned char *dest_p = (unsigned char *)dest;
    const unsigned char *src_p = (const unsigned char *)src;
    for (unsigned int i = 0; i < sizeof(s21_decimal); i++)
        dest_p[i] = src_p[i];
    return dest_p;
}
int s21_iszero(s21_decimal val) {
    if (!val.bits64[0] && !val.bits32[2] && s21_type(val) == D_NORMAL)
        return 1;
    return 0;
}
int s21_type(s21_decimal a) {
    int type = D_NEGINF;
    if (a.bits8[14] < 29)
        type = D_NORMAL;
    else if (a.bits8[14] != 255)
        type = D_NAN;
    else if (!a.bits8[15])
        type = D_INF;
    return type;
}

s21_decimal s21_lshift(s21_decimal val, int shift) {
    uint32_t buff;
    for (int q = 0; q < shift; q++) {
        val.bits32[2] <<= 1;
        for (int i = 1; i >= 0; i--) {
            buff = val.bits32[i] & (1 << 31);
            val.bits32[i] <<= 1;
            val.bits32[i + 1] = (val.bits32[i + 1] & -2) | (buff >> 31);
        }
    }
    return val;
}
s21_decimal s21_rshift(s21_decimal val, int shift) {
    uint32_t buff;
    for (int q = 0; q < shift; q++) {
        val.bits32[0] >>= 1;
        for (int i = 1; i < 3; i++) {
            buff = val.bits32[i] & 1;
            val.bits32[i] >>= 1;
            val.bits32[i - 1] = (val.bits32[i - 1] & 0x7FFFFFFF) | (buff << 31);
        }
    }
    return val;
}
s21_decimal s21_not(s21_decimal val) {
    for (int i = 0; i < 3; i++)
        val.bits32[i] = ~val.bits32[i];
    return val;
}

int s21_bincmp(s21_decimal a, s21_decimal b) {
    int i = 2;
    for (; i > 0 && a.bits32[i] == b.bits32[i]; i--) { }
    return (a.bits32[i] > b.bits32[i]) - (a.bits32[i] < b.bits32[i]);
}
s21_decimal s21_binadd(s21_decimal summand, s21_decimal addend) {
    s21_decimal res = summand;
    for (uint8_t i = 0, carry = 0; i < 3; i++) {
        res.bits32[i] = summand.bits32[i] + addend.bits32[i] + carry;
        carry = (addend.bits32[i] > UINT32_MAX - carry) || \
                (summand.bits32[i] > UINT32_MAX - addend.bits32[i] - carry);
    }
    return res;
}
s21_decimal s21_binsub(s21_decimal summand, s21_decimal addend) {
    return s21_binadd(summand, s21_binadd(s21_not(addend), S21_DECIMAL_ONE));
}

s21_decimal s21_bindiv(s21_decimal n, s21_decimal d) {
    s21_decimal r = S21_DECIMAL_ZERO, q = S21_DECIMAL_ZERO;
    for (int i = 95; i >= 0; i--) {
        r = s21_lshift(r, 1);
        r.bits8[0] |= (n.bits8[i/8] & (1 << (i%8))) >> i%8;
        if (s21_bincmp(r, d) != -1) {
            r = s21_binsub(r, d);
            q.bits8[i/8] |= 1 << (i%8);
        }
    }
    q.bits8[14] = n.bits8[14];
    q.bits8[15] = n.bits8[15] ^ d.bits8[15];
    return q;
}
s21_decimal s21_binmod(s21_decimal n, s21_decimal d) {
    s21_decimal r = S21_DECIMAL_ZERO;
    for (int i = 95; i >= 0; i--) {
        r = s21_lshift(r, 1);
        r.bits8[0] |= (n.bits8[i/8] & (1 << (i%8))) >> i%8;
        if (s21_bincmp(r, d) != -1)
            r = s21_binsub(r, d);
    }
    r.bits8[14] = n.bits8[14];
    return r;
}
s21_decimal s21_binmul(s21_decimal multer, s21_decimal multend) {
    s21_decimal res = S21_DECIMAL_ZERO;
    for (uint8_t i = 0; i < 96; i++)
        if (multend.bits8[i/8] & (1 << i%8))
            res = s21_binadd(res, s21_lshift(multer, i));
    res.bits8[14] = multer.bits8[14];
    res.bits8[15] = multer.bits8[15] ^ multend.bits8[15];
    return res;
}

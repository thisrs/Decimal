#include <stdlib.h>
#include <check.h>
#include "s21_decimal.h"

#define S21_DECIMAL_ZERO ((s21_decimal){{0, 0}})


START_TEST(s21_sub_test) {

    int result1,
            result2;

    s21_decimal one,
            two,
            res1,
            res2;

    //printf("Test_1: \n");

    one = S21_DECIMAL_ZERO;
    two = S21_DECIMAL_ZERO;
    res1 = S21_DECIMAL_ZERO;
    res2 = S21_DECIMAL_ZERO;

    one.bits32[0] = 10;
    s21_set_sign(&one, 0);
    two.bits32[0] = 5;
    s21_set_sign(&two, 0);

    result1 = s21_sub(one, two, &res1);
    result2 = 0;

    res2.bits32[0] = 5;
    s21_set_sign(&res2, 0);

    ck_assert_int_eq(result1, result2);
    ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
    ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);

    //printf("Test_2: \n");

    one = S21_DECIMAL_ZERO;
    two = S21_DECIMAL_ZERO;
    res1 = S21_DECIMAL_ZERO;
    res2 = S21_DECIMAL_ZERO;

    one.bits32[0] = 5;
    s21_set_sign(&one, 0);
    two.bits32[0] = 10;
    s21_set_sign(&two, 0);

    result1 = s21_sub(one, two, &res1);
    result2 = 0;

    res2.bits32[0] = 5;
    s21_set_sign(&res2, 1);

    ck_assert_int_eq(result1, result2);
    ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
    ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);

    //printf("Test_3: \n");

    one = S21_DECIMAL_ZERO;
    two = S21_DECIMAL_ZERO;
    res1 = S21_DECIMAL_ZERO;
    res2 = S21_DECIMAL_ZERO;

    one.bits32[0] = 10;
    s21_set_sign(&one, 1);
    two.bits32[0] = 5;
    s21_set_sign(&two, 0);

    result1 = s21_sub(one, two, &res1);
    result2 = 0;

    res2.bits32[0] = 15;
    s21_set_sign(&res2, 1);

    ck_assert_int_eq(result1, result2);
    ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
    ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);

    //printf("Test_4: \n");

    one = S21_DECIMAL_ZERO;
    two = S21_DECIMAL_ZERO;
    res1 = S21_DECIMAL_ZERO;
    res2 = S21_DECIMAL_ZERO;

    one.bits32[0] = 5;
    s21_set_sign(&one, 1);
    two.bits32[0] = 10;
    s21_set_sign(&two, 0);

    result1 = s21_sub(one, two, &res1);
    result2 = 0;

    res2.bits32[0] = 15;
    s21_set_sign(&res2, 1);

    ck_assert_int_eq(result1, result2);
    ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
    ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);

//    printf("Test_5: \n");

    one = S21_DECIMAL_ZERO;
    two = S21_DECIMAL_ZERO;
    res1 = S21_DECIMAL_ZERO;
    res2 = S21_DECIMAL_ZERO;

    one.bits32[0] = 5;
    s21_set_sign(&one, 0);
    two.bits32[0] = 10;
    s21_set_sign(&two, 1);

    result1 = s21_sub(one, two, &res1);
    result2 = 0;

    res2.bits32[0] = 15;
    s21_set_sign(&res2, 0);

    ck_assert_int_eq(result1, result2);
    ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
    ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);

    //printf("Test_6: \n");

    one = S21_DECIMAL_ZERO;
    two = S21_DECIMAL_ZERO;
    res1 = S21_DECIMAL_ZERO;
    res2 = S21_DECIMAL_ZERO;

    one.bits32[0] = 5;
    s21_set_sign(&one, 0);
    two.bits32[0] = 10;
    s21_set_sign(&two, 1);

    result1 = s21_sub(one, two, &res1);
    result2 = 0;

    res2.bits32[0] = 15;
    s21_set_sign(&res2, 0);

    ck_assert_int_eq(result1, result2);
    ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
    ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);

    //printf("Test_7: \n");

    one = S21_DECIMAL_ZERO;
    two = S21_DECIMAL_ZERO;
    res1 = S21_DECIMAL_ZERO;
    res2 = S21_DECIMAL_ZERO;

    one.bits32[0] = 10;
    s21_set_sign(&one, 1);
    two.bits32[0] = 5;
    s21_set_sign(&two, 1);

    result1 = s21_sub(one, two, &res1);
    result2 = 0;

    res2.bits32[0] = 5;
    s21_set_sign(&res2, 1);

    ck_assert_int_eq(result1, result2);
    ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
    ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);

    //printf("Test_8: \n");

    one = S21_DECIMAL_ZERO;
    two = S21_DECIMAL_ZERO;
    res1 = S21_DECIMAL_ZERO;
    res2 = S21_DECIMAL_ZERO;

    one.bits32[0] = 5;
    s21_set_sign(&one, 1);
    two.bits32[0] = 10;
    s21_set_sign(&two, 1);

    result1 = s21_sub(one, two, &res1);
    result2 = 0;

    res2.bits32[0] = 5;
    s21_set_sign(&res2, 0);

    ck_assert_int_eq(result1, result2);
    ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
    ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);

}

END_TEST


START_TEST(s21_from_float_to_decimal_1) {
    s21_decimal val;

    s21_from_float_to_decimal(0.03, &val);
    ck_assert_int_eq(val.bits[0], 3);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits8[14], 2);
    ck_assert_int_eq(val.bits8[15], 0);

    s21_from_float_to_decimal(127.1234, &val);
    ck_assert_int_eq(val.bits[0], 1271234);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits8[14], 4);
    ck_assert_int_eq(val.bits8[15], 0);
}

END_TEST
START_TEST(s21_from_float_to_decimal_2) {
    s21_decimal val;
    s21_from_float_to_decimal(-128.023, &val);
    ck_assert_int_eq(val.bits[0], 128023);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits8[15], 0x80);
    ck_assert_int_eq(val.bits8[14], 3);
}

END_TEST
START_TEST(s21_from_float_to_decimal_3) {
    s21_decimal val;
    s21_from_float_to_decimal(-2.1474836E+09, &val);
    ck_assert_int_eq(val.bits[0], -2147483648);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], -2147483648);
}

END_TEST
START_TEST(s21_from_float_to_decimal_4) {
    s21_decimal val;
    s21_from_float_to_decimal(22.14836E+03, &val);
    ck_assert_int_eq(val.bits[0], 2214836);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 131072);
}

END_TEST
START_TEST(s21_from_float_to_decimal_5) {
    s21_decimal val;
    s21_from_float_to_decimal(1.02E+09, &val);
    ck_assert_int_eq(val.bits[0], 1020000000);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], 0);
}

END_TEST
START_TEST(s21_from_float_to_decimal_6) {
    s21_decimal val;
    s21_from_float_to_decimal(-333.2222, &val);
    ck_assert_int_eq(val.bits[0], 3332222);
    ck_assert_int_eq(val.bits[1], 0);
    ck_assert_int_eq(val.bits[2], 0);
    ck_assert_int_eq(val.bits[3], -2147221504);
}

END_TEST

START_TEST(s21_negate_1) {
    s21_decimal res;
    s21_decimal val;

    val.bits8[15] = 0x80;
    val.bits8[14] = 2;
    val.bits8[0] = 5;

    s21_negate(val, &res);
    ck_assert_int_eq(res.bits8[15], 0);
    ck_assert_int_eq(res.bits8[14], 2);
    ck_assert_int_eq(res.bits8[0], 5);
}

START_TEST(s21_negate_2) {
    s21_decimal res;
    s21_decimal val;

    val.bits8[15] = 0;
    val.bits8[14] = 2;
    val.bits8[0] = 5;

    s21_negate(val, &res);
    ck_assert_int_eq(res.bits8[15], 0x80);
    ck_assert_int_eq(res.bits8[14], 2);
    ck_assert_int_eq(res.bits8[0], 5);
}

END_TEST

Suite *test_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("String test");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, s21_sub_test);

    tcase_add_test(tc_core, s21_from_float_to_decimal_1);
    tcase_add_test(tc_core, s21_from_float_to_decimal_2);
    tcase_add_test(tc_core, s21_from_float_to_decimal_3);
    tcase_add_test(tc_core, s21_from_float_to_decimal_4);
    tcase_add_test(tc_core, s21_from_float_to_decimal_5);
    tcase_add_test(tc_core, s21_from_float_to_decimal_6);

    tcase_add_test(tc_core, s21_negate_1);
    tcase_add_test(tc_core, s21_negate_2);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    Suite *s = test_suite();
    SRunner *runner = srunner_create(s);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);

    int nofailed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (nofailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
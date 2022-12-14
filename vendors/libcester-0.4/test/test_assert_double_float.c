/*!gcc -m32 {0} -I. -I../include/ -o out.exe; ./out.exe --cester-verbose */

#include <exotic/cester.h>
#include <stdint.h>

#ifndef __CESTER_STDC_VERSION__
    #define UNIT_TEST_LONG_DOUBLE double
    #define UNIT_TEST_ASSERT_LONG_DOUBLE(type) cester_assert_double_##type
    #define UNIT_TEST_CMP_LONG_DOUBLE cester_assert_cmp_double
#else
#if UINTPTR_MAX == 0xffffffff
    #define UNIT_TEST_LONG_DOUBLE double
    #define UNIT_TEST_ASSERT_LONG_DOUBLE(type) cester_assert_double_##type
    #define UNIT_TEST_CMP_LONG_DOUBLE cester_assert_cmp_double
#else /* UINTPTR_MAX == 0xffffffffffffffff*/
    #define UNIT_TEST_LONG_DOUBLE long double
    #define UNIT_TEST_ASSERT_LONG_DOUBLE(type) cester_assert_ldouble_##type
    #define UNIT_TEST_CMP_LONG_DOUBLE cester_assert_cmp_ldouble
#endif
#endif

CESTER_BODY(
typedef struct param_arg {
    float f;
    double d;
    UNIT_TEST_LONG_DOUBLE ld;
} Param;
)

CESTER_BEFORE_ALL(test_instance, 
    Param* param = (Param*) malloc(sizeof(Param));
    param->f = 121.898000f;
    param->d = 121.898000;
    param->ld = 12453541.8982340;
    test_instance->arg = param;
)

CESTER_TEST(test_assert_cmp_float, test_instance, 
    cester_assert_cmp_float(1.12, ==, 1.12, "%f %s %f");
    cester_assert_cmp_float(2.13, !=, 2.131, "%f %s %f");
)

CESTER_TEST(test_float_assertion, test_instance, 
    cester_assert_cmp_float(1.58, <, 2.12, "%f %s %f");
    cester_assert_cmp_float(31.12, >, 31.11, "%f %s %f");
)

CESTER_TEST(test_float_assertion_literal, test_instance, 
    float number = ((Param*)test_instance->arg)->f;
    cester_assert_float_eq(121.898f, number);
    cester_assert_float_ne(30.7676, number);
    cester_assert_float_gt(number, 10.31);
    cester_assert_float_ge(number, 121.0);
    cester_assert_float_lt(90.234, number);
    cester_assert_float_le(number, number);
)

CESTER_TEST(test_assert_cmp_double, test_instance, 
    cester_assert_cmp_double(1.12, ==, 1.12, "%lf %s %lf");
    cester_assert_cmp_double(2.13, !=, 2.131, "%lf %s %lf");
)

CESTER_TEST(test_double_assertion, test_instance, 
    cester_assert_cmp_double(1.58, <, 2.12, "%lf %s %lf");
    cester_assert_cmp_double(31.12, >, 31.11, "%lf %s %lf");
)

CESTER_TEST(test_double_assertion_literal, test_instance, 
    double number = ((Param*)test_instance->arg)->d;
    cester_assert_double_eq(121.898, number);
    cester_assert_double_ne(30.7676, number);
    cester_assert_double_gt(number, 10.31);
    cester_assert_double_ge(number, 121.0);
    cester_assert_double_lt(90.234, number);
    cester_assert_double_le(number, number);
)

CESTER_TEST(test_assert_cmp_long_double, test_instance, 
    UNIT_TEST_CMP_LONG_DOUBLE(1.12, ==, 1.12, "%e %s %e");
    UNIT_TEST_CMP_LONG_DOUBLE(2.13, !=, 2.131, "%e %s %e");
)

CESTER_TEST(test_long_double_assertion, test_instance, 
    UNIT_TEST_CMP_LONG_DOUBLE(133.545348, <, 3452.12353, "%e %s %e");
    UNIT_TEST_CMP_LONG_DOUBLE(343541.35312, >, 343351.345411, "%e %s %e");
)

CESTER_TEST(test_long_double_assertion_literal, test_instance, 
    UNIT_TEST_LONG_DOUBLE number = ((Param*)test_instance->arg)->ld;
    UNIT_TEST_ASSERT_LONG_DOUBLE(eq)(12453541.8982340, number);
    UNIT_TEST_ASSERT_LONG_DOUBLE(ne)(3234340.7424676, number);
    UNIT_TEST_ASSERT_LONG_DOUBLE(gt)(number, 1434320.334231);
    UNIT_TEST_ASSERT_LONG_DOUBLE(ge)(number, 1223431.01133);
    UNIT_TEST_ASSERT_LONG_DOUBLE(lt)(92340.2324324, number);
    UNIT_TEST_ASSERT_LONG_DOUBLE(le)(number, number);
)

CESTER_AFTER_ALL(test_instance,
    free(test_instance->arg);
)

CESTER_OPTIONS(
    CESTER_NO_ISOLATION();
)


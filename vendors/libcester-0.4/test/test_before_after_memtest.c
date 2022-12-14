/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>

CESTER_BODY(
typedef struct argumets {
    void *arg1;
    void *arg2;
} Args;
)

CESTER_BEFORE_ALL(inst,
    char *ba_str1 = (char *) malloc(1);
    char *ba_str2 = (char *) malloc(1);
    Args *args = (Args *) malloc(sizeof(Args));
    args->arg1 = ba_str2;
    inst->arg = args;
    
    free(ba_str1);
)

CESTER_BEFORE_EACH(inst, index, test_name,
    char *be_str1 = (char *) malloc(4);
    char *be_str2 = (char *) malloc(4);
    Args *args = (Args *) inst->arg;
    args->arg2 = be_str2;
    
    free(be_str1);
)

CESTER_TEST(test_assert_false, test_instance,
    cester_assert_nothing();
)

CESTER_TEST(test_number_2, test_instance,
    cester_assert_nothing();
)

CESTER_AFTER_EACH(inst, index, test_name,
    Args *args = (Args *) inst->arg;
    free(args->arg2);
)

CESTER_AFTER_ALL(inst,
    Args *args = (Args *) inst->arg;
    free(args->arg1);
    free(args);
)

CESTER_OPTIONS(
    char *co_str = (char *) malloc(3);
    free(co_str);
)

/*!gcc -DHAVE_CONFIG_H -I. -I.. -DUTC_OFFSET=+0000  -g -O2 -Wall -MD -Wpointer-arith -Wshadow -Wwrite-strings -Wcast-align -Wredundant-decls -Wdisabled-optimization -Wfloat-equal -Wmultichar -Wmissing-noreturn -Wstrict-null-sentinel -Woverloaded-virtual -Wsign-promo -Wno-deprecated-declarations -Wno-unknown-warning-option -funit-at-a-time -Weffc++ {0} -I. -I../include/ -o out; ./out */

#include <exotic/cester.h>

CESTER_BODY(

typedef struct a_struct {
    int index ;
    char* value;
} AStruct;

)

CESTER_TEST(definitely_crahses, test_instance,
    int *p = CESTER_NULL;
    *p=0xdead;
)

CESTER_TEST(segfault_test_null_ptr, test_instance,
    int *p = CESTER_NULL;
    AStruct* arg_value ;
    cester_assert_equal(arg_value->value, CESTER_NULL);
    cester_assert_equal(arg_value->value[21], '~');
    *p=0xdead;
)

CESTER_TEST(no_segfault, test_instance,
    int *p = CESTER_NULL;
    AStruct* arg_value = (AStruct*) malloc(sizeof(AStruct));
    arg_value->index = 20;
    cester_assert_equal(arg_value, CESTER_NULL);
    free(arg_value);
    *p=0xdead;
)

CESTER_TEST(this_should_notbe_affected, test_instance,
    cester_assert_equal(CESTER_NULL, CESTER_NULL);
)

CESTER_TEST(this_aftermath, test_instance,
    cester_assert_equal(1, 1);
)

CESTER_OPTIONS(
    CESTER_TEST_SHOULD_SEGFAULT(definitely_crahses);
    CESTER_TEST_SHOULD_SEGFAULT(segfault_test_null_ptr);
    CESTER_TEST_SHOULD_FAIL(no_segfault);
)

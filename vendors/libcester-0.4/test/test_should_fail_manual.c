/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out*/

#define CESTER_NO_MAIN
#include <exotic/cester.h>

CESTER_TEST(this_should_segfault, test_instance,
    int *p = CESTER_NULL;
    cester_assert_char_eq(((char*)test_instance->arg)[12], ((char*)test_instance->arg)[2109]);
    *p=0xdead;
)

CESTER_TEST(this_should_fail, test_instance,
   cester_assert_not_equal(CESTER_NULL, ((void*)0));
)

CESTER_TEST(this_should_pass, test_instance,
   cester_assert_equal(CESTER_NULL, ((void*)0));
)

CESTER_TEST(this_should_segfault_also_fail, test_instance,
   cester_assert_char_eq(((char*)test_instance->arg)[12], ((char*)test_instance->arg)[2109]);
)

CESTER_TEST(this_should_leak_memory, test_instance,
   char* str = (char*) malloc(sizeof(char) * 12);
)

CESTER_OPTIONS(
    CESTER_TEST_SHOULD_SEGFAULT(this_should_segfault);
    CESTER_TEST_SHOULD_FAIL(this_should_fail);
    CESTER_TEST_SHOULD_FAIL(this_should_segfault_also_fail);
    CESTER_TEST_SHOULD_LEAK_MEMORY(this_should_leak_memory);
)

CESTER_BODY(
int main(int argc, char** argv) {
    CESTER_REGISTER_TEST(this_should_segfault);
    CESTER_REGISTER_TEST(this_should_fail);
    CESTER_REGISTER_TEST(this_should_pass);
    CESTER_REGISTER_TEST(this_should_segfault_also_fail);
    CESTER_REGISTER_TEST(this_should_leak_memory);
    return CESTER_RUN_ALL_TESTS(argc, argv);
}
)

/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose */
#define __BASE_FILE__ "C:\\Users\\anton\\DEV\\Games-Engine\\src\\breakout_game_test.impl.cpp"
#include <iostream>
#include <breakout_engine.hpp>
#include <exotic/cester.h>


CESTER_TEST(rect_test, test_instance, 
    
    Rect rect = Rect(glm::vec2(0.0f, 0.0f), glm::vec2(128.0f, 128.0f));
    cester_assert_equal(rect.topLeft(), glm::vec2(0.0f, 0.0f));
    cester_assert_equal(rect.topRight(), glm::vec2(128.0f, 0.0f));
    cester_assert_equal(rect.bottomLeft(), glm::vec2(0.0f, 128.0f));
    cester_assert_equal(rect.bottomRight(), glm::vec2(128.0f, 128.0f));
    std::cout << toString(rect) << std::endl;


)


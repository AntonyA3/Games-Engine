#define __BASE_FILE__ "C:/Users/anton/DEV/Games-Engine/tests/Unit/sdl_window_wrapper.test.cpp"
#define SDL_MAIN_HANDLED
#include <exotic/cester.h>
#include <sdl_window_wrapper.hpp>

CESTER_TEST(the_active_then_termination, inst,
    SDLWindowWrapper window_wrapper;
    cester_assert_false(window_wrapper.isActive());
    window_wrapper.create();
    cester_assert_true(window_wrapper.isActive());
    window_wrapper.terminate();
    cester_assert_false(window_wrapper.isActive());
)

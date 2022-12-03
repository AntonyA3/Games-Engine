#ifndef GAMES_ENGINE_COMPLETE_WINDOW_DATA
#define GAMES_ENGINE_COMPLETE_WINDOW_DATA
#include <sdl_window_data.hpp>
#include <sdl_gl_context_data.hpp>
struct CompleteWindowData
{
    SDLWindowData sdl_window_data;
    SDLGLContextData sdl_gl_context_data;
};
#endif
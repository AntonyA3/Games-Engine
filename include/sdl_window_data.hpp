#ifndef GAMES_ENGINE_SDL_WINDOW_DATA_HPP
#define GAMES_ENGINE_SDL_WINDOW_DATA_HPP

#include <SDL2/SDL.h>
#include <string>
struct SDLWindowData
{
    Uint32 init_flags;
    std::string title;
    int width,
    height,
    x_position_flag,
    y_position_flag;

    bool window_shown, open_gl_active;
    SDL_bool resizable;

};
#endif
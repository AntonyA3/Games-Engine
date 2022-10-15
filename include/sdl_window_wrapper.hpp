
#ifndef GAMES_ENGINE_SDL_WINDOW_WRAPPER_HPP
#define GAMES_ENGINE_SDL_WINDOW_WRAPPER_HPP

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>
#include <string>
#include <sdl_event_wrapper.hpp>
#include <sdl_gl_context_wrapper.hpp>
#include<dear_imgui_wrapper.hpp>
#include<GL/glew.h>

struct SDLWindowWrapper
{
    SDL_Window * m_window;
    bool m_active;
    Uint32 m_init_flags;
    std::string m_title;
    int m_width,
    m_height,
    m_initial_width,
    m_initial_height,
    m_x_position_flag,
    m_y_position_flag,
    m_other_flags;
    SDL_bool m_resizable;

public:
    SDLWindowWrapper();
    ~SDLWindowWrapper();
    void create();
    void setDimensions(int width, int height);
    int getWidth();
    int getHeight();
    void terminate();
    void destroy();
    bool isActive();
    SDL_Window *& getWindow();
};

#endif
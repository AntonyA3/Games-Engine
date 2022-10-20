
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
#include <sdl_window_data.hpp>
struct SDLWindowWrapper
{
    SDL_Window * m_window;
    bool m_active;
    int m_width,
    m_height;

public:
    SDLWindowWrapper();
    ~SDLWindowWrapper();
    void create(SDLWindowData& sdl_window_data);
    void terminate();
    void destroy();
    bool isActive();
    SDL_Window *& getWindow();
};

#endif
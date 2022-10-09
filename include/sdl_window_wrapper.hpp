
#ifndef GAMES_ENGINE_SDL_WINDOW_WRAPPER_HPP
#define GAMES_ENGINE_SDL_WINDOW_WRAPPER_HPP

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>
#include <string>
#include <sdl_event_wrapper.hpp>
#include <sdl_gl_context_wrapper.hpp>
#include<GL/glew.h>
class SDLWindowWrapper
{
private:
    SDL_Window * m_window;
    SDLEventWrapper m_sdl_event_wrapper;
    SDLGLContextWrapper m_sdl_gl_context_wrapper;
    bool m_active;
    Uint32 m_init_flags;
    std::string m_title;
    int m_width;
    int m_height;
    int m_x_position_flag;
    int m_y_position_flag;
    int m_other_flags;
    SDL_bool m_resizable;
    struct{
        float r = 0.5f, g = 0.5f, b = 0.5f, a = 1.0f;
    } m_color;

public:
    SDLWindowWrapper();
    ~SDLWindowWrapper();
    void create();
    void clear();
    void swap();
    void setDimensions(int width, int height);
    void setColor(float r ,float g, float b, float a);
    void terminate();
    void destroyAndQuit();
    bool isActive();
    bool polledEvent();
    SDL_Event& nextEvent();
};

#endif
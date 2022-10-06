
#ifndef GAMES_ENGINE_SDL_WINDOW_WRAPPER
#define GAMES_ENGINE_SDL_WINDOW_WRAPPER

#include <SDL2/SDL.h>
#include <string>
#include <sdl_event_wrapper.hpp>
class SDLWindowWrapper
{
private:
    SDL_Window * m_window;
    SDLEventWrapper m_sdl_event_wrapper;
    bool m_active;
    Uint32 m_init_flags;
    std::string m_title;
    int m_width;
    int m_height;
    int m_x_position_flag;
    int m_y_position_flag;
    SDL_bool m_resizable;
public:
    SDLWindowWrapper();
    ~SDLWindowWrapper();
    void create();
    void terminate();
    void destroyAndQuit();
    bool isActive();
    bool polledEvent();
    SDL_Event& nextEvent();
};
#endif
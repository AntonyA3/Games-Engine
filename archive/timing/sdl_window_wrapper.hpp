
#ifndef GAMES_ENGINE_SDL_WINDOW_WRAPPER_HPP
#define GAMES_ENGINE_SDL_WINDOW_WRAPPER_HPP

#include <SDL2/SDL.h>
#include <string>
#include <sdl_event_wrapper.hpp>
#include <sdl_gl_context_wrapper.hpp>
#include<dear_imgui_wrapper.hpp>
#include<GL/glew.h>
#include <sdl_window_data.hpp>
#include <macros/debug_logger.hpp>

/*
    An abstraction to encapsulate the initial properties related  
    to an SDL window and the continuous properties related to an 
    SDL_Window
   
*/
struct SDLWindowWrapper
{
    SDL_Window * m_window; // An **allocated reference** to the SDLWindow object that created, **on creation**
    bool m_active; // To store whether the window is **currently** active
    int m_width, // To store the **current** width of the window 
    m_height; //  To store the **current**  height of the Window

public:
    SDLWindowWrapper();
    ~SDLWindowWrapper();
    /*
        Given the properties of **this**
        And **this** window property is null
        **initilise** window
        **set** window to resizable
        Then **this** window should not be null
        And **this** window should be visible on the *screen*
    */
    void create(SDLWindowData& sdl_window_data);
    void terminate(); // Set **this** to inactive
    void destroy(); // Destroy **this** window 
    bool isActive(); // Return whether **this** is active
    SDL_Window *& getWindow();
};

#endif
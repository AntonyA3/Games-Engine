#ifndef GAMES_ENGINE_SDL_GL_CONTEXT_WRAPPER_HPP
#define GAMES_ENGINE_SDL_GL_CONTEXT_WRAPPER_HPP

#include <SDL2/SDL.h> // The opengl context from SDL2
#include <iostream>
#include <GL/glew.h>
#include <sdl_gl_context_data.hpp>
#include <macros/debug_logger.hpp>

// An abstraction to store the SDLGLContext and it's initial properties
struct SDLGLContextWrapper
{
    SDL_GLContext m_gl_context; //Stores The opengl context for SDL
    
    SDLGLContextWrapper();
    ~SDLGLContextWrapper();
    /*
        Given the properties of **this**
        And a **pointer** to an SDL_Window
        Set the opengl version of the window 
        Initialise the SDLGL_Context
        And Initialise the SDLRenderer
        GetOpenGL Functions with GLEW
        Return a **reference** to the SDLGLContext
    */
    void create(SDL_Window * window, SDLGLContextData& gl_context_data); // Creates the GL context for an SDL Window given Open gl version data
    SDL_GLContext& getGLContext(); //  Gets the reference to the glContext
};
#endif
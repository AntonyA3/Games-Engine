#ifndef GAMES_ENGINE_SDL_GL_CONTEXT_WRAPPER_HPP
#define GAMES_ENGINE_SDL_GL_CONTEXT_WRAPPER_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <GL/glew.h>
#include <sdl_gl_context_data.hpp>

struct SDLGLContextWrapper
{
    SDL_GLContext m_gl_context;
    
    SDLGLContextWrapper();
    ~SDLGLContextWrapper();
    void create(SDL_Window * window, SDLGLContextData& gl_context_data);
    SDL_GLContext& getGLContext();
};
#endif
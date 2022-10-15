#ifndef GAMES_ENGINE_SDL_GL_CONTEXT_WRAPPER_HPP
#define GAMES_ENGINE_SDL_GL_CONTEXT_WRAPPER_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <GL/glew.h>

struct SDLGLContextWrapper
{
    int m_gl_major_version;
    int m_gl_minor_version;
    SDL_GLContext m_gl_context;
    SDL_Renderer * m_renderer;
    
    SDLGLContextWrapper();
    ~SDLGLContextWrapper();
    void create(SDL_Window * window, int gl_major_version, int gl_minor_version);
    SDL_GLContext& getGLContext();
};
#endif
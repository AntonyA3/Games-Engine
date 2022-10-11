#ifndef GAMES_ENGINE_SDL_GL_CONTEXT_WRAPPER_HPP
#define GAMES_ENGINE_SDL_GL_CONTEXT_WRAPPER_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <GL/glew.h>

class SDLGLContextWrapper
{
private:
    int m_gl_major_version;
    int m_gl_minor_version;
    SDL_GLContext m_gl_context;
    SDL_Renderer * m_renderer;

    
    
public:
    SDLGLContextWrapper();
    ~SDLGLContextWrapper();
    void create(SDL_Window * window);
    SDL_GLContext& getGLContext(){
        return m_gl_context;
    }
};
#endif

#include <sdl_gl_context_wrapper.hpp>

SDLGLContextWrapper::SDLGLContextWrapper()
{   
    this->m_gl_major_version = 3;
    this->m_gl_minor_version = 3;
    this->m_renderer = NULL;
}

void SDLGLContextWrapper::create(SDL_Window * window, int gl_major_version, int gl_minor_version){
    m_gl_major_version = gl_major_version;
    m_gl_minor_version = gl_minor_version;
    if (m_gl_major_version > 3 || (m_gl_major_version == 3 && m_gl_minor_version >= 3))
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, m_gl_major_version); // GL version is a property
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, m_gl_minor_version); // GL minor version us a property
    
    m_gl_context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);

    m_renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_GL_MakeCurrent(window, m_gl_context);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(1);
    }
}

SDL_GLContext& SDLGLContextWrapper::getGLContext(){
    return m_gl_context;
}

SDLGLContextWrapper::~SDLGLContextWrapper()
{
}



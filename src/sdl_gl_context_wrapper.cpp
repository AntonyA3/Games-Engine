
#include <sdl_gl_context_wrapper.hpp>

SDLGLContextWrapper::SDLGLContextWrapper()
{   
}

void SDLGLContextWrapper::create(SDL_Window * window, SDLGLContextData& gl_context_data){
    if (gl_context_data.gl_major_version > 3 || (gl_context_data.gl_major_version == 3 && gl_context_data.gl_minor_version >= 3))
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_context_data.gl_major_version); // GL version is a property
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_context_data.gl_minor_version); // GL minor version us a property
    
    m_gl_context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);
    
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(1);
    }
    SDL_GL_MakeCurrent(window, m_gl_context);
}

SDL_GLContext& SDLGLContextWrapper::getGLContext(){
    return m_gl_context;
}

SDLGLContextWrapper::~SDLGLContextWrapper()
{
}



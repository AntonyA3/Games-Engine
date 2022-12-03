#ifndef GAMES_ENGINE_SDL_GL_CONTEXT_DATA
#define GAMES_ENGINE_SDL_GL_CONTEXT_DATA
// A class that stores the data for setting up an SDL GL Context
struct SDLGLContextData
{
    int gl_minor_version, // The opengl minor version to use
    gl_major_version; // The opengl major version to use
};
#endif
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

/* Thes Object should not be used in the application
However is  useful for creating an SDL application that will
be useful for testing whether the Input is functioning correctly,
However this does not create any video */
struct BasicSDLTest
{
    SDL_Window * window;
    int width, height;

    void initialise();
    void update(bool& active);

};

struct BasicSDLOpenGLTest
{
    SDL_Window * window; // An **allocated reference** to the SDLWindow object that created, **on creation**
    SDL_GLContext gl_context; // To Store the SDL GLContext
    int opengl_major_version = 3, // To store the open gl major version
    opengl_minor_version = 3,
    width = 640, // this value id the current window width, it is initialised to the default
    height = 480; // this value id the current window height, it is initialised to the default; // To store the open gl minor version
    std::string window_name = "Test"; // The Window Name Which is initially set the breakout Game


    void initialise();
    void cleanup();

};

struct TimeTicker{
    Uint64 current_time, tick_time, 
    accumulated_time;// This variable is designed to reset every tick which marks a tick
    TimeTicker(Uint64 tick_time, Uint64 current_time);
    bool tick();
    void addTime(Uint64 new_time);
};

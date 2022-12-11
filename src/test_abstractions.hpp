#include <string>
#include <SDL2/SDL.h>
/* This Object should not be used in the application
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

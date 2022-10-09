#include <stdio.h>
#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <sdl_window_wrapper.hpp>
int main(int argc, char const *argv[])
{
    SDLWindowWrapper sdl_window;
    sdl_window.create();
    while (sdl_window.isActive())
    {
        while (sdl_window.polledEvent())
        {
            SDL_Event& event = sdl_window.nextEvent();
            switch (event.type)
            {
            case SDL_QUIT:
                SDL_Log("Program quit after %i ticks", event.quit.timestamp);
                sdl_window.terminate();
                break;
            
            default:
                break;
            }
        }

        sdl_window.clear();
        sdl_window.swap();
        
    }

    sdl_window.destroyAndQuit();
    return 0;
}

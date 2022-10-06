#include <stdio.h>
#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char const *argv[])
{
    SDL_Window* window = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    
    //Create window
    window = SDL_CreateWindow( "Hello SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    SDL_SetWindowResizable(window, SDL_TRUE);
    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    
    bool active = true;
    while(active){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch (event.type)
            {
            case SDL_QUIT:
                SDL_Log("Program quit after %i ticks", event.quit.timestamp);
                active = false;
                break;
            
            default:
                break;
            }

        }
    }

    SDL_DestroyWindow( window );
    //Quit SDL subsystems
    SDL_Quit();


    return 0;
}

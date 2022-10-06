#ifndef GAMES_ENGINE_SDL_EVENT_WRAPPER
#define GAMES_ENGINE_SDL_EVENT_WRAPPER

#include <SDL2/SDL.h>
#include <string>
class SDLEventWrapper
{
private:
    SDL_Event m_event;
public:
    SDLEventWrapper();
    ~SDLEventWrapper();
    bool polledEvent();
    SDL_Event& nextEvent();

};



#endif
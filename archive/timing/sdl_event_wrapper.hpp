#ifndef GAMES_ENGINE_SDL_EVENT_WRAPPER_HPP
#define GAMES_ENGINE_SDL_EVENT_WRAPPER_HPP

#include <SDL2/SDL.h>
#include <string>
// A short summary
class SDLEventWrapper
{
private:
    SDL_Event m_event; // Stores the most recent SDL_Event
public:
    SDLEventWrapper();
    ~SDLEventWrapper();
    bool polledEvent(); // Sets the polled event And Returns true if ther are any remaining events
    SDL_Event& nextEvent(); // Returns **this** event *the most recently polled event*

};
#endif
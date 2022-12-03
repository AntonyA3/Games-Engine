#include <sdl_event_wrapper.hpp>

SDLEventWrapper::SDLEventWrapper()
{
}


SDLEventWrapper::~SDLEventWrapper()
{
}

bool SDLEventWrapper::polledEvent(){
   return SDL_PollEvent(&m_event); 
}
SDL_Event& SDLEventWrapper::nextEvent(){
    return m_event;
}

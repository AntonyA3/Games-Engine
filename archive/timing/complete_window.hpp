#ifndef GAMES_ENGINE_COMPLETE_WINDOW
#define GAMES_ENGINE_COMPLETE_WINDOW
#include <sdl_window_wrapper.hpp>
#include <sdl_gl_context_wrapper.hpp>
#include <dear_imgui_wrapper.hpp>
#include <complete_window_data.hpp> // The data required to create the SDL Window and the data required to create the sub components
#include <sdl_event_wrapper.hpp>
/*
    This encapsulates everything that is associated to creating
    and running and SDLWindow with OpenGl and DearImgui
*/
struct CompleteWindow
{    
    SDLWindowWrapper m_sdl_window_wrapper; // Encapsulates the SDL_Window 
    SDLGLContextWrapper m_sdl_gl_context_wrapper; //  Encapsulates the GL_Context_Wrapper
    DearImGuiWrapper m_dear_imgui_wrapper; // Encapsulates the imgui context    
    SDLEventWrapper m_sdl_event_wrapper; // Encapsulates the sdl_event_wrapper

    void create(CompleteWindowData& complete_window_data); // delegates creating a complete window, to creating the sub components of the window
    bool polledEvent(); //  delegates polling to the SDLEventWrapper
    bool isActive();
    SDL_Event& nextEvent(); // delegates getting the next event to SDLEventWrapper
    void beginFrame();
    void renderFrame();
};
#endif
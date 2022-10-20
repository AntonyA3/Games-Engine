#ifndef COMPLETE_WINDOW
#define COMPLETE_WINDOW
#include <sdl_window_wrapper.hpp>
#include <sdl_gl_context_wrapper.hpp>
#include <dear_imgui_wrapper.hpp>
#include <complete_window_data.hpp>
#include <sdl_event_wrapper.hpp>
struct CompleteWindow
{    
    SDLWindowWrapper m_sdl_window_wrapper;
    SDLGLContextWrapper m_sdl_gl_context_wrapper;
    DearImGuiWrapper m_dear_imgui_wrapper;
    SDLEventWrapper m_sdl_event_wrapper;

    void create(CompleteWindowData& complete_window_data);
    bool polledEvent();
    SDL_Event& nextEvent();
};
#endif
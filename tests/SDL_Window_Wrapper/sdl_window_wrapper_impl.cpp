#include <stdio.h>
#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <sdl_window_wrapper.hpp>
#include <sdl_gl_context_wrapper.hpp>
#include <dear_imgui_demo_window.hpp>
int main(int argc, char const *argv[])
{
    SDLWindowWrapper sdl_window;
    SDLGLContextWrapper sdl_gl_context;
    DearImGuiWrapper imgui_wrapper;
    DearImGuiDemoWindow demo_window;
    
    sdl_window.create();
    sdl_gl_context.create(sdl_window.getWindow());
    glViewport(0, 0, sdl_window.getWidth(),sdl_window.getHeight());
    glClearColor(sdl_window.m_color.r, sdl_window.m_color.g, sdl_window.m_color.b, sdl_window.m_color.a);
    imgui_wrapper.create(sdl_window.getWindow(), sdl_gl_context.getGLContext());
    while (sdl_window.isActive())
    {
        while (sdl_window.polledEvent())
        {
            SDL_Event& event = sdl_window.nextEvent();
            imgui_wrapper.processEvent(event);
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

        imgui_wrapper.beginFrame();
        demo_window.show();
        imgui_wrapper.renderFrame();
        SDL_GL_SwapWindow(sdl_window.getWindow());
        
    }

    sdl_window.destroyAndQuit();
    return 0;
}

#ifndef GAMES_ENGINE_DEAR_IMGUI_WRAPPER
#define GAMES_ENGINE_DEAR_IMGUI_WRAPPER
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_sdl.h>
#include <SDL2/SDL.h>

#include <macros/debug_logger.hpp>
struct DearImGuiWrapper
    
{
    ImGuiIO * m_io; //  A reference to Imgui's io


    DearImGuiWrapper();
    ~DearImGuiWrapper();
    /*
        Given a **pointer** to an SDL_Window <br> And a **reference** to a gl_context
        Create Imgui context
        Set ImGui io property
        Set Color Theme to default
        Use ImGui for SDL and OpenGL
        Then Initialise ImGui with shader version 150
    */
    void create(SDL_Window * window, SDL_GLContext& gl_context);
    /*
        Given an SDL_Event
        Return the boolean results of delegating the SDL_Event for ImGui to process
    */
    bool processEvent(SDL_Event& event);
    /*
        Given **this** object has access to Imgui <br> Create a new Imgui(Gui) Frame For OpenGL3
        And Create a new ImGui (Gui) Frame for SDL2
        And create a new Imgui (Gui) frame for OpenGl
        An Register a Imgui new frame 
    */
    void beginFrame();
    /*
        Given **this** object has access to Imgui through **headers**
        Prepare ImGui for rendering
        And use opengl3 to render OpenGl3
    */
    void renderFrame(); 
    
};
#endif

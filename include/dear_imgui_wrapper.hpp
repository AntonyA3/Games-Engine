#ifndef GAMES_ENGINE_DEAR_IMGUI_WRAPPER
#define GAMES_ENGINE_DEAR_IMGUI_WRAPPER
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_sdl.h>
#include <SDL2/SDL.h>
class DearImGuiWrapper
    
{
private:
    ImGuiIO * m_io;

public:
    DearImGuiWrapper();
    ~DearImGuiWrapper();
    void create(SDL_Window * window, SDL_GLContext& gl_context);
    bool processEvent(SDL_Event& event);
    void beginFrame();
    void renderFrame(); 
    
};
#endif

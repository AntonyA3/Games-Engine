#ifndef GAMES_ENGINE_DEAR_IMGUI_DEMO_WINDOW
#define GAMES_ENGINE_DEAR_IMGUI_DEMO_WINDOW
#include <imgui/imgui.h>
class DearImGuiDemoWindow
{
private:
    bool m_active; //Stores whether the ImGui demo window is active
public:
    DearImGuiDemoWindow();
    ~DearImGuiDemoWindow();
    void show(); // Given Access to imgui **headers** Then Displays the ImGui window if it is **this** is active 
};
#endif
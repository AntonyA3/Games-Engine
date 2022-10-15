#ifndef GAMES_ENGINE_DEAR_IMGUI_DEMO_WINDOW
#define GAMES_ENGINE_DEAR_IMGUI_DEMO_WINDOW
#include <imgui/imgui.h>
class DearImGuiDemoWindow
{
private:
    bool m_active;
public:
    DearImGuiDemoWindow();
    ~DearImGuiDemoWindow();
    void show();
};
#endif
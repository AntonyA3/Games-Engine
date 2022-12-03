#include <dear_imgui_demo_window.hpp>

DearImGuiDemoWindow::DearImGuiDemoWindow(/* args */)
{
    m_active = true;
}

void DearImGuiDemoWindow::show(){
    ImGui::ShowDemoWindow(&m_active);
}

DearImGuiDemoWindow::~DearImGuiDemoWindow()
{
}

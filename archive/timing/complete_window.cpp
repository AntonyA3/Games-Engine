#include <complete_window.hpp>


void CompleteWindow::create(CompleteWindowData& complete_window_data){
    m_sdl_window_wrapper.create(complete_window_data.sdl_window_data);
    m_sdl_gl_context_wrapper.create(m_sdl_window_wrapper.getWindow(), complete_window_data.sdl_gl_context_data);
    m_dear_imgui_wrapper.create(m_sdl_window_wrapper.getWindow(), m_sdl_gl_context_wrapper.getGLContext());    
}

bool CompleteWindow::polledEvent(){
    return m_sdl_event_wrapper.polledEvent();
}

bool CompleteWindow::isActive(){
    return m_sdl_window_wrapper.isActive();
}

void CompleteWindow::beginFrame(){
    m_dear_imgui_wrapper.beginFrame();
}

void CompleteWindow::renderFrame(){
    m_dear_imgui_wrapper.renderFrame();
}
SDL_Event& CompleteWindow::nextEvent(){
    SDL_Event& event = m_sdl_event_wrapper.nextEvent();
    m_dear_imgui_wrapper.processEvent(event);
    return event;
}


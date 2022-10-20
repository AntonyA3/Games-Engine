#include <complete_window.hpp>


void CompleteWindow::create(CompleteWindowData& complete_window_data){
    m_sdl_window_wrapper.create(complete_window_data.sdl_window_data);
    m_sdl_gl_context_wrapper.create(m_sdl_window_wrapper.getWindow(), complete_window_data.sdl_gl_context_data);
    m_dear_imgui_wrapper.create(m_sdl_window_wrapper.getWindow(), m_sdl_gl_context_wrapper.getGLContext());    
}

bool CompleteWindow::polledEvent(){
    return m_sdl_event_wrapper.polledEvent();
}

SDL_Event& CompleteWindow::nextEvent(){
    return m_sdl_event_wrapper.nextEvent();
}


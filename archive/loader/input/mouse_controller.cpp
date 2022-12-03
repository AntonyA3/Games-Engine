#include <input/mouse_controller.hpp>


MouseCursor& MouseController::mouseCursor(){
    return m_mouse_cursor;
}

MouseButton& MouseController::leftButton(){
    return m_left_button;
}

MouseButton& MouseController::rightButton(){
    return m_right_button;
}


void MouseController::create(){
    m_mouse_cursor.create();
    m_left_button.create();
    m_right_button.create();
}

void MouseController::update(){
    int x, y;
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    m_left_button.update((buttons & SDL_BUTTON_LMASK) != 0);
    m_right_button.update((buttons & SDL_BUTTON_RMASK) != 0);
    m_mouse_cursor.update((float)x, (float)y);
}
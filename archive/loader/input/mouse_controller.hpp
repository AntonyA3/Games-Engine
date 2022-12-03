#ifndef GAMES_ENGINE_MOUSE_CONTROLLER
#define GAMES_ENGINE_MOUSE_CONTROLLER
#include "mouse_cursor.hpp"
#include "mouse_button.hpp"
#include <iostream>
class MouseController
{
private:
    MouseCursor m_mouse_cursor;
    MouseButton m_left_button;
    MouseButton m_right_button;
public:

    MouseCursor& mouseCursor();
    MouseButton& leftButton();
    MouseButton& rightButton();
    void create();
    void update();

};
#endif
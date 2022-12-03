#include <input/button.hpp>

void Button::create(){
    m_state = ButtonState_Up;
}

void Button::update(bool down){
    if(down){
        switch (m_state)
        {
        case ButtonState_Pressed:
        case ButtonState_Down:
            m_state = ButtonState_Down;
            break;
        case ButtonState_Released:
        case ButtonState_Up:
            m_state = ButtonState_Pressed;
            break;
    }
    }else{ // not down
        switch (m_state)
        {
        case ButtonState_Pressed:
        case ButtonState_Down:
            m_state = ButtonState_Released;
            break;
        case ButtonState_Released:
        case ButtonState_Up:
            m_state = ButtonState_Up;
            break;
        }
    }
}

bool Button::isPressedOrDown(){

    return (m_state == ButtonState_Pressed) || (m_state == ButtonState_Down);
}

bool Button::isPressed(){
    return m_state == ButtonState_Pressed;
}

bool Button::isReleased(){
    return m_state == ButtonState_Released;
}

bool Button::isReleasedOrUp(){
    return (m_state == ButtonState_Released) || (m_state == ButtonState_Up);
}

bool Button::isDown(){
    return m_state == ButtonState_Down;
}

bool Button::isUp(){
    return m_state == ButtonState_Up;
}

ButtonState Button::getState(){
    return m_state;
}
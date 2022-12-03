#ifndef GAMES_ENGINE_BUTTON
#define GAMES_ENGINE_BUTTON
#include "button_state.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <i_game_button.hpp>
struct Button :public IGameButton
{
    ButtonState m_state;
    void create();
    void update(bool down);
    bool isPressedOrDown();
    bool isPressed();
    bool isDown();
    bool isReleased();
    bool isUp();
    bool isReleasedOrUp();
    ButtonState getState();
};

#endif
#ifndef GAMES_ENGINE_I_GAME_BUTTON
#define GAMES_ENGINE_I_GAME_BUTTON
#include <input/button_state.hpp>
struct IGameButton
{
    virtual void create() = 0;
    virtual void update(bool down) = 0;
    virtual bool isPressedOrDown() = 0;
    virtual bool isPressed() = 0;
    virtual bool isDown() = 0;
    virtual bool isReleased() = 0;
    virtual bool isUp() = 0;
    virtual bool isReleasedOrUp() = 0;
    virtual ButtonState getState() = 0;

};
#endif

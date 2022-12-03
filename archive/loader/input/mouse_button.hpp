#ifndef GAMES_ENGINE_MOUSE_BUTTON
#define GAMES_ENGINE_MOUSE_BUTTON
#include <SDL2/SDL.h>
#include "button_state.hpp"
#include "button.hpp"
class MouseButton : public Button
{
private:
    
public:
    void create();
    void update(bool isDown);
  
};
#endif
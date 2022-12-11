#include <breakout_engine.hpp>
#include <SDL2/SDL.h>

int main(int argc, char const *argv[])
{    
   
    Button test_button = Button(SDL_SCANCODE_A, std::string("Test Button"));
    const Uint8 * keyboard_states = SDL_GetKeyboardState(NULL); // Points to the keyboard state

    while (true)
    {
        bool down = keyboard_states[test_button.scancode];
        updateButton(test_button, keyboard_states);
        SDL_Delay(0.016);

    }
   
    return 0;
}

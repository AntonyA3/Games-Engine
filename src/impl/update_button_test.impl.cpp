#include <breakout_engine.hpp>
#include <test_abstractions.hpp>
#include <SDL2/SDL.h>

int main(int argc, char const *argv[])
{    
    bool active = true;

    BasicSDLTest test_dependancy;
    test_dependancy.initialise();
   
    Button test_button = Button(SDL_SCANCODE_A, std::string("Test Button"));
    const Uint8 * keyboard_states = SDL_GetKeyboardState(NULL); // Points to the keyboard state

    Uint64 accumulated_time , // This variable is designed to reset every second which marks a tick
    current_time;
    Uint64 tick_time = 2000;
    current_time = SDL_GetTicks64();// Get the initial current time
    while (active)
    {
        test_dependancy.update(active); 
        if(accumulated_time >= tick_time){
            accumulated_time -= tick_time;
            update(test_button, keyboard_states);
            std::cout << "=========Next State========" << std::endl;
            std::cout << toString(test_button) << std::endl;

        }

        Uint64 new_time = SDL_GetTicks64();
        Uint64 delta_time = new_time - current_time;
        accumulated_time += delta_time;
        current_time = new_time;
    }
   
    return 0;
}

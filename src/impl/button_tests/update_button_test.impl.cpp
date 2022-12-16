#include <breakout_engine.hpp>
#include <SDL2/SDL.h>


int main(int argc, char const *argv[])
{    
    bool active = true;

    BasicSDLApplicationLoopTest test_dependancy;
    test_dependancy.initialise();
   
    Button test_button = Button(SDL_SCANCODE_A, std::string("Test Button"));
    const Uint8 * keyboard_states = SDL_GetKeyboardState(NULL); // Points to the keyboard state
    TimeTicker time_ticker = TimeTicker(2000, SDL_GetTicks64()); // Get the initialize with initial current time
    while (active)
    {
        test_dependancy.update(active); 

        if(time_ticker.tick()){
            update(test_button, keyboard_states);
            std::cout << "=========Next State========" << std::endl;
            std::cout << toString(test_button) << std::endl;

        }
        time_ticker.addTime(SDL_GetTicks64());

    }
    test_dependancy.cleanup();
    return 0;
}

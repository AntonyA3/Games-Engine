#include <breakout_engine.hpp>
#include <test_abstractions.hpp>
#include <SDL2/SDL.h>

int main(int argc, char const *argv[])
{
   bool active = true;

    BasicSDLTest test_dependancy;
    test_dependancy.initialise();
    
    Cursor test_cursor = Cursor();
    TimeTicker time_ticker = TimeTicker(2000, SDL_GetTicks64()); // Get the initialize with initial current time
    while (active)
    {
        test_dependancy.update(active); 

        if(time_ticker.tick()){
            update(test_cursor);
            std::cout << "=========Next State========" << std::endl;
            std::cout << toString(test_cursor) << std::endl;
        }
        time_ticker.addTime(SDL_GetTicks64());

    }
   
    return 0;
}

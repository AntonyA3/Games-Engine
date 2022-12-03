#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <iostream>
#include <limits>
#include <timing/time_controller.hpp>

void intro(){
    std::cout << "////////////////////////////////////////////////////" << std::endl;
    std::cout << "//////////Expect Positive Delta time values/////////" << std::endl;
    std::cout << "/////And the ability to handle 64 bit numbers//////" << std::endl;
}
void seperate(){
    std::cout << "////////////////////////////////////////////////////" << std::endl;
    std::cout << "////////////////////////////////////////////////////" << std::endl;
    std::cout << "////////////////////////////////////////////////////" << std::endl;
    std::cout << "////////////////////////////////////////////////////" << std::endl;
}
int main(int argc, char const *argv[])
{
    TimeController time_controller;
    time_controller.create(0);
    std::cout << "Current time is 0" << std::endl;
    
    seperate();
    while (true)
    {
        Uint64 value;
        Uint64 previous_time = time_controller.getTime();
        std::cout << "Set Next Time or (111, to quit) (112 for max Uint64 - 10)" << std::endl;
        std::cin >> value;   
        if(value == 111){
            break;
        }else if(value == 112){
            value = std::numeric_limits<Uint64>::max() - 10;
        }
        time_controller.update(value);
        std::cout << "Time From: " << previous_time << "ms To: " << time_controller.getTime() << "ms" << std::endl;
        std::cout << "Delta time is: " << time_controller.getDeltaTime() << std::endl;

        seperate();
    }
    

    return 0;
}

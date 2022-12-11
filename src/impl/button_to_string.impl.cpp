#include <breakout_engine.hpp>
int main(int argc, char const *argv[])
{
    Button a_button = Button(SDL_SCANCODE_A, "A Button");
    std::cout << "Button Test:===========" << std::endl;
    std::cout << toString(a_button) << std::endl;
    return 0;
}

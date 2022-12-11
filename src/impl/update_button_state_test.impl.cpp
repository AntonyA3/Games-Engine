#include <breakout_engine.hpp>


void displayTable(ButtonState state, bool down){
    std::string state_string = toString(state);
    std::string bool_string = toString(down);
    std::string new_state_string = toString(update(state, down));
    std::cout << "state: " << state_string << "| down: " << bool_string << " | new state: " << new_state_string << "|\n";
}

int main(int argc, char const *argv[])
{
    std::cout << "| Previous State | down | new state|\n ";
    displayTable(ButtonState_Pressed, true);
    displayTable(ButtonState_Down, true);
    displayTable(ButtonState_Up, true);
    displayTable(ButtonState_Released, true);
    displayTable(ButtonState_Pressed, false);
    displayTable(ButtonState_Down, false);
    displayTable(ButtonState_Up, false);
    displayTable(ButtonState_Released, false);     

    return 0;
}


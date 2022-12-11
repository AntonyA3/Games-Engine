#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <assert.h>

enum ButtonState{
    ButtonState_Pressed,
    ButtonState_Down,
    ButtonState_Up,
    ButtonState_Released
};


std::string toString(bool value){
    return (value) ? "true" : "false";
}


std::string toString(ButtonState value){
    switch (value)
    {
    case ButtonState_Pressed:
        return "ButtonState_Pressed";
    case ButtonState_Down:
        return "ButtonState_Down";
    case ButtonState_Up:
        return "ButtonState_Up";
    case ButtonState_Released:
        return "ButtonState_Released";    
    }
}

ButtonState updateButtonState(ButtonState state, bool down){
    ButtonState new_state;
    new_state = (state == ButtonState_Pressed && down) ? ButtonState_Down : new_state;
    new_state = (state == ButtonState_Down && down) ? ButtonState_Down : new_state;
    new_state = (state == ButtonState_Up && down) ? ButtonState_Pressed : new_state;
    new_state = (state == ButtonState_Released && down) ? ButtonState_Pressed : new_state;
    new_state = (state == ButtonState_Pressed && !down) ? ButtonState_Released : new_state;
    new_state = (state == ButtonState_Down && !down) ? ButtonState_Released : new_state;
    new_state = (state == ButtonState_Up && !down) ? ButtonState_Up : new_state;
    new_state = (state == ButtonState_Released && !down) ? ButtonState_Up : new_state;
    std::cout << "|"<< toString(state) <<" | |" << toString(down) << " | | " << toString(new_state) << "|\n" ;
    
    return new_state;
}


int main(int argc, char const *argv[])
{
    std::string command;
    std::string file_content;
    while(true){

        std::cout << "============" << std::endl;
        std::cout << "type \"exit\" to quit" << std::endl; 
        std::cout << "press enter to continue" << std::endl; 
        std::cout << "============" << std::endl;

        std::cin >> command;
        if(command == "exit"){
            break;
        }

        std::cout << "| Previous State | down | new state|\n ";

        updateButtonState(ButtonState_Pressed, true);
        updateButtonState(ButtonState_Down, true);
        updateButtonState(ButtonState_Up, true);
        updateButtonState(ButtonState_Released, true);
        updateButtonState(ButtonState_Pressed, false);
        updateButtonState(ButtonState_Down, false);
        updateButtonState(ButtonState_Up, false);
        updateButtonState(ButtonState_Released, false);     
    }
    return 0;
}


#include <breakout_engine.hpp>

Button::Button(SDL_Scancode scancode, std::string tag){
    this->state_change = true; // Presume that initialisation is a state change
    this->tag = tag;
    this->scancode = scancode;
    this->state = ButtonState_Up;
}


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

std::string toString(Button& button){
    std::stringstream ss;
    ss <<"Button: {\n";
    ss <<"   state_change: " << toString(button.state_change) << "\n";
    ss <<"   tag: " << button.tag << "\n";
    ss <<"   scancode: " << SDL_GetScancodeName(button.scancode) << "\n";
    ss <<"   button_state: " << toString(button.state) << "\n";
    ss << "}\n";
    return ss.str();
}


std::string readFile(std::string filename){
    std::stringstream ss;
    std::ifstream my_read_file;
    my_read_file.open(filename);
    char read_buffer[2048];
    bool open = my_read_file.is_open();
    assert(open);
    if(open){
        while (!my_read_file.eof())
        {
            my_read_file.getline(read_buffer, 2048);
            ss << read_buffer;
            if(!my_read_file.eof()){
                ss << "\n";
            }
        }  
        my_read_file.close();
    }
    return ss.str();
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
    return new_state;
}

void updateButton(Button& button, const Uint8 * keyboard_state){
    ButtonState new_state = updateButtonState(button.state, keyboard_state[button.scancode]);
    button.state_change = new_state != button.state;
    button.state = new_state;
}

void alwaysShowDemo(){
    bool show = true;
    ImGui::ShowDemoWindow(&show);
}

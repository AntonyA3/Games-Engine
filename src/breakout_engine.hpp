#ifndef BREAKOUT_ENGINE_HPP
#define BREAKOUT_ENGINE_HPP
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>

#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <imgui/imgui_internal.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_sdl.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>

#include <vector>
enum Base_Event {
    Base_Event_No_Event = 0,
    Base_Event_Quit_Event,
    Base_Event_Window_Resize,
};

enum ButtonState{
    ButtonState_Pressed,
    ButtonState_Down,
    ButtonState_Up,
    ButtonState_Released
};

struct Button{
    bool state_change; // This bool detects whether the button state has changed after an update, which should occur every frame
    std::string tag;
    SDL_Scancode scancode; // The button is assigned to the key
    ButtonState state; // the button is presumed to be up by default
    Button(SDL_Scancode scancode, std::string tag); // Constructor takes a scancode
};


typedef glm::vec4 Color;
std::string readFile(std::string filename); // given a file return the file content
void updateButtonState(ButtonState& new_state, ButtonState state, bool down);
void updateButton(Button& button, const Uint8 * keyboard_state);
std::string toString(bool value);
std::string toString(ButtonState value);
void alwaysShowDemo();
#endif
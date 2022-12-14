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

struct Rect{
    glm::vec2 position;
    glm::vec2 size;
    Rect(glm::vec2 position, glm::vec2 size);
    glm::vec2 topLeft();
    glm::vec2 topRight();
    glm::vec2 bottomLeft();
    glm::vec2 bottomRight();
};

struct Button{
    bool state_change; // This bool detects whether the button state has changed after an update, which should occur every frame
    std::string tag;
    SDL_Scancode scancode; // The button is assigned to the key
    ButtonState state; // the button is presumed to be up by default
    Button(SDL_Scancode scancode, std::string tag); // Constructor takes a scancode
};

struct Cursor{
    glm::ivec2 position;
    glm::ivec2 delta;
    Cursor();
};

struct VertexIndexBatch{
    std::vector<float> verticies;
    std::vector<unsigned int> indicies;
    unsigned int index_offset = 0;
    void clear();
};

struct Mesh{
    GLuint vertex_buffer, index_buffer;
    Mesh();
};

typedef glm::vec3 Color3;
typedef glm::vec4 Color4;
std::string readFile(std::string filename); // given a file return the file content
void update(glm::mat4& matrix, int width, int height);
/*
| State                | is Down | New state            |
| ---                  | ---     | ---                  |
| ButtonState_Pressed  | true    | ButtonState_Down     |
| ButtonState_Down     | true    | ButtonState_Down     |
| ButtonState_Up       | true    | ButtonState_Pressed  |
| ButtonState_Released | true    | ButtonState_Pressed  |
| ButtonState_Pressed  | false   | ButtonState_Released |
| ButtonState_Down     | false   | ButtonState_Released |
| ButtonState_Up       | false   | ButtonState_Up       |
| ButtonState_Released | false   | ButtonState_Up       |
*/
ButtonState update(ButtonState state, bool down);
void update(Button& button, const Uint8 * keyboard_state);
void update(Cursor& cursor);
void update(Mesh& mesh, VertexIndexBatch& batch);

/*
| value | string  |
| true  | "true"  |
| false | "false" |
*/
std::string toString(bool value);
/**/
std::string toString(ButtonState value);
/**/

template<typename vector>
std::string toString(vector& obj){
    std::stringstream ss;
    ss << "[x: " << obj.x << ", y: " << obj.y << "]";
    return ss.str();
}
/**/
std::string toString(Rect& rect);
/**/
std::string toString(Button& button);
/**/
std::string toString(Cursor& mouse);
/**/
std::string toString(Mesh& mesh);
GLuint makeShader(GLenum shader_type, const char * shader_text);
GLuint makeShader(GLenum shader_type, std::string filename);
void addRect(VertexIndexBatch& vertex_index_batch, Rect& rect, Color3& color);
void displayShaderCompileStatus(GLuint shader_object);
void alwaysShowDemo();
#endif
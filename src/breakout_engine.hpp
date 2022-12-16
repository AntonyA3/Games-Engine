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
    GLuint vertex_buffer = 0, index_buffer = 0;
    int index_count = 0;
    Mesh();
};



struct CommonSDLTest{
    SDL_Window * window; // An **allocated reference** to the SDLWindow object that created, **on creation**
    void cleanup();
};

/* Thes Object should not be used in the application
However is  useful for creating an SDL application that will
be useful for testing whether the Input is functioning correctly,
However this does not create any video */
struct BasicSDLApplicationLoopTest : public CommonSDLTest
{
    int width, height;
    void initialise();
    void update(bool& active);

};

struct BasicSDLOpenGLTest : public CommonSDLTest
{
    SDL_GLContext gl_context; // To Store the SDL GLContext
    int opengl_major_version = 3, // To store the open gl major version
    opengl_minor_version = 3,
    width = 640, // this value id the current window width, it is initialised to the default
    height = 480; // this value id the current window height, it is initialised to the default; // To store the open gl minor version
    std::string window_name = "Test"; // The Window Name Which is initially set the breakout Game
    void initialise();
};

struct TimeTicker{
    Uint64 current_time, tick_time, 
    accumulated_time;// This variable is designed to reset every tick which marks a tick
    TimeTicker(Uint64 tick_time, Uint64 current_time);
    bool tick();
    void addTime(Uint64 new_time);
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
GLuint makeProgram(GLuint vertex_shader, GLuint fragment_shader);
GLuint makeProgram(std::string vertex_shader_file, std::string fragment_shader_file);
void addRect(VertexIndexBatch& vertex_index_batch, Rect& rect, Color3& color);
void displayShaderCompileStatus(GLuint shader_object);
void alwaysShowDemo();
#endif
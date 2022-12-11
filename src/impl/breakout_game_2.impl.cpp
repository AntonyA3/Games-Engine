/*
    [Contents]
*/

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

Button::Button(SDL_Scancode scancode, std::string tag){
    this->state_change = true; // Presume that initialisation is a state change
    this->tag = tag;
    this->scancode = scancode;
    this->state = ButtonState_Up;
}

typedef glm::vec4 Color;
std::string readFile(std::string filename); // given a file return the file content
void updateButtonState(ButtonState& new_state, ButtonState state, bool down);
void updateButton(Button& button);
std::string toString(bool value);
std::string toString(ButtonState value);

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
int main(int argc, char const *argv[])
{
    const Color grey = Color(0.5f, 0.5f, 0.5f, 1.0f);
    bool active = true; // To store whether the appplication is active
    SDL_Window * window; // An **allocated reference** to the SDLWindow object that created, **on creation**
    SDL_GLContext gl_context; // To Store the SDL GLContext
    std::string window_name = "Breakout Game"; // The Window Name Which is initially set the breakout Game
    GLenum err; // Stores to value of the flag that detects whether there is an error in opengl
    int default_width = 640, // The default width were this should be the window width at begining of application
    default_height = 480, // The default height were this should be the window height at begining of application
    width = default_width, // this value id the current window width, it is initialised to the default
    height = default_height, // this value id the current window height, it is initialised to the default
    opengl_major_version = 3, // To store the open gl major version
    opengl_minor_version = 3; // To store the open gl minor version
    Color background_color; // To store the background color
    glm::mat4 render_matrix; // This is the matrix that will be used in all of the renderers
    
    std::vector<Button> buttons = {
        Button(SDL_SCANCODE_A, "Left"),
        Button(SDL_SCANCODE_D, "Right")
    };

    Button& left_button = buttons[0];
    Button& right_button = buttons[1];
    
    SDL_Scancode& left_button_scancode= left_button.scancode; // The left button is assigned to the key a
    ButtonState& left_button_state = left_button.state; // the left button is presumed to be up by default
    SDL_Scancode& right_button_scancode= right_button.scancode; // The right button is assigned to the key a
    ButtonState& right_button_state = right_button.state; // the right button is presumed to be up by default

    const Uint8 * keyboard_states = SDL_GetKeyboardState(NULL); // Points to the keyboard state

    if(SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_SetWindowMinimumSize(window, width, height); // Set the window with tho current widht and height, which should be the same as the minimum
    if(window == NULL){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY); // This is required of the opengl versions are greater than or equal to 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, opengl_major_version); // GL version is a property
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, opengl_minor_version); // GL minor version us a property
    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);
    err = glewInit(); // Initialise glew

    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(1);
    }

    SDL_GL_MakeCurrent(window, gl_context);
    // Initialise Imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext(NULL);
    ImGuiIO * io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->IniFilename = NULL; // There is no imgui ini file to restore imgui tom it's default state
    io->ConfigWindowsMoveFromTitleBarOnly = true;
    ImGui::StyleColorsDark(NULL); // use default ciolor pallette
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 150");
    // end the initialisation of opengl
    glViewport(0, 0, width, height);
    background_color = grey;
    glClearColor(background_color.r, background_color.g, background_color.b, background_color.a);
    while (active) // app loop
    {
        SDL_Event event; // The current SDL event to process
        while (SDL_PollEvent(&event))
        {   
            ImGui_ImplSDL2_ProcessEvent(&event);
            // An SDL Event is proceesed in a way where nested events should be mapped to non nested events
            Base_Event base_event = Base_Event_No_Event;
            base_event = (event.type == SDL_QUIT) ? Base_Event_Quit_Event : base_event;
            base_event = (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) ? Base_Event_Window_Resize : base_event;
            switch (base_event)
            {
            case Base_Event_Quit_Event:
                active = false; // When this is false the program will terminate
                break;
            case Base_Event_Window_Resize:
                width = event.window.data1; // this sets the width
                height = event.window.data2; // this sets the height
                glViewport(0, 0, width, height);
                break;

            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // update buttons
        for (Button& button : buttons){
            updateButton(button, keyboard_states);
            if(button.state_change){
                std::cout << button.tag << " Button State: " << toString(button.state)<< std::endl;
            }
        }


        // Beginning a new ImGui Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Inspector");
        ImGui::Text("width: %d", width);
        ImGui::Text("height: %d", height);
        ImGui::End();

        alwaysShowDemo();
        // Ending an imgui Frame
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);

    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
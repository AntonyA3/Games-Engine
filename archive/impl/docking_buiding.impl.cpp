#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <imgui/imgui_internal.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_sdl.h>


/**
 * Initial Ustructured attempts at trying tpo understand how to use the docking mechanism

 */

int main(int argc, char const *argv[])
{
    
    SDL_Window * window; // An **allocated reference** to the SDLWindow object that created, **on creation**
    bool active = true; // To store whether the window is **currently** active
    int width = 640, // To store the **current** width of the window 
    height = 480; //  To store the **current**  height of the Window  
    SDL_GLContext gl_context;
    int gl_major_version = 3;
    int gl_minor_version = 3;
    int init_result = SDL_Init( SDL_INIT_VIDEO );

    if(init_result < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    window = SDL_CreateWindow(
        "Breakout Game", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        width, 
        height, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );
    SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_SetWindowMinimumSize(window, 640, 480);
    if(window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }    

    if (gl_major_version > 3 || (gl_major_version == 3 && gl_minor_version >= 3))
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_major_version); // GL version is a property
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_minor_version); // GL minor version us a property
    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);
    GLenum err = glewInit();

    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(1);
    }


    SDL_GL_MakeCurrent(window, gl_context);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext(NULL);
    ImGuiIO * io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->ConfigWindowsMoveFromTitleBarOnly = true;
    io->IniFilename = NULL;
    ImGui::StyleColorsDark(NULL);
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 150");

    float slider_ratio = 0.5f;
    // float parent_width;
    // float node_1_width;
    // float node_2_width;

    bool docks_visible = true;
    while (active)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {   
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT:
                active = false;
                break;
            }
        }
        glViewport(0, 0, 640, 480);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();


        
        bool show_demo = true;

        ImGui::ShowDemoWindow(&show_demo);

        ImGui::Begin("Toggles", 0);
        ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());
        ImGui::Checkbox("Display Full Viewport dock Window", &docks_visible);
        ImGui::End();



        // Test Diffrent Methods of docking within a window the

        // 1 or 2 windows stacked vertically

        ImGui::Begin("Undockable",  (bool *)__null, 0);
        ImGui::End();

        /* NOTE: Make sure the window with the dock space has been created beforethe other windows
        */
        ImGui::Begin("Docking Window", (bool *)__null, ImGuiWindowFlags_NoDocking);
        ImGui::Text("Item");
        ImGui::DockSpace(ImGui::GetID("MyDockSpace"), ImVec2(0.0f, 0.0f), 0);
        ImGui::End();


        ImGui::SetNextWindowSize(ImVec2(256,256));
        ImGui::SetNextWindowDockID(ImGui::GetID("MyDockSpace"), 0);
        ImGui::Begin("RidgedWindow1", (bool *)__null,0);
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(256,256));
        ImGui::Begin("RidgedWindow2",  (bool *)__null, 0);
        ImGui::End();



        // Display the Dock Windows
        

        if(docks_visible){

            ImGui::Begin("Window1", (bool *)__null, ImGuiWindowFlags_NoBringToFrontOnFocus);
            // ImGui::Text("parent width: %f", parent_width);
            // ImGui::Text("node1 width: %f", node_1_width);
            // ImGui::Text("node 2 width: %f", node_2_width);
            // node_1_width = ImGui::GetWindowWidth();
            ImGui::End();

            ImGui::Begin("Window2", (bool *)__null, ImGuiWindowFlags_NoBringToFrontOnFocus);
            {
                // node_2_width = ImGui::GetWindowWidth();


            }
            ImGui::End();
            

            //Docking inside window 4
            
            ImGui::Begin("Window4", (bool *)__null, 0);
                // node_1_width =fminf(node_1_width, ImGui::GetWindowWidth());
                
            ImGui::End();

            ImGui::Begin("Window5");
        
            ImGui::End();

            
            ImGui::Begin("Window6");
        
            ImGui::End();
            ImGui::Begin("Window7");
        
            ImGui::End();



            ImGuiID node_1 = ImGui::GetID("node_1");
            ImGuiID left_id = ImGui::GetID("left_id");
            ImGuiID right_id = ImGui::GetID("right_id");

            ImGui::DockBuilderAddNode(node_1, 0); // Create Node with ID of 1
            ImGui::DockBuilderSetNodeSize(node_1, ImVec2(480, 480)); // Set the size of the node
            ImGuiID id = ImGui::DockBuilderSplitNode(node_1,ImGuiDir_Left, slider_ratio, &left_id, &right_id); // Set the size of the node
            // ImGui::GetMousePos().x / 
            ImGui::DockBuilderDockWindow("Window1", left_id);
            ImGui::DockBuilderDockWindow("Window4", left_id);
            ImGui::DockBuilderDockWindow("Window2", right_id);
            ImGui::DockBuilderFinish(node_1);
        }

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

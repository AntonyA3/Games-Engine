#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <imgui/imgui_internal.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_sdl.h>


/*
    A sample of testing Gui Windows, to Find the Constraints

    * I can Dock Windows Into Dockspace

    - Can I move a window out of the position set by the dockbuilder then move it back into position
    * No I can not redock the window, prefer to use the node based, dockbuilder for windows that will be in a fixed position.

    - Can I doc the window into a dockspace without needing to add it as a node,but with just the dockspace Id
    * I can dock windows directly into the dockspace without needing to add a node;

    - Can I Split a dockspace Without adding a node then attaching it to a dockspace
    * No, The dockspace node Id needs to be added by the dockbuilder, then split, then finished then have the do space set at it's Id

    - Can a window that is created before the dockspace be docked into a dockspace
    * If a window is able to be docked into another window, it most be created after the window that it will be docked into

    - Can a window Have 2 dockspaces
    * Yes I can have two dockspaces inside a window

    * Conside the dockspace split layout to be an alternative to using columns
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
    io->IniFilename = NULL;
    // io->ConfigDockingNoSplit = true; Do not have this line if I want split based docking to work correctly

    io->ConfigWindowsMoveFromTitleBarOnly = true;
    ImGui::StyleColorsDark(NULL);
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 150");



    float slider_ratio = 0.5f;
    bool on_start = true;
    

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
        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->WorkPos, 0);

        ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize, 0);
        {
            /* code */
        }
        
        ImGui::Begin("Editor Viewport", (bool*)__null, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking);

        if(ImGui::DockBuilderGetNode(ImGui::GetID("editor_viewport_doc")) == NULL){ // DO NOT CALL GET NODE TO SET A VARIABLE
            // [Note] Creates a layout that will be used within the editor Window's dockspace
            ImGui::DockBuilderAddNode(ImGui::GetID("editor_viewport_doc"), ImGuiDockNodeFlags_DockSpace | ImGuiDockNodeFlags_NoResizeY);
            ImGui::DockBuilderSetNodeSize(ImGui::GetID("editor_viewport_doc"), ImGui::GetMainViewport()->WorkSize);
            ImGuiID l1_id = ImGui::GetID("l1"); // leaf
            ImGuiID r1_id = ImGui::DockBuilderSplitNode(ImGui::GetID("editor_viewport_doc"), ImGuiDir_Right, 0.75f, NULL, &l1_id); // Set the size of the node
            ImGuiID b2_id = ImGui::GetID("b2"); // leaf
            ImGuiID t2_id = ImGui::DockBuilderSplitNode(r1_id, ImGuiDir_Up, 0.25f, &t2_id, &b2_id); // Set the size of the node
            ImGuiID l3_id = ImGui::GetID("l3"); // leaf
            ImGuiID r3_id = ImGui::GetID("r3"); // leaf
            ImGui::DockBuilderSplitNode(t2_id, ImGuiDir_Right, 0.75, &l3_id, &r3_id); // Set the size of the node
            ImGui::DockBuilderDockWindow("Window1", l1_id);
            ImGui::DockBuilderDockWindow("Window2", b2_id);
            ImGui::DockBuilderDockWindow("Window3", l3_id);
            ImGui::DockBuilderDockWindow("Window4", r3_id);
            ImGui::DockBuilderFinish(ImGui::GetID("editor_viewport_doc"));
        }
        ImGui::DockSpace(ImGui::GetID("editor_viewport_doc"), ImVec2(0,0), ImGuiDockNodeFlags_NoDockingSplitMe );
        ImGui::End();


        ImGui::Begin("Window1", (bool*)__null, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize );
        ImGui::DockSpace(ImGui::GetID("window_1_dockspace"), ImVec2(0,0), ImGuiDockNodeFlags_NoDockingSplitMe);
        ImGui::End();

        ImGui::Begin("Window2", (bool*)__null,  ImGuiWindowFlags_NoResize);
        ImGui::DockSpace(ImGui::GetID("window_2_dockspace"), ImVec2(0,0), ImGuiDockNodeFlags_NoDockingSplitMe);
        ImGui::End();
        
        ImGui::Begin("Window3", (bool*)__null, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        if(ImGui::DockBuilderGetNode(ImGui::GetID("window_3_dockspace")) == NULL){
            ImGui::DockBuilderDockWindow("Scene", ImGui::GetID("window_3_dockspace")); // The Scene window is docked directly into the dockspace on initialisation
            ImGui::DockBuilderDockWindow("Scene2", ImGui::GetID("window_3_bottom_dockspace"));
            ImGui::DockBuilderFinish(ImGui::GetID("window_3_dockspace"));

        }
        ImGui::DockSpace(ImGui::GetID("window_3_dockspace"), ImVec2(0, ImGui::GetWindowHeight() / 2), ImGuiDockNodeFlags_NoDockingSplitMe);
        ImGui::DockSpace(ImGui::GetID("window_3_bottom_dockspace"), ImVec2(0, ImGui::GetWindowHeight() / 2), ImGuiDockNodeFlags_NoDockingSplitMe);

        ImGui::End();

        ImGui::Begin("Window4", (bool*)__null, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::DockSpace(ImGui::GetID("window_4_dockspace"), ImVec2(0,0), ImGuiDockNodeFlags_NoDockingSplitMe);
        ImGui::End();



        
        ImGui::Begin("Scene");
        ImGui::End();

        ImGui::Begin("Scene2");
        ImGui::End();

        bool show_demo = true;

        ImGui::ShowDemoWindow(&show_demo);
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

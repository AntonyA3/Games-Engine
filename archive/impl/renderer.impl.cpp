

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <renderer.hpp>


#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_sdl.h>


void processWindowEvent(Renderer& renderer, SDL_WindowEvent &event){
    switch (event.event)
    {
    case SDL_WINDOWEVENT_RESIZED:
        renderer.setWidthHeight( (int)event.data1,(int)event.data2);
        break;                
    default:
        break;
    }
}

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
    LOG(
        if(init_result < 0 )
        {
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        }
    );

    window = SDL_CreateWindow(
        "Breakout Game", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        width, 
        height, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );
    SDL_SetWindowResizable(window, SDL_TRUE);
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
    LOG(
        if (GLEW_OK != err)
        {
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
            exit(1);
        }
    );
    SDL_GL_MakeCurrent(window, gl_context);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext(NULL);
    ImGuiIO * io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark(NULL);
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 150");
    LOG(
        std::cout << "Imgui Initialised" << std::endl;
    );
    // Formalise the Design of the Renderer and the Tests that are needed for the renderer
    glm::vec4 background_color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    Renderer renderer = Renderer();
    renderer.create();      
    renderer.setWidthHeight(640, 480);

    renderer.setBackgroundColor(background_color.r, background_color.g, background_color.b, background_color.a);
    renderer.enableAlphaTransparency();

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
            case SDL_WINDOWEVENT:
                processWindowEvent(renderer, event.window);
                break;
            }
        }
        renderer.clearRender();
        renderer.begin();

        int rows = 64;
        int columns = 64;
        int spacing = 480 / 64;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns ;j++){
                if(j %4 == 0){
                    float size = spacing / 2.0f;

                    AARect rect;
                    rect.m_position = glm::vec2(spacing * i, spacing * j);
                    rect.m_size = glm::vec2(size, size);
                    renderer.addRect(rect, glm::vec3( i / 64.0f, j / 64.0f, 0.0f));
                }else{
                    Circle circle;
                    circle.position = glm::vec2(spacing * i, spacing * j);
                    circle.radius = spacing / 4.0f;
                    renderer.addCircle(circle, glm::vec3( i / 64.0f, j / 64.0f, 0.0f));
                }
            }   
        }
        renderer.render();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Render Debug");

        
        if(ImGui::SliderFloat4("Background Color", &background_color.r, 0.0f, 1.0f)){
            renderer.setBackgroundColor(background_color.r, background_color.g, background_color.b, background_color.a);
        }
        ImGui::End();
        

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); 
        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

#define ENABLE_DEBUG_LOGGER
#include <macros/debug_logger.hpp>
#include <stdio.h>
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_sdl.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <shapes/aa_rect.hpp>
#include <shapes/circle.hpp>
#include <renderer.hpp>
#ifndef SHADER_FILE_PATH
#define SHADER_FILE_PATH "./data/shaders/"
#endif
#include <input/keyboard_button.hpp>
#include <i_input.hpp>
#include <GL/glew.h>
#include <glutils.hpp>


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
        "Frame Buffer Test", 
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
    io->IniFilename = NULL; // No ini
  
    ImGui::StyleColorsDark(NULL);
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 150");

   
    int window_x, window_y;
    SDL_GetWindowSize(window, &window_x, &window_y);
    
    //generate the texture for rendering    

    Renderer renderer;
    renderer.create();

    GLuint color_texture;
    glGenTextures(1, &color_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, color_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 640, 480, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);


    GLuint depth_texture;
    glGenTextures(1, &depth_texture);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 640, 480, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, 0);






    GLuint frame_buffer_id;
    glGenFramebuffers(1, &frame_buffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_texture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){
        std::cout << "frame buffer is successful" << std::endl;
    }


    // Generate the shader program for rendering textures
    const char * texture_vertex_shader = "#version 330\n"
    "layout (location = 0) in vec3 vpos;\n"
    "layout (location = 1) in vec3 vcolor;\n"
    "layout (location = 2) in vec2 vTexcoord;\n"
    "uniform mat4 uViewMat;\n"
    "out vec3 fcolor;\n"
    "out vec2 fTexcoord;\n;"
    "void main(){\n"
    "   fcolor = vcolor;\n"
    "   fTexcoord = vTexcoord;\n"
    "   gl_Position = uViewMat * vec4(vpos, 1.0f);\n"
    "}\n";


    const char * texture_fragment_shader = "#version 330\n"
    "precision mediump float;\n"
    "in vec3 fcolor;\n"
    "in vec2 fTexCoord;\n"
    "out vec4 color;\n"
    "uniform sampler2D uTexture;\n"   
    "void main(){\n"
    "   color = texture(uTexture, fTexCoord);\n"
    "}\n";


    GLuint texture_program = GLutils().makeProgramFromContent(texture_vertex_shader, texture_fragment_shader);
    GLint texture_loc = glGetUniformLocation(texture_program, "uTexture");
    GLint matrix_loc = glGetUniformLocation(texture_program, "uViewMat");

    // create the texture quad
    AARect rect;
    rect.create(glm::vec2(0.0f, 0.0f), glm::vec2(640.0f / 2.0f, 480.0f / 2.0f));
    Mesh mesh;
    mesh.create();



    // Attach texture to frame buffer        

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
        // First Render the expected 'Scene'
        {
            glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_id);
            renderer.setBackgroundColor(0.5f, 0.5f, 0.5f, 1.0f);
            renderer.setWidthHeight(640.0f, 480.0f);
            renderer.enableAlphaTransparency();    

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glBindTexture(GL_TEXTURE_2D, color_texture);
            glViewport(0, 0, 640, 480);
            
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

            // Circle big_circle;

        
            float radius = 10.0f;
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("ds");
            ImGui::DragFloat("fd", &radius);
            ImGui::End();

          
            // big_circle.create(glm::vec2(0.0f, 0.0f), radius);
            // renderer.addCircle(big_circle, glm::vec3(1.0f, 0.0f, 0.0f));
            renderer.render();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        }
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glViewport(0, 0, 640, 480);
            glDisable(GL_DEPTH_TEST);
            renderer.setWidthHeight(640.0f, 480.0f);


            MeshData mesh_data;
            mesh_data.create();
            renderer.setBackgroundColor(0.0f, 0.0f, 0.5f, 1.0f);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
            // Push Rect with color and tecture coordinate
            RectVerticies rect_verticies;
            rect_verticies.create(rect);
            mesh_data.pushPosition(rect_verticies.bottom_left );
            mesh_data.pushColor(color);
            mesh_data.pushTextureCoordinates(glm::vec2(0.0f, 1.0f));

            mesh_data.pushPosition( rect_verticies.bottom_right );
            mesh_data.pushColor(color);
            mesh_data.pushTextureCoordinates(glm::vec2(1.0f, 1.0f));

            mesh_data.pushPosition(rect_verticies.top_right);
            mesh_data.pushColor(color);
            mesh_data.pushTextureCoordinates(glm::vec2(1.0f, 0.0f));

            mesh_data.pushPosition(rect_verticies.top_left);
            mesh_data.pushColor(color);
            mesh_data.pushTextureCoordinates(glm::vec2(0.0f, 0.0f));

            mesh_data.generateRectIndicies();

            mesh.setData(
                &mesh_data.getVertexData().at(0),
                mesh_data.getVertexData().size(),
                &mesh_data.getIndexData().at(0),
                mesh_data.getIndexData().size()
            );

            glUseProgram(texture_program);
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, color_texture);
            glUniform1i(texture_loc, 0);

            glm::mat4 m = glm::ortho(0.0f, (float)640.0f, (float)480.0f, 0.0f);
            glUniformMatrix4fv(matrix_loc, 1, GL_FALSE, &m[0][0]);
        
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(0 * sizeof(float)));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);
            mesh.draw();
            mesh_data.clear();
            SDL_GL_SwapWindow(window);
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
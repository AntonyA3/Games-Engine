#define ENABLE_DEBUG_LOGGER
#include <macros/debug_logger.hpp>


#include <stdio.h>
#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>


#include <sdl_window_wrapper.hpp>
#include <sdl_gl_context_wrapper.hpp>
#include <dear_imgui_demo_window.hpp>
#include <loader/file_reader.hpp>
#include <mesh.hpp>
#include <shader_program.hpp>
#include <shapes/aa_rect.hpp>
#include <shapes/circle.hpp>
#include <sdl_gl_context_data.hpp>
#include <sdl_window_data.hpp>
#include <complete_window.hpp>
#include <complete_window_data.hpp>
#include <sub_renderer.hpp>
#include <renderer.hpp>
#ifndef SHADER_FILE_PATH
#define SHADER_FILE_PATH "./data/shaders/"
#define GAMES_ENGINE_USE_IMGUI_DEBUGING
#endif

int main(int argc, char const *argv[])
{


    LOG(std::cout << "Hello World\n" );

    CompleteWindowData complete_window_data = {
        {
            SDL_INIT_VIDEO, 
            std::string("Sample Title"),
            640,
            480,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            true,
            true,
            SDL_TRUE
        },
        {
            3, 
            3
        }
    };
    
    CompleteWindow complete_window; 
    complete_window.create(complete_window_data); // CREATE complete_window

    DearImGuiDemoWindow demo_window; //CREATE demo_window

    glm::mat4 global_matrix = glm::ortho(0.0f, 480.0f, 640.0f, 0.0f); //CREATE global_matrix

    // SET opengl viewport to WIDTH of sdl window and HEIGHT of SDL window
    glViewport(0, 0, 
        complete_window.m_sdl_window_wrapper.m_width,
        complete_window.m_sdl_window_wrapper.m_height
    );

    //SET Opengl background color to VAR opengl background color

    float opengl_color[4] = {0.5f, 0.5f, 0.5f, 1.0f};
    glClearColor(opengl_color[0], opengl_color[1], opengl_color[2], opengl_color[4]);
    
    // Enable Face Culling & Cull the back face
    bool cull_face_on = true;
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Enable Transparency (in shaders an alpha of 0 is transparent)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    std::vector<VertexAttributeData> polygon_vertex_attributes;
    polygon_vertex_attributes.insert(polygon_vertex_attributes.end(),{{3}, {3}});
    std::vector<VertexAttributeData> circle_vertex_attributes;
    circle_vertex_attributes.insert(circle_vertex_attributes.end(),{{3}, {3}, {2}});
  
    Renderer renderer;
    renderer.create(renderer_data);

    while (complete_window.m_sdl_window_wrapper.m_active)
    {
        while (complete_window.polledEvent())
        {
            SDL_Event& event = complete_window.nextEvent();
            switch (event.type)
            {
            case SDL_QUIT:
                complete_window.m_sdl_window_wrapper.terminate(); // TERMINATE SDL WINDOW
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_RESIZED:
                    // SET SDL Window width and window height
                    complete_window.m_sdl_window_wrapper.m_width = (int)event.window.data1;
                    complete_window.m_sdl_window_wrapper.m_height = (int)event.window.data2;
                    glViewport(0, 0, complete_window.m_sdl_window_wrapper.m_width, complete_window.m_sdl_window_wrapper.m_height); // UPDATE OPENGL Viewport size
                    break;                
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // CLEAR WINDOW
        

        renderer.begin(); //BEGIN RENDERER (clears the vertex arrys in any renderer)
        renderer.setMatrix(global_matrix);
        {            
            Circle circle;
            circle.create(glm::vec2(400, 400), 50.0f);
            renderer.addCircle(circle);            
            AARect rect0, rect1;

            rect0.create(glm::vec2(100, 100), glm::vec2(100, 100));
            renderer.addRect(rect0);

            rect1.create(glm::vec2(200, 200), glm::vec2(100, 100));
            renderer.addRect(rect1);
 
        }
        renderer.render();
        
     
        glUseProgram(0); // Ues default shader
        complete_window.beginFrame();

        // Display window to toggle face culling
        ImGui::Begin("Cull Face Toggle");
        {
                    
            if(ImGui::Checkbox("Face Culling is On", &cull_face_on)){
                if(cull_face_on){
                    glEnable(GL_CULL_FACE);
                    glCullFace(GL_BACK);
                }else{
                    glDisable(GL_CULL_FACE);
                }
            }
            ImGui::End();
        }
        demo_window.show();
        complete_window.renderFrame(); // Renders the current ImGuI fRAME

        SDL_GL_SwapWindow(complete_window.m_sdl_window_wrapper.getWindow()); //Swap the ImGui Frame to the rendered Frame


        
    }
    complete_window.m_sdl_window_wrapper.destroy(); 
    SDL_Quit(); //Quit the SDL application

    return 0; // END PROGRAM
}

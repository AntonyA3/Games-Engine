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
#include <loader/program_loader.hpp>
#include <mesh.hpp>
#include <shader_program.hpp>
#include <aa_rect.hpp>
#include <circle.hpp>
#include <mesh_data_converter.hpp>
#include <sdl_gl_context_data.hpp>
#include <sdl_window_data.hpp>
#include <complete_window.hpp>
#include <complete_window_data.hpp>
#include <sub_renderer.hpp>
#include <vertex_attribute_data.hpp>
#include <renderer_data.hpp>
#include <renderer.hpp>
#ifndef SHADER_FILE_PATH
#define SHADER_FILE_PATH "./data/shaders/"
#endif
int main(int argc, char const *argv[])
{
    CompleteWindow complete_window;
    SDLGLContextData sdl_gl_context_data = {
        3, 
        3
    };

    SDLWindowData sdl_window_data ={
        SDL_INIT_VIDEO, 
        std::string("Sample Title"),
        640,
        480,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        true,
        true,
        SDL_TRUE
    };

    CompleteWindowData complete_window_data = {
        sdl_window_data,
        sdl_gl_context_data
    };
  
    complete_window.create(complete_window_data);
    DearImGuiDemoWindow demo_window;
    glm::mat4 global_matrix = glm::ortho(0.0f, 480.0f, 640.0f, 0.0f);
    
    glViewport(0, 0, 
        complete_window.m_sdl_window_wrapper.m_width,
        complete_window.m_sdl_window_wrapper.m_height
    );
    float opengl_color[4] = {0.5f, 0.5f, 0.5f, 1.0f};
    glClearColor(opengl_color[0], opengl_color[1], opengl_color[2], opengl_color[4]);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    std::vector<VertexAttributeData> polygon_vertex_attributes;
    polygon_vertex_attributes.insert(polygon_vertex_attributes.end(),{{3}, {3}});
    std::vector<VertexAttributeData> circle_vertex_attributes;
    circle_vertex_attributes.insert(circle_vertex_attributes.end(),{{3}, {3}, {2}});
    RendererData renderer_data = {
        // polygon_renderer_data
        {
            // shader_program_data
            {
                std::string(SHADER_FILE_PATH) + "polygon_position_color.vert",
                std::string(SHADER_FILE_PATH) + "polygon_position_color.frag",
                polygon_vertex_attributes
            }

        },
        // circle_renderer_data
        {
            // shader_program_data
            {
                std::string(SHADER_FILE_PATH) + "circle_position_color_texcoord.vert",
                std::string(SHADER_FILE_PATH) +"circle_position_color_texcoord.frag",
                circle_vertex_attributes
            }

        }
    };
    Renderer renderer;
    renderer.create(renderer_data);
  


    bool cull_face_on = true;

    AARect render_rectangle;
    render_rectangle.create(glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 100.0f));

    while (complete_window.m_sdl_window_wrapper.m_active == true)
    {
        while (complete_window.polledEvent())
        {
            SDL_Event& event = complete_window.nextEvent();
            complete_window.m_dear_imgui_wrapper.processEvent(event);
            switch (event.type)
            {
            case SDL_QUIT:
                complete_window.m_sdl_window_wrapper.terminate();
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_RESIZED:
                    complete_window.m_sdl_window_wrapper.m_width = (int)event.window.data1;
                    complete_window.m_sdl_window_wrapper.m_height = (int)event.window.data2;
                    glViewport(0, 0, complete_window.m_sdl_window_wrapper.m_width, complete_window.m_sdl_window_wrapper.m_height);
                    break;                
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        renderer.begin();
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
        
     
        glUseProgram(0);
        complete_window.m_dear_imgui_wrapper.beginFrame();

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
        complete_window.m_dear_imgui_wrapper.renderFrame();
        SDL_GL_SwapWindow(complete_window.m_sdl_window_wrapper.getWindow());
        
    }
    complete_window.m_sdl_window_wrapper.destroy();
    SDL_Quit();

    return 0;
}

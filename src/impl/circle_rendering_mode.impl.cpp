#include <stdio.h>
#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <sdl_window_wrapper.hpp>
#include <sdl_gl_context_wrapper.hpp>
#include <dear_imgui_demo_window.hpp>
#include <loader/file_reader.hpp>
#include <glm/glm.hpp>
#include <loader/program_loader.hpp>
#include <mesh.hpp>
#include <mesh_generator.hpp>
#include <shader_program.hpp>
#include <aa_rect.hpp>
#include <mesh_from_rectangle.hpp>
#include <polygon_batcher.hpp>
#include <sdl_gl_context_data.hpp>
#include <sdl_window_data.hpp>
#include <complete_window.hpp>
#include <complete_window_data.hpp>
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
    ShaderProgram circle_shader_program;
    
    std::string vertex_file = std::string(SHADER_FILE_PATH) + "circle_position_color.vert";
    std::string fragment_file = std::string(SHADER_FILE_PATH) +"circle_position_color.frag";
    ProgramLoader program_loader;
    program_loader.load(vertex_file, fragment_file, true);
    circle_shader_program.m_program = program_loader.m_program;
    circle_shader_program.m_uniform_matrix_location = glGetUniformLocation(circle_shader_program.m_program, "u_view_mat");

    

    //Print the program loader
    std::cout << "circle program successful: " << ((program_loader.m_status == GL_TRUE) ? "true" : "false") << std::endl;
    std::cout << "circle vertex shader successful: " << ((program_loader.m_vertex_shader_content.m_status == GL_TRUE) ? "true" : "false") << std::endl;
    std::cout << "circle fragment shader successful: " << ((program_loader.m_fragment_shader_content.m_status == GL_TRUE) ? "true" : "false") << std::endl;
    std::cout << "fragment shader fail log" << program_loader.m_fragment_shader_content.m_info_log << std::endl;


    
    Renderer renderer;
    renderer.create(circle_shader_program);

    MeshGenerator mesh_generator;
    //new Flat Shader
  
    //Expect shader to compile

   

    AARect render_rectangle;
    render_rectangle.create(glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 100.0f));
    MeshFromRectangle mesh_from_rectangle;

    Mesh rectangle_mesh = mesh_from_rectangle.generate(render_rectangle);
    
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
        AARect rect0, rect1;
        rect0.create(glm::vec2(100, 100), glm::vec2(100, 100));
        rect1.create(glm::vec2(200, 200), glm::vec2(100, 100));

        renderer.addRect(rect0);
        renderer.addRect(rect1);
        renderer.setMatrix(&global_matrix[0][0]);
        renderer.render();
        
        glUseProgram(0);
        complete_window.m_dear_imgui_wrapper.beginFrame();

        complete_window.m_dear_imgui_wrapper.renderFrame();
        SDL_GL_SwapWindow(complete_window.m_sdl_window_wrapper.getWindow());
        
    }
    complete_window.m_sdl_window_wrapper.destroy();
    SDL_Quit();

    return 0;
}




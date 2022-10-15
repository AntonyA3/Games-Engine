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

#ifndef SHADER_FILE_PATH
#define SHADER_FILE_PATH "./data/shaders/"
#endif
int main(int argc, char const *argv[])
{
    SDLWindowWrapper sdl_window;
    SDLEventWrapper sdl_event_wrapper;
    SDLGLContextWrapper sdl_gl_context;
    DearImGuiWrapper imgui_wrapper;
    DearImGuiDemoWindow demo_window;
  
    
    sdl_window.create();
    sdl_gl_context.create(sdl_window.getWindow(), 3, 3);
 
    
    glViewport(0, 0, sdl_window.getWidth(),sdl_window.getHeight());
    float opengl_color[4] = {0.5f, 0.5f, 0.5f, 1.0f};
    glClearColor(opengl_color[0], opengl_color[1], opengl_color[2], opengl_color[4]);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    imgui_wrapper.create(sdl_window.getWindow(), sdl_gl_context.getGLContext());

    //new Flat Shader
    ShaderProgram shader_program;
    {
        std::string vertex_file = std::string(SHADER_FILE_PATH) + "polygon_position_color.vert";
        std::string fragment_file = std::string(SHADER_FILE_PATH) +"polygon_position_color.frag";
        ProgramLoader program_loader;
        program_loader.load(vertex_file, fragment_file, true);
        shader_program.program = program_loader.m_program;
        shader_program.uniform_matrix_location = glGetUniformLocation(shader_program.program, "u_view_mat");
    }

    //Expect shader to compile

    Mesh mesh;
    mesh.create();

    MeshGenerator mesh_generator;
    {
        int float_count = 6 * 3;
        int index_count = 3;
        float position_color[float_count] = {
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f
        };
        unsigned int indicies[index_count] = {
            0, 1, 2
        };
        mesh_generator.generate(mesh, &position_color[0], float_count, &indicies[0], index_count);
    }
   
    bool cull_face_on = true;

    AARect render_rectangle;
    render_rectangle.create(glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, 0.5f));
    MeshFromRectangle mesh_from_rectangle;
    Mesh rectangle_mesh = mesh_from_rectangle.generate(render_rectangle);
    
    while (sdl_window.isActive())
    {
        while (sdl_event_wrapper.polledEvent())
        {
            SDL_Event& event = sdl_event_wrapper.nextEvent();
            imgui_wrapper.processEvent(event);
            switch (event.type)
            {
            case SDL_QUIT:
                SDL_Log("Program quit after %i ticks", event.quit.timestamp);
                sdl_window.terminate();
                break;
            default:
                break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader_program.use();

        mesh.bind();
        shader_program.enableVertexAttributes();
        shader_program.setMatrix(&mesh.m_matrix[0][0]);
        mesh.draw();

        rectangle_mesh.bind();
        shader_program.enableVertexAttributes();
        shader_program.setMatrix(&rectangle_mesh.m_matrix[0][0]);
        rectangle_mesh.draw();

        glUseProgram(0);
        imgui_wrapper.beginFrame();

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
        imgui_wrapper.renderFrame();
        SDL_GL_SwapWindow(sdl_window.getWindow());
        
    }
    sdl_window.destroy();
    SDL_Quit();

    return 0;
}

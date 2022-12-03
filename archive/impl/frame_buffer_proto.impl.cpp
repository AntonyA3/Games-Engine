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

#ifndef SHADER_FILE_PATH
#define SHADER_FILE_PATH "./data/shaders/"
#endif
#include <GL/glew.h>
#include <glutils.hpp>



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
    SDL_GL_MakeCurrent(window, gl_context);
    
    // End Setup

    struct {
        GLuint object;
        GLuint color_texture;
    } frame_buffer;

    struct {
        GLuint program;
        GLint texture_uniform;
        GLint matrix_uniform;
    } texture_renderer;


    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer.object);

    glGenTextures(1, &frame_buffer.color_texture);
    glBindTexture(GL_TEXTURE_2D, frame_buffer.color_texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 640, 480, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glGenFramebuffers(1, &frame_buffer.object);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer.object);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frame_buffer.color_texture, 0);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){
        std::cout << "frame buffer is successful" << std::endl;
    }

    texture_renderer.program =  GLutils().makeProgram("data\\shaders\\texture_color.vert", "data\\shaders\\texture_color.frag");
    texture_renderer.texture_uniform  = glGetUniformLocation(texture_renderer.program, "uTexture");
    texture_renderer.matrix_uniform = glGetUniformLocation(texture_renderer.program, "uViewmat");

    
    GLuint flat_shader = GLutils().makeProgram("./data/shaders/polygon_position_color.vert", "./data/shaders/polygon_position_color.frag");
    GLint flat_shader_matrix_loc = glGetUniformLocation(flat_shader, "u_view_mat");
    // Triangle mesh
    float triangle_data[6 * 3] {
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        100.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        400.0f, 400.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    };

    GLuint triangle;
    glGenBuffers(1, &triangle);
    glBindBuffer(GL_ARRAY_BUFFER, triangle);     
    glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), triangle_data,  GL_DYNAMIC_DRAW);
         

    float quad_vertex_data[8 * 4] {
        0.0f, 100.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        100.0f, 100.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };
    GLuint quad_vertex;
    glGenBuffers(1, &quad_vertex);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertex);     
    glBufferData(GL_ARRAY_BUFFER, 8 * 4 * sizeof(float), quad_vertex_data,  GL_DYNAMIC_DRAW);

    unsigned int quad_index_data[6] {
        0, 1, 2,
        0, 2, 3
    };
    GLuint quad_index;
    glGenBuffers(1, &quad_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_index);     
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), quad_index_data,  GL_DYNAMIC_DRAW);
    

    while (active)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {   
            switch (event.type)
            {
            case SDL_QUIT:
                active = false;
                break;
    
            }
        }
        glm::mat4 m;

       
        glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer.object);
        glViewport(0, 0, 640, 480);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(flat_shader);
    
        m = glm::ortho(0.0f, (float)640.0f, (float)480.0f, 0.0f);
        glUniformMatrix4fv(flat_shader_matrix_loc, 1, GL_FALSE, &m[0][0]);
    

        glBindBuffer(GL_ARRAY_BUFFER, triangle);     
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(0 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Render the texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(0, 0, 640, 480);
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, quad_vertex);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_index);


        glUseProgram(texture_renderer.program);
        glUniformMatrix4fv(texture_renderer.matrix_uniform, 1, GL_FALSE, &m[0][0]);
        glUniform1i(texture_renderer.texture_uniform, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, frame_buffer.color_texture);
    
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(0 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        SDL_GL_SwapWindow(window);
        
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
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


#include <shapes/aa_rect.hpp>
#include <mesh_data.hpp>
#include <mesh.hpp>
#include <texture_renderer.hpp>
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

    TextureRenderer texture_renderer=  TextureRenderer();
    // texture data rgba
    unsigned char texture_data_rgba[] = {
        255,0,0,255,     0,0,255,255,   0,255,0,255,
        0,255,0,255,     255,0,0,255,   0,0,255,255,
        0,0,255,255,     0,255,0,255,   255,0,0,255

    };
    texture_renderer.setTexture(GL_RGBA, 3, 3, GL_RGBA, GL_UNSIGNED_BYTE, &texture_data_rgba);
    
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
        AARect pos_size = AARect(glm::vec2(0.0f, 0.0f), glm::vec2(200.0f, 200.0f));
        AARect texture_area = AARect(glm::vec2(0.0f, 0.0f), glm::vec2(2.5f, 3.0f));
        texture_renderer.addSprite(pos_size, texture_area, glm::vec3(1.0f, 1.0f, 1.0f));
        
        // Render the texture
        glViewport(0, 0, 640, 480);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        texture_renderer.render();
        SDL_GL_SwapWindow(window);


      
        
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
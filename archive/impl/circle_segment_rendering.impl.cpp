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

#include <vector>

struct PolygonRenderer{
    GLuint program = 0, uniform_matrix = 0, vertex_buffer = 0, index_buffer = 0;
    std::vector<float> vertex_batch;
    std::vector<unsigned int> index_batch;
    unsigned int index_offset = 0;
    PolygonRenderer(){
        this->program = GLutils().makeProgram("./data/shaders/polygon_position_color.vert", "./data/shaders/polygon_position_color.frag");
        this->uniform_matrix = glGetUniformLocation(this->program, "u_view_mat");
        glGenBuffers(1, &this->vertex_buffer);
        glGenBuffers(1, &this->index_buffer);
        this->vertex_batch.clear();
        this->index_batch.clear();
        this->index_offset = 0;

    }
    void begin(){
        this->index_offset = 0;
    }
};



// Adds slice with the vertex format of "xyz rgb"
void addSlice(PolygonRenderer& polygon_renderer, float min_degrees, float max_degrees, float steps, float origin_x, float origin_y, float circle_radius){
    std::vector<float>& vertex_batch = polygon_renderer.vertex_batch;
    std::vector<unsigned int>& index_batch  = polygon_renderer.index_batch;
    unsigned int& index_offset = polygon_renderer.index_offset;
    vertex_batch.insert(vertex_batch.end(),{
        origin_x, origin_y, 0.0f, 1.0f, 1.0f, 1.0f,
    });
    
    for(float theta = min_degrees; theta <= max_degrees; theta += steps){
        theta = fminf(theta, max_degrees);
        float as_rad = (float)theta / 180.0f * M_PI;
        float cosine = cos(as_rad);
        float sine = sin(as_rad);
        vertex_batch.insert(vertex_batch.end(),{
            origin_x - cosine * circle_radius, origin_y + sine * circle_radius, 0.0f, 1.0f, 1.0f, 1.0f,
        });
    }
    int tri = ceilf((max_degrees - min_degrees) / steps);
    unsigned int start = index_offset;
    for(int i = 0; i < tri; i++){
        index_batch.insert(index_batch.end(), 
            {
                start, index_offset + 2, index_offset + 1,   
            }
        );
        polygon_renderer.index_offset += 1;
    }
    polygon_renderer.index_offset += 2;

}




// Adds arc with the vertex format of "xyz rgb"
void addArc(PolygonRenderer& polygon_renderer, float min_degrees, float max_degrees, float steps, float origin_x, float origin_y, float circle_radius, float mask_radius){
    std::vector<float>& vertex_batch = polygon_renderer.vertex_batch;
    std::vector<unsigned int>& index_batch  = polygon_renderer.index_batch;
    unsigned int& index_offset = polygon_renderer.index_offset;
    for(float theta = min_degrees; theta <= max_degrees; theta += steps){
        theta = fminf(theta, max_degrees);
        float as_rad = (float)theta / 180.0f * M_PI;
        float cosine = cos(as_rad);
        float sine = sin(as_rad);
        vertex_batch.insert(vertex_batch.end(),{
            origin_x - cosine * mask_radius, origin_y + sine * mask_radius, 0.0f, 1.0f, 1.0f, 1.0f,
            origin_x - cosine * circle_radius, origin_y + sine * circle_radius, 0.0f, 1.0f, 1.0f, 1.0f,
        });
    }
    int quads = ceilf((max_degrees - min_degrees) / steps);
    for(int i = 0; i < quads; i++){
        index_batch.insert(index_batch.end(), 
            {
                index_offset, index_offset + 2, index_offset + 1,   
                index_offset + 2, index_offset + 3, index_offset + 1
            }
        );
        index_offset += 2;
    }
    index_offset += 2;
}

void renderPolygonBatch(PolygonRenderer& polygon_renderer, glm::mat4 matrix){
    if(polygon_renderer.index_batch.size() > 0){
        glBindBuffer(GL_ARRAY_BUFFER, polygon_renderer.vertex_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, polygon_renderer.index_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * polygon_renderer.vertex_batch.size(), &polygon_renderer.vertex_batch.at(0), GL_DYNAMIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * polygon_renderer.index_batch.size(), &polygon_renderer.index_batch.at(0), GL_DYNAMIC_DRAW);

        glUseProgram(polygon_renderer.program);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(0 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glUniformMatrix4fv(polygon_renderer.uniform_matrix, 1, GL_FALSE, &matrix[0][0]);
        // draw the polygon   
        glDrawElements(GL_TRIANGLES, polygon_renderer.index_batch.size(), GL_UNSIGNED_INT, 0);
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
    io->IniFilename = NULL; // No init
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->ConfigWindowsMoveFromTitleBarOnly = true;
    ImGui::StyleColorsDark(NULL);
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 150");


    struct {
        float x = 200.0f, y = 200.0f;
        float inner_radius = 100.0f, outer_radius = 110.0f;
    } circle_arc;

    struct {
        int theta = 45;
    } segment;

    PolygonRenderer polygon_renderer = PolygonRenderer();
    glm::mat4 matrix = glm::ortho(0.0f, (float)width, (float)height, 0.0f);

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

        
        
        polygon_renderer.begin();
        addArc(polygon_renderer, 90.0f, 120.0f, 5.0f, 200.0f, 200.0f, 110.0f, 100.0f);
        addArc(polygon_renderer, 90.0f, 120.0f, 5.0f, 200.0f, 200.0f, 110.0f + 30.0f, 100.0f + 30.0f);
        addSlice(polygon_renderer, 0.0f, 90.0f, 45.0f, 400.0f, 200.0f, 110.0f);
        addSlice(polygon_renderer, 0.0f, 90.0f, 45.0f, 100.0f, 100.0f, 110.0f);


        glViewport(0, 0, 640, 480);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderPolygonBatch(polygon_renderer, matrix);
        
        SDL_GL_SwapWindow(window);

    }

    return 0;
}

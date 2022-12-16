#include <breakout_engine.hpp>

// void displayTable(ButtonState state, bool down){
//     std::string state_string = toString(state);
//     std::string bool_string = toString(down);
//     std::string new_state_string = toString(update(state, down));
//     std::cout << "state: " << state_string << "| down: " << bool_string << " | new state: " << new_state_string << "|\n";
// }

int main(int argc, char const *argv[])
{
    SDL_Window * window; // An **allocated reference** to the SDLWindow object that created, **on creation**
    SDL_GLContext gl_context; // To Store the SDL GLContext
    int opengl_major_version = 3, // To store the open gl major version
    opengl_minor_version = 3,
    width = 640, // this value id the current window width, it is initialised to the default
    height = 480; // this value id the current window height, it is initialised to the default; // To store the open gl minor version
    std::string window_name = "Test"; // The Window Name Which is initially set the breakout Game

     if(SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_SetWindowMinimumSize(window, width, height); // Set the window with tho current widht and height, which should be the same as the minimum
    if(window == NULL){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY); // This is required of the opengl versions are greater than or equal to 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, opengl_major_version); // GL version is a property
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, opengl_minor_version); // GL minor version us a property
    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);
    GLenum err = glewInit(); // Initialise glew

    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(1);
    }
    SDL_GL_MakeCurrent(window, gl_context);

    // {
    //     Rect rect = Rect(glm::vec2(0.0f, 0.0f), glm::vec2(128.0f, 128.0f));
    //     assert(rect.topLeft() == glm::vec2(0.0f, 0.0f));
    //     assert(rect.topRight() == glm::vec2(128.0f, 0.0f));
    //     assert(rect.bottomLeft() == glm::vec2(0.0f, 128.0f));
    //     assert(rect.bottomRight() == glm::vec2(128.0f, 128.0f));
    //     std::cout << toString(rect) << std::endl;
    // }

    
    // {
    //     VertexIndexBatch test_vertex_index_batch = VertexIndexBatch();
    //     Rect test_rect = Rect(glm::vec2(0.0f, 0.0f), glm::vec2(128.0f, 128.0f));
    //     glm::vec3 test_color = glm::vec3(1.0f, 0.0f, 0.0f);
    //     size_t expected_verticies_size = 24;
    //     size_t expected_indicies_size = 6;
    //     addRect(test_vertex_index_batch, test_rect, test_color);
    //     // Verify the first rectangle has been added correctly

    //     assert(test_vertex_index_batch.indicies.size() == 6);
    //     assert(test_vertex_index_batch.verticies.size() == expected_verticies_size);
    //     assert(test_vertex_index_batch.index_offset == 4);
    //     {
    //         float values[expected_verticies_size] = {
    //             0.0f, 128.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //             128.0f, 128.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //             128.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //             0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //         };
    //         bool values_match = true;
    //         for(size_t i = 0; i < expected_verticies_size; i++){
    //             values_match = values_match && (test_vertex_index_batch.verticies.at(i) == values[i]);
    //         }
    //         assert(values_match);
    //     }
    //     {
    //         bool values_match = true;
    //         unsigned int values[expected_indicies_size] = {
    //             0, 1, 2,
    //             0, 2, 3
    //         };
    //         for(size_t i = 0; i < expected_indicies_size; i++){
    //             values_match = values_match && (test_vertex_index_batch.indicies.at(i) == values[i]);
    //         }
    //         assert(values_match);
    //     }

    //     test_rect = Rect(glm::vec2(128.0f, 128.0f), glm::vec2(128.0f, 128.0f));
    //     test_color = glm::vec3(0.0f, 0.0f, 1.0f);
    //     // Verify that all following rect will be added correctly by induction
    //     expected_verticies_size = 48;
    //     expected_indicies_size = 12;

    //     addRect(test_vertex_index_batch, test_rect, test_color);
    //     assert(test_vertex_index_batch.indicies.size() == expected_indicies_size);
    //     assert(test_vertex_index_batch.verticies.size() == expected_verticies_size);
    //     assert(test_vertex_index_batch.index_offset == 8);

    //     {
    //         float values[expected_verticies_size] = {
    //             0.0f, 128.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //             128.0f, 128.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //             128.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //             0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    //             128.0f, 256.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    //             256.0f, 256.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    //             256.0f, 128.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    //             128.0f, 128.0f, 0.0f, 0.0f, 0.0f, 1.0f
    //         };
    //         bool values_match = true;

    //         for(size_t i = 0; i < expected_verticies_size; i++){
    //             values_match = values_match && (test_vertex_index_batch.verticies.at(i) == values[i]);
    //         }
    //         assert(values_match);
    //     }
    //     {
    //         bool values_match = true;
    //         unsigned int values[expected_indicies_size] = {
    //             0, 1, 2,
    //             0, 2, 3,

    //             4, 5, 6,
    //             4, 6, 7
    //         };
    //         for(size_t i = 0; i < expected_indicies_size; i++){
    //             values_match = values_match && (test_vertex_index_batch.indicies.at(i) == values[i]);
    //         }
    //         assert(values_match);
    //     }


    //     test_vertex_index_batch.clear();
    //     //Verify that the clear action worked correctly
    //     assert(test_vertex_index_batch.indicies.size() == 0);
    //     assert(test_vertex_index_batch.verticies.size() == 0);
    //     assert(test_vertex_index_batch.index_offset == 0);
    // }
    // {
    //     std::cout << "========Update Button State========\n";
    //     std::cout << "| Previous State | down | new state|\n";
    //     displayTable(ButtonState_Pressed, true);
    //     displayTable(ButtonState_Down, true);
    //     displayTable(ButtonState_Up, true);
    //     displayTable(ButtonState_Released, true);
    //     displayTable(ButtonState_Pressed, false);
    //     displayTable(ButtonState_Down, false);
    //     displayTable(ButtonState_Up, false);
    //     displayTable(ButtonState_Released, false);     

    // }
    // {
    //     std::cout << "========Cursor Construction Test========\n";

    //     Cursor cursor = Cursor();
    //     std::cout << toString(cursor) << std::endl;
    //     Cursor cursor1;
    //     std::cout << toString(cursor1) << std::endl;

    // }
    // {
    //     std::cout << "========Update Matrix Test========\n";
    //     glm::mat4 test_matrix;
    //     update(test_matrix, 640, 480);
    //     std::cout << glm::to_string(test_matrix) << std::endl;
    // }
    // {
    //     std::cout << "========Button To String Test========\n";
    //     Button a_button = Button(SDL_SCANCODE_A, "A Button");
    //     std::cout << "Button Test:===========" << std::endl;
    //     std::cout << toString(a_button) << std::endl;
    // }
    // {
    //     std::cout << "========Cursor To String Test========\n";

    //     Cursor cursor;
    //     cursor.position = glm::ivec2(40, 40);
    //     cursor.delta = glm::ivec2(-80, -20);

    //     std::cout << toString(cursor) << std::endl;
    // }
    // {
    //     std::cout << "========To String Test Vector Template========\n";
    //     glm::ivec2 int_vec2 = glm::ivec2(100, 40);
    //     glm::vec2 float_vec2 = glm::vec2(100.5f, 40.1f);
    //     std::cout << toString(int_vec2) << std::endl;
    //     std::cout << toString(float_vec2) << std::endl;
    // }
    {
        std::cout << "========update MeshDataTest========\n";
        Mesh test_mesh = Mesh();
        VertexIndexBatch test_vertex_index_batch;
        Rect test_rect = Rect(glm::vec2(0.0f, 0.0f), glm::vec2(128.0f, 128.0f));
        glm::vec3 test_color = glm::vec3(1.0f, 0.0f, 0.0f);
        addRect(test_vertex_index_batch, test_rect, test_color);
        addRect(test_vertex_index_batch, test_rect, test_color);
        update(test_mesh, test_vertex_index_batch);

        size_t float_count = 24;
        size_t unsigned_int_count = 6;
        float expected_verticies[float_count] = {
            0.0f, 128.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            128.0f, 128.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            128.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        };

        unsigned int expected_indicies[6] = {
            0, 1, 2,
            0, 2, 3
        };

        float vertex_read_data[float_count];
        glBindBuffer(GL_ARRAY_BUFFER, test_mesh.vertex_buffer);
        glGetBufferSubData(GL_ARRAY_BUFFER, 0, float_count * sizeof(float), vertex_read_data);
        std::cout << "------For Verticies ------"<< std::endl;
        for(size_t i = 0; i < float_count; i++){
            std::cout << "i: " << i << " expected: " << expected_verticies[i] << " actual: " << vertex_read_data[i] << std::endl;
            assert(expected_verticies[i] == vertex_read_data[i]);
        }

        unsigned int index_read_data[unsigned_int_count];
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, test_mesh.index_buffer);
        glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, unsigned_int_count * sizeof(unsigned int), index_read_data);
        std::cout << "------For Indicies ------"<< std::endl;
        for(size_t i = 0; i < unsigned_int_count; i++){
            std::cout << "i: " << i << " expected: " << expected_indicies[i] << " actual: " << index_read_data[i] << std::endl;
            assert(expected_indicies[i] == index_read_data[i]);
        }
    
    }
    {
        std::cout << "------Make Program test 1------"<< std::endl;
        GLuint result_program = makeProgram("data\\shaders\\polygon_position_color.vert", "data\\shaders\\polygon_position_color.frag");
        assert(result_program != 0);
    }
    {
        std::cout << "------Make Program test 2------"<< std::endl;
        GLuint vertex_shader = makeShader(GL_VERTEX_SHADER, "data\\shaders\\polygon_position_color.vert");
        GLuint fragment_shader = makeShader(GL_FRAGMENT_SHADER, "data\\shaders\\polygon_position_color.frag");
        GLuint result_program = makeProgram(vertex_shader, fragment_shader);
        assert(result_program != 0);
        {
            GLint delete_status;
            glGetShaderiv(vertex_shader, GL_DELETE_STATUS, &delete_status);
            assert(delete_status ==  GL_TRUE);

        }
        {
            GLint delete_status;
            glGetShaderiv(fragment_shader, GL_DELETE_STATUS, &delete_status);
            assert(delete_status ==  GL_TRUE);
            
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

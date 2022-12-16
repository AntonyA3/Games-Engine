/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose */
#define __BASE_FILE__ "C:\\Users\\anton\\DEV\\Games-Engine\\src\\breakout_game_test.impl.cpp"
#include <iostream>
#include <breakout_engine.hpp>

#include <exotic/cester.h>

CESTER_TEST(test_that_glew_init_works_in_this_environment, test_instance,
    
      
    SDL_Window * window; // An **allocated reference** to the SDLWindow object that created, **on creation**
    SDL_GLContext gl_context; // To Store the SDL GLContext
    std::string window_name = "Test"; // The Window Name Which is initially set the breakout Game
    int default_width = 640, // The default width were this should be the window width at begining of application
    default_height = 480, // The default height were this should be the window height at begining of application
    width = default_width, // this value id the current window width, it is initialised to the default
    height = default_height, // this value id the current window height, it is initialised to the default
    opengl_major_version = 3, // To store the open gl major version
    opengl_minor_version = 3; // To store the open gl minor version

    
    if(SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    cester_assert_true_msg(true, "SDL Initialised successfully");
    window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    cester_assert_not_equal(NULL, window);
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

    GLenum err = glewInit();  
    cester_assert_equal (err, GLEW_OK);
    SDL_DestroyWindow(window);
    SDL_Quit();
)

// CESTER_TEST(CommonSDLOpenGL_BasicSDLOpengl_cleanup_test, test_instance,
  
    
// )


// CESTER_TEST(BasicSDLOpengl_initialise_test, test_instance,
  
//     BasicSDLOpenGLTest test_object;
//     test_object.initialise();
//     cester_assert_not_equal(NULL, test_object.window);
//     cester_assert_not_equal(NULL, test_object.gl_context);
//     int attrib;
//     SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &attrib);
//     cester_assert_equal(SDL_GL_CONTEXT_PROFILE_COMPATIBILITY, attrib);

//     SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &attrib);
//     cester_assert_equal(3, attrib);

//     SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &attrib);
//     cester_assert_equal(3, attrib);
// )

CESTER_TEST(are_string_equality_tests_valid, test_instance,
    std::string s0 = "Hello World";
    std::string s1 = "Hello World";

    cester_assert_equal(s0, s1);
)

CESTER_TEST(rect_test, test_instance, 
    
    Rect rect = Rect(glm::vec2(0.0f, 0.0f), glm::vec2(128.0f, 128.0f));
    cester_assert_equal(rect.topLeft(), glm::vec2(0.0f, 0.0f));
    cester_assert_equal(rect.topRight(), glm::vec2(128.0f, 0.0f));
    cester_assert_equal(rect.bottomLeft(), glm::vec2(0.0f, 128.0f));
    cester_assert_equal(rect.bottomRight(), glm::vec2(128.0f, 128.0f));
    std::cout << toString(rect) << std::endl;
)


CESTER_TEST(vertex_index_batch_add_rect_test_first_rect, test_instance,
    VertexIndexBatch test_vertex_index_batch = VertexIndexBatch();
    Rect test_rect = Rect(glm::vec2(0.0f, 0.0f), glm::vec2(128.0f, 128.0f));
    glm::vec3 test_color = glm::vec3(1.0f, 0.0f, 0.0f);
    size_t expected_verticies_size = 24;
    size_t expected_indicies_size = 6;
    addRect(test_vertex_index_batch, test_rect, test_color);
    // Verify the first rectangle has been added correctly

    cester_assert_equal(test_vertex_index_batch.indicies.size(), 6);
    cester_assert_equal(test_vertex_index_batch.verticies.size(), expected_verticies_size);
    cester_assert_equal(test_vertex_index_batch.index_offset, 4);
    {
        float values[expected_verticies_size] = {
            0.0f, 128.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            128.0f, 128.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            128.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        };
        for(size_t i = 0; i < expected_verticies_size; i++){
            cester_assert_equal(test_vertex_index_batch.verticies.at(i), values[i]);
        }
    }
    {
        unsigned int values[expected_indicies_size] = {
            0, 1, 2,
            0, 2, 3
        };
        for(size_t i = 0; i < expected_indicies_size; i++){
            cester_assert_equal(test_vertex_index_batch.indicies.at(i), values[i]);
        }
    } 
)

CESTER_TEST(vertex_index_batch_add_rect_test_second_rect, test_instance,
    VertexIndexBatch test_vertex_index_batch = VertexIndexBatch();
    Rect test_rect = Rect(glm::vec2(0.0f, 0.0f), glm::vec2(128.0f, 128.0f));
    glm::vec3 test_color = glm::vec3(1.0f, 0.0f, 0.0f);
    size_t expected_verticies_size = 24;
    size_t expected_indicies_size = 6;
    addRect(test_vertex_index_batch, test_rect, test_color);
    // Verify the first rectangle has been added correctly

    test_rect = Rect(glm::vec2(128.0f, 128.0f), glm::vec2(128.0f, 128.0f));
    test_color = glm::vec3(0.0f, 0.0f, 1.0f);
    // Verify that all following rect will be added correctly by induction
    expected_verticies_size = 48;
    expected_indicies_size = 12;

    addRect(test_vertex_index_batch, test_rect, test_color);
    cester_assert_equal(test_vertex_index_batch.indicies.size(), expected_indicies_size);
    cester_assert_equal(test_vertex_index_batch.verticies.size(), expected_verticies_size);
    cester_assert_equal(test_vertex_index_batch.index_offset, 8);

    {
        float values[expected_verticies_size] = {
            0.0f, 128.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            128.0f, 128.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            128.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            128.0f, 256.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            256.0f, 256.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            256.0f, 128.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            128.0f, 128.0f, 0.0f, 0.0f, 0.0f, 1.0f
        };
        for(size_t i = 0; i < expected_verticies_size; i++){
            cester_assert_equal(test_vertex_index_batch.verticies.at(i), values[i]);
        }
    }
    {
        unsigned int values[expected_indicies_size] = {
            0, 1, 2,
            0, 2, 3,

            4, 5, 6,
            4, 6, 7
        };
        for(size_t i = 0; i < expected_indicies_size; i++){
            cester_assert_equal(test_vertex_index_batch.indicies.at(i), values[i]);
        }
    }


 
)
CESTER_TEST(vertex_index_clear_test, test_instance,
    VertexIndexBatch test_vertex_index_batch = VertexIndexBatch();
    Rect test_rect = Rect(glm::vec2(0.0f, 0.0f), glm::vec2(128.0f, 128.0f));
    glm::vec3 test_color = glm::vec3(1.0f, 0.0f, 0.0f);
    addRect(test_vertex_index_batch, test_rect, test_color);
    test_vertex_index_batch.clear();
    //Verify that the clear action worked correctly
    cester_assert_equal(test_vertex_index_batch.indicies.size(), 0);
    cester_assert_equal(test_vertex_index_batch.verticies.size(), 0);
    cester_assert_equal(test_vertex_index_batch.index_offset, 0);

)


CESTER_TEST(cursor_constructor_test, test_instance,
    std::cout << "========Cursor Construction Test========\n";
    Cursor cursor = Cursor();
    cester_assert_equal(cursor.position.x, 0);
    cester_assert_equal(cursor.position.y, 0);
    cester_assert_equal(cursor.delta.x, 0);
    cester_assert_equal(cursor.delta.y, 0);
)

CESTER_TEST(to_string_cursor_tests_base_case, test_instance,
    std::cout << "========Cursor To String Test========\n";
    Cursor cursor = Cursor();
    std::string result_string = toString(cursor);
    std::string expected_string = readFile("src\\test_data_cursor_to_string.txt");
    cester_assert_equal(expected_string, result_string );
)
CESTER_TEST(to_string_cursor_tests_other_case, test_instance,

    std::cout << "========Cursor To String Test========\n";

    Cursor cursor;
    cursor.position = glm::ivec2(40, 40);
    cursor.delta = glm::ivec2(-80, -20);
    std::cout << toString(cursor) << std::endl;
    std::string result_string = toString(cursor);
    std::string expected_string = readFile("src\\test_data_cursor_to_string_other_cases.txt");
    cester_assert_equal(expected_string, result_string );
)
    
CESTER_TEST(update_matrix_test, test_instance,
    std::cout << "========Update Matrix Test========\n";
    glm::mat4 test_matrix;
    update(test_matrix, 640, 480);
    float expected_matrix[4][4] = {
        {1.0f / 640.0f * 2.0f, 0.0f, 0.0f, 0.0f},
        {0, -(1.0f / 480.0f * 2.0f), 0.0f, 0.0f},
        {0.0f, 0.0f, -1.0f, 0.0f},
        {-1.0f, 1.0f, 0.0f, 1.0f}
    };

    for(size_t i = 0; i < 4; i++){
        for(size_t j = 0; j < 4; j++){
            cester_assert_equal(expected_matrix[i][j], test_matrix[i][j]);
        }
    }
)

CESTER_TEST(to_string_button_test, test_instance,
    std::cout << "========Button To String Test========\n";
    Button button = Button(SDL_SCANCODE_A, "A Button");
    std::string result_string = toString(button);
    std::string expected_string = readFile("src\\tests_data_button_to_string.txt");
    cester_assert_equal( readFile("src\\tests_data_button_to_string.txt"), result_string); 
)


CESTER_TEST(button_state_test_exhaustive, test_instance,
    std::cout << "========Update Button State========\n";
    cester_assert_equal(ButtonState_Down, update(ButtonState_Pressed, true));
    cester_assert_equal(ButtonState_Down, update(ButtonState_Down, true));
    cester_assert_equal(ButtonState_Pressed, update(ButtonState_Up, true));
    cester_assert_equal(ButtonState_Pressed, update(ButtonState_Released, true));
    cester_assert_equal(ButtonState_Released, update(ButtonState_Pressed, false));
    cester_assert_equal(ButtonState_Released, update(ButtonState_Down, false));
    cester_assert_equal(ButtonState_Up, update(ButtonState_Up, false));
    cester_assert_equal(ButtonState_Up, update(ButtonState_Released, false));
)

CESTER_TEST(to_string_vector_template_case_ivec2_test, test_instance,
    glm::ivec2 int_vec2 = glm::ivec2(100, 40);
    cester_assert_equal(readFile("src\\test_data_to_string_vector_template_case_ivec2_test.txt"), toString(int_vec2));

)

CESTER_TEST(to_string_vector_template_case_vec2_test, test_instance,
    glm::vec2 float_vec2 = glm::vec2(100.5f, 40.1f);
    cester_assert_equal(readFile("src\\test_data_to_string_vector_template_case_vec2_test.txt"), toString(float_vec2));
)

#ifndef TEST_DATA_DIRECTORY
#define TEST_DATA_DIRECTORY "./tests/data/"
#endif

#define GLEW_STATIC
#include <GL/glew.h>

#define SDL_MAIN_HANDLED
#include <exotic/cester.h>
#include <loader/program_loader.hpp>
#include <GL/glew.h>
#include <iostream>

/*
    GIVEN a valid vertex file
    AND a valid  fragment file
    AND and shaders should be deleted
    AFTER Loading the program
    EXPECT program to not be 0
    EXPECT program status to be true
    EXPECT vertex shader load status to be true
    EXPECT fragment shader load status to be true

*/
CESTER_TEST(load_with_valid_vertex_shader_and_fragment_shader, inst,
    std::string vertex_file = std::string(TEST_DATA_DIRECTORY) + "polygon_position_color.vert";
    std::string fragment_file = std::string(TEST_DATA_DIRECTORY) + "polygon_position_color.frag";
    ProgramLoader program_loader;
    program_loader.load(vertex_file, fragment_file,true);

    cester_assert_uint_ne(0, program_loader.m_program);
    cester_assert_true(program_loader.m_status == GL_TRUE);
    cester_assert_true(program_loader.m_vertex_shader_content.m_status == GL_TRUE);
    cester_assert_true(program_loader.m_fragment_shader_content.m_status == GL_TRUE);
)

/*
    GIVEN an invalid vertex file
    AND a valid fragment file
    AND and shaders should be deleted
    AFTER Loading the program
    EXPECT program to not be 0
    EXPECT program status to be false
    EXPECT vertex shader load status to be false
    EXPECT fragment shader load status to be true
*/
CESTER_TEST(load_with_valid_vertex_shader_and_fragment_shader, inst,
    std::string vertex_file = "failed";
    std::string fragment_file = "data/shaders/polygon_position_color.frag";
    ProgramLoader program_loader;
    program_loader.load(vertex_file, fragment_file ,true);
    cester_assert_uint_ne(0, program_loader.m_program);
    cester_assert_true(program_loader.m_status == GL_TRUE);
    cester_assert_false(program_loader.m_vertex_shader_content.m_status == GL_TRUE);
    cester_assert_true(program_loader.m_fragment_shader_content.m_status == GL_TRUE);
)


/*
    GIVEN a valid vertex file
    AND a valid  fragment file
    AND and shaders should be deleted
    AFTER Loading the program Twice
    EXPECT program to not be 0
    EXPECT program status to be true
    EXPECT vertex shader load status to be true
    EXPECT fragment shader load status to be true

*/
CESTER_TEST(double_loading_program, inst,
    std::string vertex_file = "data/shaders/polygon_position_color.vert";
    std::string fragment_file = "data/shaders/polygon_position_color.frag";
    ProgramLoader program_loader;
    program_loader.load(vertex_file, fragment_file ,true);
    program_loader.load(vertex_file, fragment_file ,true);

    cester_assert_uint_ne(0, program_loader.m_program);
    cester_assert_true(program_loader.m_status == GL_TRUE);
    cester_assert_true(program_loader.m_vertex_shader_content.m_status == GL_TRUE);
    cester_assert_true(program_loader.m_fragment_shader_content.m_status == GL_TRUE);
)



#ifndef GAMES_ENGINE_PROGRAM_LOADER
#define GAMES_ENGINE_PROGRAM_LOADER
#include <GL/glew.h>
#include <string>
#include <loader/shader_loader.hpp>

struct ProgramLoader
{
    GLuint m_program;
    ShaderLoader m_vertex_shader_content;
    ShaderLoader m_fragment_shader_content;
    int m_status;
    std::string m_info_log;

    /*
        INPUT vertex_file path
        INPUT fragment file path
        INPUT should shaders be deleted?
        INITIALISE info log array
        LOAD vertex shader
        LOAD fragment shader
        CREATE Shader program
        ATTACH vertex shader to program
        ATTACH fragment shader to program
        LINK the program
        SET status of the program linking
        SET info related to the program linking
        IF shaders should be deleted
            DELETE vertex shader
            DELETE fragment shader
    */
    void load(std::string vertex_shader_file, std::string fragment_shader_file, bool deleteShaders);
};
#endif
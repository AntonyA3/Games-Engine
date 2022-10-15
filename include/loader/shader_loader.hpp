#ifndef GAMES_ENGINE_SHADER_LOADER
#define GAMES_ENGINE_SHADER_LOADER
#include <GL/glew.h>
#include <loader/file_reader.hpp>
#include <iostream>

struct ShaderLoader{
    GLuint m_shader;
    FileReader m_file_reader;
    int m_status;
    GLuint m_content;
    std::string m_info_log;

    void load(std::string filename, GLint shader_type);
};

#endif
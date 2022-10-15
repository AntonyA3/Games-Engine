#include <loader/program_loader.hpp>



void ProgramLoader::load(std::string vertex_shader_file, std::string fragment_shader_file, bool deleteShaders = true){
    GLchar info_log[1000]; 
    m_vertex_shader_content.load(vertex_shader_file, GL_VERTEX_SHADER);
    m_fragment_shader_content.load(fragment_shader_file, GL_FRAGMENT_SHADER);

    m_program = glCreateProgram();
    glAttachShader(m_program, m_vertex_shader_content.m_shader);
    glAttachShader(m_program, m_fragment_shader_content.m_shader);
    glLinkProgram(m_program);
    glGetProgramiv(m_program, GL_LINK_STATUS, &m_status);
    glGetProgramInfoLog(m_program, 1000, NULL, &info_log[0]);
    m_info_log = std::string(info_log);
    if(deleteShaders){
        glDeleteShader(m_vertex_shader_content.m_shader);
        glDeleteShader(m_fragment_shader_content.m_shader);
    }
}
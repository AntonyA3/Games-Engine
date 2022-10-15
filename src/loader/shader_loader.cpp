#include <loader/shader_loader.hpp>

void ShaderLoader::load(std::string filename, GLint shader_type){
    GLchar info_log[1000];
    m_shader = glCreateShader(shader_type);
    m_file_reader.read(filename);
    const char * shader_src = m_file_reader.m_content.c_str();
    glShaderSource(m_shader, 1, &shader_src, NULL);
    glCompileShader(m_shader);
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &m_status);
    glGetShaderInfoLog(m_shader, 1000, NULL, &info_log[0]);
    m_info_log = std::string(info_log);

}
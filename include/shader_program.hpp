
#ifndef GAMES_ENGINE_SHADER_PROGRAM
#define GAMES_ENGINE_SHADER_PROGRAM
#include <vector>
#include <GL/glew.h>
#include <vertex_attribute_data.hpp>
#include <shader_program_data.hpp>
#include <loader/program_loader.hpp>
struct ShaderProgram
{
    GLuint m_program, m_uniform_matrix_location;
    std::vector<VertexAttributeData> m_vertex_attributes;
    int m_vertex_size;
    void create(ShaderProgramData &shader_program_data);

    void use();
    void setMatrix(float * matrix);
    void enableVertexAttributes();
};

#endif
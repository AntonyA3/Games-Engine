
#ifndef GAMES_ENGINE_SHADER_PROGRAM
#define GAMES_ENGINE_SHADER_PROGRAM
#include <vector>
#include <GL/glew.h>
#include <vertex_attribute_data.hpp>
#include <shader_program_data.hpp>
struct ShaderProgram
{
    GLuint m_program, m_uniform_matrix_location;
    std::vector<VertexAttributeData> m_vertex_attributes;
    int m_vertex_size;
    
    void create(GLuint program, std::vector<VertexAttributeData> attributes);
    void use();
    void setMatrix(float * matrix);
};

#endif
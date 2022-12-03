#include <shader_program.hpp>


void ShaderProgram::create(GLuint program, std::vector<VertexAttributeData> attributes){
    m_program = program;
    m_vertex_attributes = attributes;

    m_uniform_matrix_location = glGetUniformLocation(m_program, "u_view_mat");
    m_vertex_size = 0;
    for(int i = 0; i < attributes.size(); i++){
        m_vertex_size += attributes.at(i).size;
    }
}

void ShaderProgram::use(){
    glUseProgram(m_program);
    int vertex_offset = 0;
    for(int i = 0; i < m_vertex_attributes.size(); i++){
        VertexAttributeData& vertex_attribute_data = m_vertex_attributes.at(i);
        glVertexAttribPointer(i, vertex_attribute_data.size, GL_FLOAT, GL_FALSE, m_vertex_size * sizeof(float), (void *)(vertex_offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        vertex_offset += vertex_attribute_data.size;
    }   
}

void ShaderProgram::setMatrix(float * matrix){
    glUniformMatrix4fv(m_uniform_matrix_location, 1, GL_FALSE, matrix);
}


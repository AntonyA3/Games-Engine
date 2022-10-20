#include <shader_program.hpp>


void ShaderProgram::create(ShaderProgramData &shader_program_data){
    ProgramLoader program_loader;
    program_loader.load(shader_program_data.vertex_file, shader_program_data.fragment_file, true);
    m_vertex_attributes = shader_program_data.vertex_attributes;

    m_program = program_loader.m_program;
    m_uniform_matrix_location = glGetUniformLocation(m_program, "u_view_mat");
    m_vertex_size = 0;
    for(int i = 0; i < shader_program_data.vertex_attributes.size(); i++){
        m_vertex_size += shader_program_data.vertex_attributes.at(i).size;
    }
}


void ShaderProgram::use(){
    glUseProgram(m_program);
}

void ShaderProgram::setMatrix(float * matrix){
    glUniformMatrix4fv(m_uniform_matrix_location, 1, GL_FALSE, matrix);
}

void ShaderProgram::enableVertexAttributes(){
    int vertex_offset = 0;
    for(int i = 0; i < m_vertex_attributes.size(); i++){
        VertexAttributeData& vertex_attribute_data = m_vertex_attributes.at(i);
        glVertexAttribPointer(i, vertex_attribute_data.size, GL_FLOAT, GL_FALSE, m_vertex_size * sizeof(float), (void *)(vertex_offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        vertex_offset += vertex_attribute_data.size;
    }     
}
#include <mesh.hpp>

void Mesh::create(){
    glGenBuffers(1, &m_vertex_buffer);
    glGenBuffers(1, &m_index_buffer);
}

void Mesh::bind(){
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
}

void Mesh::setData(float * vertex_array, int float_count, unsigned int * index_array, int index_count){
    this->bind();
    m_index_count = index_count;
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * float_count, vertex_array, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * index_count, index_array, GL_DYNAMIC_DRAW);
}

void Mesh::setData(MeshData& mesh_data){
    this->setData(
        &mesh_data.m_vertex_array.at(0), mesh_data.m_vertex_array.size(),
        &mesh_data.m_index_array.at(0), mesh_data.m_index_array.size()
    );
}


void Mesh::draw(){
    glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0);
}
#include <mesh.hpp>



void Mesh::create(){
    glGenBuffers(1, &m_vertex_buffer);
    glGenBuffers(1, &m_index_buffer);
}

void Mesh::bind(){
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
}

void Mesh::draw(){
    glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0);

}
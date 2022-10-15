#include <mesh_generator.hpp>

void MeshGenerator::generate(Mesh& mesh, float * vertex_array, int float_count, unsigned int * index_array, int index_count){
    mesh.m_index_count = index_count;
    glBindBuffer(GL_ARRAY_BUFFER, mesh.m_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * float_count, vertex_array, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.m_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * index_count, index_array, GL_DYNAMIC_DRAW);

}

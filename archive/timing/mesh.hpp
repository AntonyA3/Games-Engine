#ifndef GAMES_ENGINE_MESH_HPP
#define GAMES_ENGINE_MESH_HPP
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <mesh_data.hpp>
struct Mesh
{
    GLuint m_vertex_buffer, // Stores the vertex buffer of the mesh
    m_index_buffer; // Stores the index buffer of the mesh
    int m_index_count;
    void create();
    void bind(); // Binds both the vertex buffer and the index buffer of the mesh
    void setData(float * vertex_array, int float_count, unsigned int * index_array, int index_count);
    void setData(MeshData& mesh_data);

    void draw();
};

#endif
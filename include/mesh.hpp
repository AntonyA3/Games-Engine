#ifndef GAMES_ENGINE_MESH_HPP
#define GAMES_ENGINE_MESH_HPP
#include <GL/glew.h>
#include <glm/glm.hpp>
struct Mesh
{
    GLuint m_vertex_buffer, m_index_buffer;
    int m_index_count;
    void create();
    void bind();
    void setData(float * vertex_array, int float_count, unsigned int * index_array, int index_count);
    void draw();
};

#endif
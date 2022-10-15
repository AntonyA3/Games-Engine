#ifndef GAMES_ENGINE_MESH_HPP
#define GAMES_ENGINE_MESH_HPP
#include <GL/glew.h>
#include <glm/glm.hpp>
struct Mesh
{
    GLuint m_vertex_buffer, m_index_buffer;
    int m_index_count;
    glm::mat4 m_matrix = glm::mat4(1.0f);

    void create();
    void bind();
    void draw();
};

#endif
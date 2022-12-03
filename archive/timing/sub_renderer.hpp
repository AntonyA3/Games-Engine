#ifndef GAMES_ENGINE_SUB_RENDERER_HPP
#define GAMES_ENGINE_SUB_RENDERER_HPP
#include <glutils.hpp>
#include <glm/glm.hpp>
#include <mesh_data.hpp>
#include <mesh.hpp>
#include <shader_program.hpp>
#include <vertex_attribute_data.hpp>
struct  SubRenderer{
    MeshData m_mesh_data;
    Mesh m_mesh;
    ShaderProgram m_shader_program;
    glm::mat4 m_matrix;


    void create(std::string vertex_file, std::string fragment_file, std::vector<VertexAttributeData> vertex_attributes);
    void begin();
    void setMatrix(glm::mat4 matrix);
    void render();

    protected:
    MeshData& refMeshData();
};

#endif
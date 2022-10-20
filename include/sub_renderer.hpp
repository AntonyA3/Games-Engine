#ifndef GAMES_ENGINE_SUB_RENDERER_HPP
#define GAMES_ENGINE_SUB_RENDERER_HPP
#include <shader_program.hpp>
#include <aa_rect.hpp>
#include <mesh.hpp>
#include <mesh_data_converter.hpp>
#include <glm/gtx/string_cast.hpp>
#include <sub_renderer_data.hpp>
struct SubRenderer
{
    MeshDataConverter m_mesh_data_converter;
    ShaderProgram m_shader_program;
    Mesh m_mesh;
    glm::mat4 m_matrix;
    void create(SubRendererData &sub_renderer_data);
    void begin();
    void addRect(AARect& rect);
    void addRectWithPositionColorTextureCoordinates(AARect& rect);
    void setMatrix(glm::mat4 matrix);
    void render();

};
#endif
#ifndef GAMES_ENGINE_MESH_FROM_RECTANGLE
#define GAMES_ENGINE_MESH_FROM_RECTANGLE

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <iostream>

#include <mesh.hpp>
#include <mesh_generator.hpp>
#include <mesh_data_converter.hpp>
#include <shapes/aa_rect.hpp>
struct MeshFromRectangle
{
    MeshGenerator mesh_generator;
    MeshDataConverter m_mesh_data_converter;
    Mesh generate(AARect& rectangle);
};

#endif
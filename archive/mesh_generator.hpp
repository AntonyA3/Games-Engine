#ifndef GAMES_ENGINE_MESH_GENERATOR_HPP
#define GAMES_ENGINE_MESH_GENERATOR_HPP
#include <mesh.hpp>
struct MeshGenerator
{
    void generate(Mesh& mesh, float * vertex_array, int float_count, unsigned int * index_array, int index_count);
};
#endif

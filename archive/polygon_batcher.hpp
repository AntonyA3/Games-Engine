#ifndef GAMES_ENGINE_POLYGON_BATCHER
#define GAMES_ENGINE_POLYGON_BATCHER

#include <vector>
#include <shapes/aa_rect.hpp>
#include <mesh_data_converter.hpp>
struct PolygonBatcher
{
    std::vector<float> m_vertex_array;
    std::vector<unsigned int> m_index_array;
    unsigned int m_index_offset;
    MeshDataConverter m_mesh_data_converter;

    void clear();
    void addRect(AARect& rect);
};
#endif
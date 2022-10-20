
#include <polygon_batcher.hpp>

void PolygonBatcher::clear(){
    m_vertex_array.clear();
    m_index_array.clear();
    m_index_offset = 0;
}

void PolygonBatcher::addRect(AARect& rect){
    m_mesh_data_converter.generate(rect, m_index_offset);
    m_vertex_array.insert(
        m_vertex_array.end(), 
        m_mesh_data_converter.m_vertex_array.begin(),
        m_mesh_data_converter.m_vertex_array.end()
    );

    m_index_array.insert(
        m_index_array.end(), 
        m_mesh_data_converter.m_index_array.begin(),
        m_mesh_data_converter.m_index_array.end()
    );

    m_index_offset += 4;
}


#include <mesh_from_rectangle.hpp>

Mesh MeshFromRectangle::generate(AARect& rectangle){
    Mesh out_mesh;
    out_mesh.create();
    m_mesh_data_converter.generate(rectangle);
    mesh_generator.generate(
        out_mesh, 
        &m_mesh_data_converter.m_vertex_array.at(0),
        m_mesh_data_converter.m_vertex_array.size(),
        &m_mesh_data_converter.m_index_array.at(0),
        m_mesh_data_converter.m_index_array.size()
    );
    return out_mesh;
    
}
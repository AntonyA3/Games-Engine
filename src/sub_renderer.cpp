#include <sub_renderer.hpp>



void SubRenderer::create(SubRendererData &sub_renderer_data){    
    m_mesh.create();
    m_mesh_data_converter.create();
    m_shader_program.create(sub_renderer_data.shader_program_data);
}

/*
    CLEAR MESH DATA GENERATOR
*/
void SubRenderer::begin(){
    m_mesh_data_converter.clear();
}

void SubRenderer::addRect(AARect& rect){
    m_mesh_data_converter.generate(rect);
}

void SubRenderer::addRectWithPositionColorTextureCoordinates(AARect& rect){
    m_mesh_data_converter.generateRectWithColorAndUnitCoords(rect);
}

void SubRenderer::setMatrix(glm::mat4 matrix){
    m_matrix = matrix;
}

void SubRenderer::render(){
    if( m_mesh_data_converter.m_index_array.size() > 0){
        m_mesh.setData(
            &m_mesh_data_converter.m_vertex_array.at(0),
            m_mesh_data_converter.m_vertex_array.size(),
            &m_mesh_data_converter.m_index_array.at(0),
            m_mesh_data_converter.m_index_array.size()
        );    
        m_shader_program.use();
        m_mesh.bind();
        m_shader_program.enableVertexAttributes();
        m_shader_program.setMatrix(&m_matrix[0][0]);        
        m_mesh.draw();
    }
}
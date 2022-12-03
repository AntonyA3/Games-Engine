#include <sub_renderer.hpp>

void SubRenderer::create(std::string vertex_file, std::string fragment_file, std::vector<VertexAttributeData> vertex_attributes){
    GLuint program = GLutils().makeProgram(vertex_file, fragment_file);
    m_shader_program.create(program, vertex_attributes);
    m_mesh.create();
    m_mesh_data.create();
}

void SubRenderer::begin(){
    m_mesh_data.clear();
}


MeshData& SubRenderer::refMeshData(){
    return m_mesh_data;
}

void SubRenderer::setMatrix(glm::mat4 matrix){
    m_matrix = matrix;
}

void SubRenderer::render(){
    if(m_mesh_data.getIndexData().size() > 0){
        m_mesh.setData(
            &m_mesh_data.getVertexData().at(0),
            m_mesh_data.getVertexData().size(),
            &m_mesh_data.getIndexData().at(0),
            m_mesh_data.getIndexData().size()
        );    
        m_mesh.bind();        
        m_shader_program.use();
        m_shader_program.setMatrix(&m_matrix[0][0]);        
        m_mesh.draw();
    }
}
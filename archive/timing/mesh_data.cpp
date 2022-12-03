#include <mesh_data.hpp>


MeshData::MeshData(){
    this->create();
}

void MeshData::create(){
    clear();
}

void MeshData::pushRectOfColor(AARect& rectangle, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f)){
    RectVerticies rect_verticies;
    rect_verticies.create(rectangle);
    this->pushPosition(rect_verticies.bottom_left );
    this->pushColor(color);
    this->pushPosition( rect_verticies.bottom_right );
    this->pushColor(color);
    this->pushPosition(rect_verticies.top_right);
    this->pushColor(color);
    this->pushPosition(rect_verticies.top_left);
    this->pushColor(color);
    this->generateRectIndicies();
}

void MeshData::pushPolygonOfColor(Polygon& polygon, glm::vec3 color){
    std::vector<glm::vec2>& verticies = polygon.getVerticies();
    for(int i = 0; i < verticies.size(); i++){
        this->pushPosition(glm::vec3(verticies.at(i), 0.0f));
        this->pushColor(color);
    }
    
    for(unsigned int i = 0; i < verticies.size() - 1; i++){
        this->m_index_array.insert(this->m_index_array.end(),{
            i + m_index_offset,
            i + 1 + m_index_offset,
            m_index_offset
        });
    }
    m_index_offset +=  verticies.size();


}


void MeshData::clear(){
    m_vertex_array.clear();
    m_index_array.clear();
    m_index_offset = 0;
}

void MeshData::pushRectOfColorAndAreaUnit(AARect rectangle, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f)){
    RectVerticies rect_verticies;
    rect_verticies.create(rectangle);
    this->pushPosition(rect_verticies.bottom_left );
    this->pushColor(color);
    this->pushTextureCoordinates(glm::vec2(-1.0f, 1.0f));
    this->pushPosition( rect_verticies.bottom_right );
    this->pushColor(color);
    this->pushTextureCoordinates(glm::vec2(1.0f, 1.0f));
    this->pushPosition(rect_verticies.top_right);
    this->pushColor(color);
    this->pushTextureCoordinates(glm::vec2(1.0f, -1.0f));
    this->pushPosition(rect_verticies.top_left);
    this->pushColor(color);
    this->pushTextureCoordinates(glm::vec2(-1.0f, -1.0f));
    this->generateRectIndicies();
}

void MeshData::generateRectIndicies(){
    unsigned int indicies[6] ={
        0, 1, 2,
        0, 2, 3
    };
    for(int i = 0; i < 6; i++){
        m_index_array.push_back(indicies[i] + m_index_offset) ;
    }
    m_index_offset += 4;
}

void MeshData::pushPosition(glm::vec3 position){
    m_vertex_array.insert(m_vertex_array.end(),{
        position.x, position.y, position.z
    });
}

void MeshData::pushColor(glm::vec3 color){
    m_vertex_array.insert(m_vertex_array.end(),{
        color.x, color.y, color.z
    });
}

void MeshData::pushTextureCoordinates(glm::vec2 coords){
    m_vertex_array.insert(m_vertex_array.end(),{
        coords.x, coords.y
    });
}

std::vector<float>& MeshData::getVertexData(){
    return m_vertex_array;
}

std::vector<unsigned int>& MeshData::getIndexData(){
    return m_index_array;
}
    

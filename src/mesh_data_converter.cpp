#include <mesh_data_converter.hpp>

void MeshDataConverter::create(){
    m_index_offset = 0;
}

void MeshDataConverter::generate(AARect& rectangle){
    MeshDataConverter::RectVerticies rect_verticies;
    rect_verticies.create(rectangle);
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
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

void MeshDataConverter::RectVerticies::create(AARect& rectangle){
    this->top_left = glm::vec3(rectangle.getTopLeft(), 0.0f);
    this->top_right = glm::vec3(rectangle.getTopRight(), 0.0f);
    this->bottom_left = glm::vec3(rectangle.getBottomLeft(), 0.0f);
    this->bottom_right = glm::vec3(rectangle.getBottomRight(), 0.0f);
}


void MeshDataConverter::clear(){
    m_vertex_array.clear();
    m_index_array.clear();
    m_index_offset = 0;
}

void MeshDataConverter::generateRectWithColorAndUnitCoords(AARect rectangle){
    MeshDataConverter::RectVerticies rect_verticies;
    rect_verticies.create(rectangle);
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

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

void MeshDataConverter::generateRectIndicies(){
    
    unsigned int indicies[6] ={
        0, 1, 2,
        0, 2, 3
    };

    for(int i = 0; i < 6; i++){
        m_index_array.push_back(indicies[i] + m_index_offset) ;
    }

    m_index_offset += 4;
}

void MeshDataConverter::pushPosition(glm::vec3 position){
    m_vertex_array.insert(m_vertex_array.end(),{
        position.x, position.y, position.z
    });
}

void MeshDataConverter::pushColor(glm::vec3 color){
    m_vertex_array.insert(m_vertex_array.end(),{
        color.x, color.y, color.z
    });
}

void MeshDataConverter::pushTextureCoordinates(glm::vec2 coords){
    m_vertex_array.insert(m_vertex_array.end(),{
        coords.x, coords.y
    });
}

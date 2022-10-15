#include <aa_rect.hpp>



void AARect::create(glm::vec2 position, glm::vec2 size){
    m_position = position;
    m_size = size;
}

float AARect::getTop(){
    return m_position.y;
}

float AARect::getBottom(){
    return m_position.y + m_size.y;
}

float AARect::getLeft(){
    return m_position.x;
}

float AARect::getRight(){
    return m_position.x + m_position.x;
}

glm::vec2 AARect::getTopLeft(){
    return m_position;
}
glm::vec2 AARect::getTopRight(){
    glm::vec2 out = m_position;
    out.x += m_size.x;
    return out;
}

glm::vec2 AARect::getBottomLeft(){
    glm::vec2 out = m_position;
    out.y += m_size.y;
    return out;
}

glm::vec2 AARect::getBottomRight(){
    return m_position + m_size;
}

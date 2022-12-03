#include <shapes/aa_rect.hpp>


AARect::AARect(glm::vec2 position, glm::vec2 size){
    this->create(position, size);
}

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
    return m_position.x + m_size.x;
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

glm::vec2 AARect::getCentre(){
    return glm::vec2(m_position.x + 0.5f * m_size.x, m_position.y + 0.5f * m_size.y);
}


float AARect::getWidth()
{
    return m_size.x;
}

float AARect::getHeight()
{
    return m_size.y;
}

void AARect::combine(AARect other_rect){
    float x = fminf(this->m_position.x, other_rect.m_position.x);
    float y = fminf(this->m_position.y, other_rect.m_position.y);
    float sx = fmaxf(other_rect.getRight(), this->getRight()) - x;
    float sy = fmaxf(other_rect.getBottom(), this->getBottom()) - y;

    this->m_position.x = x;
    this->m_position.y = y;
    this->m_size.x = sx;
    this->m_size.y = sy;
}

void AARect::move(glm::vec2 movement){
    this->m_position += movement;
}

bool AARect::contains(glm::vec2 point){
    return point.x >= this->getLeft() && point.x <= this->getRight() &&
        point.y >= this->getTop() && point.y <= this->getBottom();
}
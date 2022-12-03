#include <input/mouse_cursor.hpp>


void MouseCursor::create(){
    m_position = glm::vec2(0.0f, 0.0f);
    m_delta = glm::vec2(0.0f, 0.0f);
}

void MouseCursor::update(float x, float y){
    glm::vec2 m_new_position = glm::vec2(x, y);
    m_delta = m_new_position - m_position;
    m_position = m_new_position;
}

glm::vec2 MouseCursor::getPosition(){
    return m_position;
}

glm::vec2 MouseCursor::getDelta(){
    return m_delta;
}


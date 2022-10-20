#ifndef GAMES_ENGINE_CIRCLE_HPP
#define GAMES_ENGINE_CIRCLE_HPP
#include <glm/glm.hpp>
struct Circle
{
    glm::vec2 m_position;
    float m_radius;

    void create(glm::vec2 position, float radius){
        m_position = position;
        m_radius = radius;
    }

    AARect toRect(){
        AARect rect;
        glm::vec2 position = glm::vec2(m_position.x - m_radius, m_position.y - m_radius);
        float diameter = 2.0f * m_radius;
        glm::vec2 size = glm::vec2(diameter, diameter);
        rect.create(position, size);
        return rect;
    }
};
#endif
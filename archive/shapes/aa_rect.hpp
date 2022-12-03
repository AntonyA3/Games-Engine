
#ifndef GAMES_ENGINE_AA_RECT
#define GAMES_ENGINE_AA_RECT
#include <glm/glm.hpp>
#include <iostream>
struct AARect
{
    glm::vec2 m_position;
    glm::vec2 m_size;

public:
    AARect(){};
    AARect(glm::vec2 position, glm::vec2 size);
    void create(glm::vec2 position, glm::vec2 size);
    float getTop();
    float getBottom();
    float getLeft();
    float getRight();
    glm::vec2 getTopLeft();
    glm::vec2 getTopRight();
    glm::vec2 getBottomLeft();
    glm::vec2 getBottomRight();
    glm::vec2 getCentre();
    float getWidth();
    float getHeight();
    void combine(AARect other_rect);
    void move(glm::vec2 movement);
    bool contains(glm::vec2 point);

};
#endif
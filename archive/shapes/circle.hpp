#ifndef GAMES_ENGINE_CIRCLE_HPP
#define GAMES_ENGINE_CIRCLE_HPP
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <shapes/aa_rect.hpp>
struct Circle
{
    glm::vec2 position;
    float radius;

    void create(glm::vec2 position, float radius);
    void move(glm::vec2 movement);
    void move(glm::vec2 velocity, float delta_time);
    AARect toRect();
    bool containsPoint(glm::vec2 point);
    float getTop();
    float getBottom();
    float getLeft();
    float getRight();
    glm::vec2 getBottomPoint();
    glm::vec2 getTopPoint();
    glm::vec2 getLeftPoint(); 
    glm::vec2 getRightPoint();
};
#endif
#ifndef GAMES_ENGINE_CAPSULE
#define GAMES_ENGINE_CAPSULE
#include <glm/glm.hpp>
#include <string>
#include <sstream>
#include <shapes/circle.hpp>
#include <shapes/polygon.hpp>
#include <shapes/sweeped_rect.hpp>
struct Capsule
{
    glm::vec2 position;
    float radius;
    glm::vec2 direction;    

    void create(glm::vec2 position, float radius, glm::vec2 direction);
    void sweepUpdate(glm::vec2 movement);
    Circle getStartCircle();
    Circle getEndCircle();
    Polygon getMidSection();
    glm::vec2 end();
    std::string toString();
};
#endif
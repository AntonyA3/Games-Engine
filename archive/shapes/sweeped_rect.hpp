
#ifndef GAMES_ENGINE_SWEEPED_RECT_HPP
#define GAMES_ENGINE_SWEEPED_RECT_HPP
#include <glm/glm.hpp>
struct SweepedRect
{
    glm::vec2 start;
    float hh;
    glm::vec2 direction;

    void create(glm::vec2 start, float half_height, glm::vec2 direction);
};
#endif
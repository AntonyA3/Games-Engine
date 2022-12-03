#ifndef GAMES_ENGINE_RECT_VERTICIES_HPP
#define GAMES_ENGINE_RECT_VERTICIES_HPP
#include <glm/glm.hpp>
#include <shapes/aa_rect.hpp>
struct RectVerticies{
    glm::vec3 top_left;
    glm::vec3 top_right;
    glm::vec3 bottom_left;
    glm::vec3 bottom_right;
    void create(AARect& rect);
};   
#endif
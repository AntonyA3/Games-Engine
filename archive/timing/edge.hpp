
#ifndef GAMES_ENGINE_EDGE_HPP
#define GAMES_ENGINE_EDGE_HPP
#include <glm/glm.hpp>
#include <extra_vector_math.hpp>
/*
    Dependancies:
    include\intersector.hpp
*/
struct Edge
{
    glm::vec2 p0, p1;
    Edge& create(glm::vec2 p0, glm::vec2 p1);
    glm::vec2 asVector();
    glm::vec2 getNormal();
};

#endif
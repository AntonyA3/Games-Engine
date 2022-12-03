#ifndef GAMES_ENGINE_POLYGON
#define GAMES_ENGINE_POLYGON
#include <vector>
#include <shapes/aa_rect.hpp>
#include <rect_verticies.hpp>
#include <edge.hpp>
#include <shapes/sweeped_rect.hpp>

class Polygon
{
    std::vector<glm::vec2> verticies;
    AARect rect;
    public:
    Polygon(){}
    Polygon& create(AARect& rect);
    Polygon& create(SweepedRect& rect);
    AARect toRect();
    Polygon& move(glm::vec2 velocity, float dt);
    Polygon& move(glm::vec2 movement);
    bool containsPoint(glm::vec2 point);
    std::vector<glm::vec2>& getVerticies();
    std::vector<Edge> getEdges();
    float getLeft();
    float getRight();
    float getTop();
    float getBottom();
};

#endif
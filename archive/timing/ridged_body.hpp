#ifndef GAMES_ENGINE_RIDGED_BODY
#define GAMES_ENGINE_RIDGED_BODY
#include <vector>
#include <shapes/circle.hpp>
#include <shapes/aa_rect.hpp>
#include <shapes/polygon.hpp>
#include <intersector.hpp>
#include <imovable.hpp>

struct RidgedBody
{
    glm::vec2 velocity;
    std::vector<Circle> circles;
    std::vector<AARect> rects;
    std::vector<Polygon> polygons;
    std::vector<IMovable *> movables;
    AARect bounding_area;
    RidgedBody& addCircle(Circle& circle);
    RidgedBody& addRect(AARect rect);
    RidgedBody& addPolygon(Polygon& polygon);
    RidgedBody& addMovable(IMovable* movable);
    bool intersects(RidgedBody *other_body);
    void move(float dt);
    void move(glm::vec2 movement);
    void setVelocity(glm::vec2 velocity);
};
#endif

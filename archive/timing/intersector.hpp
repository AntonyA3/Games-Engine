#ifndef GAMES_ENGINE_INTERSECTOR_HPP
#define GAMES_ENGINE_INTERSECTOR_HPP
#include <shapes/aa_rect.hpp>
#include <shapes/polygon.hpp>
#include <shapes/circle.hpp>
#include <shapes/capsule.hpp>
#include <extra_vector_math.hpp>
#include <glm/gtx/string_cast.hpp>
#include <imgui.h>
namespace Intersector{
    template <typename ShapeA, typename ShapeB>
    bool asRectIntersectsAsRect(ShapeA& a, ShapeB& b);
    bool rectIntersectsRect(AARect& rect_0, AARect& rect_1);
    bool circleIntersectsRect(Circle& circle, AARect& rect);
    bool circleIntersectsPolygon(Circle& circle, Polygon& polygon);
    bool polygonIntersectsPolygon(Polygon& polygon_0, Polygon& polygon_1);
    bool polygonIntersectsPolygonEdgeTest(Polygon& polygon_0, Polygon& polygon_1);
    bool capsuleIntersectsRect(Capsule& capsule, AARect& rect);
    bool polygonIntersectsRect(Polygon& polygon, AARect& rect);
};
#endif
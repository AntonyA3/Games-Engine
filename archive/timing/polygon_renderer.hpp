#ifndef GAMES_ENGINE_POLYGON_RENDERER
#define GAMES_ENGINE_POLYGON_RENDERER
#include <mesh.hpp>
#include <glutils.hpp>
#include <mesh_data.hpp>
#include <shapes/polygon.hpp>
#include <iostream>
#include <sub_renderer.hpp>
class PolygonRenderer : public SubRenderer
{
    public:
    void addQuad(AARect& rect, glm::vec3 color);
    void addPolygon(Polygon& polygon, glm::vec3 color);
};
#endif
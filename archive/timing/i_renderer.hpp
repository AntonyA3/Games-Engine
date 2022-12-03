#ifndef GAMES_ENGINE_IRENDERER
#define GAMES_ENGINE_IRENDERER
#include <shapes/circle.hpp>
#include <shapes/polygon.hpp>
#include <glm/glm.hpp>
struct IRenderer
{
    virtual void setBackgroundColor(float r, float g, float b, float a) = 0;
    virtual void addRect(AARect &rect, glm::vec3 color) = 0;
    virtual void addPolygon(Polygon &polygon, glm::vec3 color) = 0;
    virtual void addCircle(Circle &circle, glm::vec3 color) = 0;
    virtual void setWidthHeight(int width, int height) = 0;
    virtual void enableBackfaceCulling() = 0;
    virtual void enableAlphaTransparency() = 0;
};
#endif
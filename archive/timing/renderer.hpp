#ifndef GAMES_ENGINE_RENDERER_HPP
#define GAMES_ENGINE_RENDERER_HPP

#include <sub_renderer.hpp>
#include <shapes/aa_rect.hpp>
#include <shapes/circle.hpp>
#include <shapes/polygon.hpp>
#include <sub_renderer.hpp>
#include <polygon_renderer.hpp>
#include <smooth_circle_renderer.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

#include <i_renderer.hpp>

struct  Renderer :public IRenderer
{
    static const int sub_renderer_count = 0;
    PolygonRenderer m_polygon_renderer;
    SmoothCircleRenderer m_circle_renderer;
    
    int m_width, m_height;
    void updateViewport();
    public:
    void create();
    void begin();
    void clearRender();
    void setBackgroundColor(float r, float g, float b, float a);
    void addRect(AARect &rect, glm::vec3 color);
    void addPolygon(Polygon &polygon, glm::vec3 color);
    void addCircle(Circle &circle, glm::vec3 color);
    void setWidthHeight(int width, int height);
    void render();
    void enableBackfaceCulling();
    void enableAlphaTransparency();
};
#endif
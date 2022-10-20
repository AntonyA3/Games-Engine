#ifndef GAMES_ENGINE_RENDERER_HPP
#define GAMES_ENGINE_RENDERER_HPP
#include <sub_renderer.hpp>
#include <aa_rect.hpp>
#include <circle.hpp>
#include <renderer_data.hpp>
struct Renderer
{
    SubRenderer m_polygon_renderer;
    SubRenderer m_circle_renderer;
    void create(RendererData &renderer_data);
    void begin();
    void addRect(AARect &rect);
    void addCircle(Circle &circle);
    void setMatrix(glm::mat4 matrix);
    void render();
};
#endif
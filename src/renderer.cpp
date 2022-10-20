#include <renderer.hpp>

void Renderer::create(RendererData &renderer_data){
    m_polygon_renderer.create(renderer_data.polygon_renderer_data);
    m_circle_renderer.create(renderer_data.circle_renderer_data);
}

void Renderer::begin(){
    m_circle_renderer.begin();
    m_polygon_renderer.begin();

}

void Renderer::addRect(AARect &rect){
    m_polygon_renderer.addRect(rect);
}

void Renderer::addCircle(Circle &circle){
    AARect rect = circle.toRect();
    m_circle_renderer.addRectWithPositionColorTextureCoordinates(rect);
}

void Renderer::setMatrix(glm::mat4 matrix){
    m_circle_renderer.setMatrix(matrix);
    m_polygon_renderer.setMatrix(matrix);
}

void Renderer::render(){
    m_polygon_renderer.render();
    m_circle_renderer.render();
}
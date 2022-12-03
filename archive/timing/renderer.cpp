#include <renderer.hpp>




void Renderer::create(){
    m_polygon_renderer.create("./data/shaders/polygon_position_color.vert", "./data/shaders/polygon_position_color.frag", {{3}, {3}});
    m_circle_renderer.create("./data/shaders/circle_position_color_texcoord.vert", "./data/shaders/circle_position_color_texcoord.frag", {{3}, {3}, {2}});
}


void Renderer::updateViewport(){
    glViewport(0, 0, m_width, m_height);
    LOG(
        std::cout << "dimensions(" << m_width << " ," << m_height << ")" << std::endl;
    )
    glm::mat4 matrix = glm::ortho(0.0f, (float)m_width, (float)m_height, 0.0f);
    m_polygon_renderer.setMatrix(matrix);
    m_circle_renderer.setMatrix(matrix);
}

void Renderer::begin(){
    m_circle_renderer.begin();
    m_polygon_renderer.begin();
}

void Renderer::addRect(AARect &rect, glm::vec3 color){
    m_polygon_renderer.addQuad(rect, color);
}

void Renderer::addPolygon(Polygon &polygon, glm::vec3 color){
    m_polygon_renderer.addPolygon(polygon, color);
}


void Renderer::addCircle(Circle &circle, glm::vec3 color){
    AARect rect = circle.toRect();
    m_circle_renderer.addQuad(rect, color);
}

void Renderer::setWidthHeight(int width, int height){
    m_width = width;
    m_height = height;
    LOG(
        std::cout << "Renderer Set Width: " << width << " and Height: " << height << std::endl;
    );
    updateViewport();
}

void Renderer::clearRender(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setBackgroundColor(float r, float g, float b, float a){

    glClearColor(r, g, b, a);
}

void Renderer::render(){
  
    m_polygon_renderer.render();
    m_circle_renderer.render();
}

void Renderer::enableBackfaceCulling(){
    LOG(
        std::cout << "Enable Backface" << std::endl;
    );
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); 
}

void Renderer::enableAlphaTransparency(){
    LOG(
        std::cout << "Enable Transparency" << std::endl;
    );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
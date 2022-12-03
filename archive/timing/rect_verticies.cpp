#include <rect_verticies.hpp>

void RectVerticies::create(AARect& rectangle){
    this->top_left = glm::vec3(rectangle.getTopLeft(), 0.0f);
    this->top_right = glm::vec3(rectangle.getTopRight(), 0.0f);
    this->bottom_left = glm::vec3(rectangle.getBottomLeft(), 0.0f);
    this->bottom_right = glm::vec3(rectangle.getBottomRight(), 0.0f);
}
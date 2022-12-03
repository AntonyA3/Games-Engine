#include <shapes/sweeped_rect.hpp>>

void SweepedRect::create(glm::vec2 start, float half_height, glm::vec2 direction){
    this->start = start;
    this->hh = half_height;
    this->direction = direction;
}

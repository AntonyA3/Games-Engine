#include <edge.hpp>

Edge& Edge::create(glm::vec2 p0, glm::vec2 p1){
    this->p0 = p0;
    this->p1 = p1;
    return *this;
}

glm::vec2 Edge::asVector(){
    return this->p1 - this->p0;
}

glm::vec2 Edge::getNormal(){
    glm::vec2 vector = this->asVector();
    return glm::vec2(-vector.y, vector.x);
}


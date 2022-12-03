#include <shapes/circle.hpp>


void Circle::create(glm::vec2 position, float radius){
    this->position = position;
    this->radius = radius;
}

void Circle::move(glm::vec2 movement){
    this->position += movement;
}

void Circle::move(glm::vec2 velocity, float delta_time){
    this->position += velocity * delta_time;
}

AARect Circle::toRect(){
    AARect rect;
    glm::vec2 pos = glm::vec2(this->position.x - this->radius, this->position.y - this->radius);
    float diameter = 2.0f * this->radius;
    glm::vec2 size = glm::vec2(diameter, diameter);
    rect.create(pos, size);
    return rect;
}

bool Circle::containsPoint(glm::vec2 point){
    return glm::length2(point - this->position) <= this->radius * this->radius;
}

float Circle::getTop(){
    return this->position.y - this->radius;
}

float Circle::getBottom(){
    return this->position.y + this->radius;
}

float Circle::getLeft(){
    return this->position.x - this->radius;
}

float Circle::getRight(){
    return this->position.x + this->radius;
}

glm::vec2 Circle::getBottomPoint(){
    return glm::vec2(this->position.x, getBottom());
}

glm::vec2 Circle::getTopPoint(){
    return glm::vec2(this->position.x, getTop());
}

glm::vec2 Circle::getLeftPoint(){
    return glm::vec2(getLeft(), this->position.y);
} 

glm::vec2 Circle::getRightPoint(){
    return glm::vec2(getRight(), this->position.y);
}
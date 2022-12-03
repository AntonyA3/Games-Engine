#include <shapes/capsule.hpp>

void Capsule::create(glm::vec2 position, float radius, glm::vec2 direction){
    this->position = position;
    this->radius = radius;
    this->direction = direction;
}

void Capsule::sweepUpdate(glm::vec2 movement){
    glm::vec2 new_end = this->end() + movement;
    this->position = this->end();  
    this->direction = new_end - this->position;
}


glm::vec2 Capsule::end(){
    return this->position + this->direction;
}


Circle Capsule::getStartCircle(){
    Circle circle;
    circle.create(this->position, this->radius);
    return circle;
}

Circle Capsule::getEndCircle(){
    Circle circle = this->getStartCircle();
    circle.move(this->direction);
    return circle;
}

Polygon Capsule::getMidSection(){
    SweepedRect sweep_rect;
    sweep_rect.create(this->position, this->radius, this->direction);
    Polygon polygon;
    polygon.create(sweep_rect);
    return polygon;
}

std::string Capsule::toString(){
    std::stringstream ss;
    ss << "Capsule: {\n";
    ss << "\tposition: {x:" << this->position.x << ", y: " << this->position.y << "}\n";
    ss << "\tradius: " << this->radius << "\n"; 
    ss << "\tdirection: {x:" << this->direction.x << ", y: " << this->direction.y << "}\n";
    ss << "}";
    return ss.str();
}


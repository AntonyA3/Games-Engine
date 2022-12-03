
#include <shapes/polygon.hpp>


Polygon& Polygon::create(AARect& rect){
    RectVerticies rect_verticies;
    rect_verticies.create(rect);
    this->verticies.clear();
    this->verticies.push_back(glm::vec2(rect_verticies.bottom_left.x, rect_verticies.bottom_left.y));
    this->verticies.push_back(glm::vec2(rect_verticies.bottom_right.x, rect_verticies.bottom_right.y));
    this->verticies.push_back(glm::vec2(rect_verticies.top_right.x, rect_verticies.top_right.y));
    this->verticies.push_back(glm::vec2(rect_verticies.top_left.x, rect_verticies.top_left.y));
    this->rect = rect;
    return *this;
}

Polygon& Polygon::create(SweepedRect& rect){

    glm::vec2 normal = glm::normalize(glm::vec2(-rect.direction.y, rect.direction.x));
    this->verticies.clear();
    this->verticies.push_back(rect.start + normal * rect.hh);
    this->verticies.push_back(rect.start + rect.direction + normal * rect.hh);
    this->verticies.push_back(rect.start + rect.direction - normal * rect.hh);
    this->verticies.push_back(rect.start - normal * rect.hh);

    float min_x = ExtraVectorMath::maxPoint(this->verticies, glm::vec2(-1.0f, 0.0f)).x;
    float max_x = ExtraVectorMath::maxPoint(this->verticies, glm::vec2(1.0f, 0.0f)).x;
    float min_y = ExtraVectorMath::maxPoint(this->verticies, glm::vec2(0.0f, -1.0f)).y;
    float max_y = ExtraVectorMath::maxPoint(this->verticies, glm::vec2(1.0f, 1.0f)).y;
    this->rect.create(glm::vec2(min_x, min_y), glm::vec2(max_x - min_x, max_y - min_y));
    return *this;

}


AARect Polygon::toRect(){
    return rect;
}

std::vector<glm::vec2>& Polygon::getVerticies(){
    return this->verticies;
}

Polygon& Polygon::move(glm::vec2 movement){
    for(int i = 0; i < verticies.size(); i++){
        verticies.at(i) += movement;
    }
    return *this;
}

Polygon& Polygon::move(glm::vec2 velocity, float dt){
    return this->move(velocity * dt);
}

bool Polygon::containsPoint(glm::vec2 point){
    std::vector<Edge> edges = this->getEdges();
    bool contains = true;
    for(int i = 0; i < edges.size(); i++){
        contains = contains && ExtraVectorMath::projectionT(point, edges.at(i).p0, edges.at(i).getNormal()) > 0.0f;
        
    }
    return contains;
}

std::vector<Edge> Polygon::getEdges(){
    std::vector<Edge> edges;
    for(int i = 0; i < this->verticies.size(); i++){
        Edge edge;
        edge.create(this->verticies.at(i), this->verticies.at((i + 1) % this->verticies.size()));
        edges.push_back(edge);
    }
    return edges;
}


float Polygon::getLeft(){
    return ExtraVectorMath::maxPoint(this->verticies, glm::vec2(-1.0f, 0.0f)).x;
}
float Polygon::getRight(){
    return ExtraVectorMath::maxPoint(this->verticies, glm::vec2(1.0f, 0.0f)).x;

}
float Polygon::getTop(){
    return ExtraVectorMath::maxPoint(this->verticies, glm::vec2(0.0f, -1.0f)).y;

}
float Polygon::getBottom(){
    return ExtraVectorMath::maxPoint(this->verticies, glm::vec2(0.0f, 1.0f)).y;

}
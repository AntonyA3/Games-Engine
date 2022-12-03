#include <ridged_body.hpp>

RidgedBody& RidgedBody::addCircle(Circle& circle){
    AARect rect = circle.toRect();
    this->bounding_area.combine(rect);
    this->circles.push_back(circle);
    return *this;
}

RidgedBody& RidgedBody::addRect(AARect rect){
    this->bounding_area.combine(rect);
    this->rects.push_back(rect);
    return *this;

}

RidgedBody& RidgedBody::addPolygon(Polygon& polygon){
    AARect polygon_as_rect = polygon.toRect();
    this->bounding_area.combine(polygon_as_rect);
    this->polygons.push_back(polygon);
    return *this;
}

RidgedBody& RidgedBody::addMovable(IMovable * movable){
    this->movables.push_back(movable);
    return * this;
}


bool RidgedBody::intersects(RidgedBody * other_body){
    if(!Intersector::rectIntersectsRect(this->bounding_area, other_body->bounding_area)){
        return false;
    }

    bool intersecting = false;
    for(Circle& circle : this->circles){
        for(Circle& other_circle : other_body->circles){
            
        }
        for(AARect& other_rect : other_body->rects){
            intersecting |= Intersector::circleIntersectsRect(circle, other_rect);
        }

        for(Polygon& other_polygon : other_body->polygons){

        }
    }
    for(AARect& rect : this->rects){
        for(Circle& other_circle : other_body->circles){
            
        }
        for(AARect& other_rect : other_body->rects){
            intersecting |= Intersector::rectIntersectsRect(rect, other_rect);
        }

        for(Polygon& other_polygon : other_body->polygons){

        }
    }
    for(Polygon& polygon : this->polygons){
        for(Circle& other_circle : other_body->circles){
            
        }
        for(AARect& other_rect : other_body->rects){
            
        }

        for(Polygon& other_polygon : other_body->polygons){

        }
    }

    return intersecting;

}
void RidgedBody::move(glm::vec2 movement){
    for (Circle& circle : this->circles)
    {
        circle.move(movement);
    }

    for(AARect& rect : this->rects){
        rect.move(movement);
    }
    
    for(Polygon& polygon : this->polygons){
        polygon.move(movement);
    }

    for(IMovable * movable : this->movables){
        std::cout << "address of the movable. which should be the same as paddle movable: " << movable << std::endl;
        movable->move(movement);
    }
}

void RidgedBody::move(float dt){
    this->move(this->velocity * dt);
}

void RidgedBody::setVelocity(glm::vec2 velocity){
    this->velocity = velocity;
}

#include <shapes/multi_shape.hpp>


void MultiShape::move(glm::vec2 movement){
    for(AARect& rect : this->aa_rects){
        rect.move(movement);
    }
    for(Circle& circle : this->circles){
        circle.move(movement);
    }
    bounding_rect.move(movement);

}


void MultiShape::addCircle(Circle circle){
    this->circles.push_back(circle);
    if(shape_count == 0){
        bounding_rect = circle.toRect();
    }else{
        bounding_rect.combine(circle.toRect());
    }
    shape_count++;
}

void MultiShape::addRect(AARect rect){
    this->aa_rects.push_back(rect);
    if(shape_count == 0){
        bounding_rect = rect;
    }else{
        bounding_rect.combine(rect);
    }
    shape_count++;

}

bool MultiShape::containsPoint(glm::vec2 point){
    for(Circle& circle : this->circles){
        if(circle.containsPoint(point)){
            return true;
        }
    }

    for(AARect& rect : this->aa_rects){
        if(rect.contains(point)){
            return true;
        }
    }
    return false;
}
    
float MultiShape::getLeft(){
    return this->bounding_rect.getLeft(); 
}

float MultiShape::getRight(){
    return this->bounding_rect.getRight();
}

float MultiShape::getBottom(){
    return this->bounding_rect.getBottom();
}

float MultiShape::getTop(){
    return this->bounding_rect.getTop();
}

float MultiShape::getWidth(){
    return this->getRight() - this->getLeft();
}


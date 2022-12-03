#include <shape_resolver.hpp>

struct CircleLineIntersection{
    bool hit; 
    float t0, t1;

    CircleLineIntersection& intersect(Circle& circle, glm::vec2 line_start, glm::vec2 vector){
        glm::vec2 circle_to_line_start = line_start - circle.position;
        float a_val = glm::dot(vector, vector);
        float b_val = 2.0f * glm::dot(vector, line_start - circle.position);
        float c_val =  glm::dot(circle.position, circle.position - 2.0f * line_start) + glm::dot(line_start, line_start) - circle.radius * circle.radius;
        float determinant = b_val * b_val - 4.0f * a_val * c_val;
        this->hit = determinant >= 0.0f;
        if (!hit){ 
            return *this;
        }
        this->t0 = ((-b_val) - sqrtf(determinant)) / (2.0f * a_val);
        this->t1 = ((-b_val) + sqrtf(determinant)) / (2.0f * a_val);
        return *this;
    }

    bool hitThis(){
        return this->hit;
    }

    float maxT(){
        return std::max(this->t0, this->t1);
    }
};



template <int axis, int other_axis>
bool ShapeResolver::resolve(float& dt, glm::vec2& normal, float start, float target, float min_bound, float max_bound, glm::vec2 start_point, glm::vec2 velocity, glm::vec2 new_normal){
    
    float t = (start - target) / velocity[axis];
    glm::vec2 pp = start_point - velocity * t;
    bool better = (t > dt) && (pp[other_axis] >= min_bound) && (pp[other_axis] <= max_bound);
    if(better){

        dt = t;
        normal = new_normal;
    }
    return better;
}

bool ShapeResolver::resolve(float& dt, glm::vec2& normal, Circle& circle, AARect& rect, glm::vec2 velocity){
    // For each box points on the circle,find how far it is away from the rectangle
    bool better = false;
    // top
    {
        float t = (circle.getBottom() - rect.getTop()) / velocity.y;
        glm::vec2 point = circle.getBottomPoint() - velocity * t;

        if ((velocity.y > 0.0f) && (t > dt) && (point.x >= rect.getLeft()) && (point.x <= rect.getRight())){
            dt =  t;
            normal = glm::vec2(0.0f, -1.0f);
            better = true;
        }
        
    }
    //bottom
    {
        float t = (circle.getTop() - rect.getBottom()) / velocity.y;
        glm::vec2 point = circle.getTopPoint() - velocity * t;
        if ((velocity.y < 0.0f) && (t > dt) && (point.x >= rect.getLeft()) && (point.x <= rect.getRight())){
            dt = t;
            normal = glm::vec2(0.0f, 1.0f);
            better = true;

        }  
    }
    //right
    {
        float t = (circle.getLeft() - rect.getRight()) / velocity.x;
        glm::vec2 point = circle.getLeftPoint() - velocity * t;
        if((velocity.x < 0.0f) && (t > dt) && (point.y >= rect.getTop()) && (point.y <= rect.getBottom())){
            dt = t;
            normal = glm::vec2(1.0f, 0.0f);
            better = true;

        }
    }
    //left
    {
        float t = (circle.getRight() - rect.getLeft()) / velocity.x;
        glm::vec2 point = circle.getRightPoint() - velocity * t;
        if((velocity.x > 0.0f) && (t > dt) && (point.y >= rect.getTop()) && (point.y <= rect.getBottom())){
            dt = t;
            normal = glm::vec2(-1.0f, 0.0f);
            better = true;

        } 
    }
    
    glm::vec2 rect_verticies[4] = {
        rect.getTopLeft(),
        rect.getTopRight(),
        rect.getBottomLeft(),
        rect.getBottomRight()
    };

    for(int i = 0; i < 4; i++){
        CircleLineIntersection circle_intersection = CircleLineIntersection();
        circle_intersection.intersect(circle, rect_verticies[i], velocity);
        if (circle_intersection.hitThis()){
            float t = circle_intersection.hit ? circle_intersection.maxT() : 0.0f;
            if(t > dt){
                dt = t;
                normal = glm::normalize(circle.position - (rect_verticies[i] + t * velocity));
                better = true;

            }   
        }
    }
    return better;
}



bool ShapeResolver::resolve(float& dt, glm::vec2& normal, float start, float target, float velocity, glm::vec2 new_normal){
    bool better = false;
    if(velocity != 0){
        float t = (start - target) / velocity;
        better = t > dt;
        if(better){
            dt = t;
            normal = new_normal;
        }
    }
    return better;
}

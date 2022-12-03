#include <extra_vector_math.hpp>


ExtraVectorMath::VectorMathResult ExtraVectorMath::pointintersectLineT(glm::vec2 r_line_start, glm::vec2 r_line_velocity, glm::vec2 target_line_point, glm::vec2 target_line_normal){
    VectorMathResult vector_math_result;
    
    float determinant = glm::dot(target_line_normal, r_line_velocity);
    if(determinant == 0.0f) {
        vector_math_result.hit = false;
        return vector_math_result;
    };
    vector_math_result.hit = true;
    vector_math_result.t = glm::dot(target_line_point - r_line_start, target_line_normal) / determinant;

    return vector_math_result;
}


/// @brief Given a point on the line, a line normal and a point not on the line, Calculate
/// @param l0 The point away from the line
/// @param p The point on the line
/// @param n The line normal
/// @return The relative distance to the closest point on the line
float ExtraVectorMath::projectionT(glm::vec2 l0, glm::vec2 p, glm::vec2 n){
    return glm::dot(p - l0, n) / glm::dot(n, n);
}

glm::vec2 ExtraVectorMath::projectionPoint(glm::vec2 l0, glm::vec2 p, glm::vec2 n){
    float t = projectionT(l0, p, n);
    return l0 + n * t;
}


/// @brief Given a point on a line, the start of the line and the end of the line
/// @param point The point on the line
/// @param start The point at start of the line
/// @param end The point at end of the line
/// @return The reletive distance of the point along the line
float ExtraVectorMath::pointOnLineT(glm::vec2 point, glm::vec2 start, glm::vec2 end){
    glm::vec2 line_vector = end - start;
    return glm::dot(point - start, line_vector) / glm::dot(line_vector, line_vector);
}


float ExtraVectorMath::pointOnLineT_2(glm::vec2 point, glm::vec2 start, glm::vec2 line_vector){
    return glm::dot(point - start, line_vector) / glm::dot(line_vector, line_vector);
}

glm::vec2 ExtraVectorMath::lineClamp(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 line_point, glm::vec2 vector){
    float t = glm::dot(line_point - line_start, vector) / glm::dot(vector, vector);
    return 
        (t <= 0.0f) ? line_start :
        (t >= 1.0f) ? line_end :
        line_point;
}

bool ExtraVectorMath::isPointOnLine(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 point){
    float t = pointOnLineT(point, line_start, line_end);
    return  (t >= 0.0f) && (t <= 1.0f);
}

glm::vec2 ExtraVectorMath::lineClamp(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 line_point){
    glm::vec2 vector = line_end - line_start;
    return lineClamp(line_start, line_end, line_point, vector);
}



glm::vec2 ExtraVectorMath::maxPoint(std::vector<glm::vec2>& points, glm::vec2 vector){
    float dot_product = std::numeric_limits<float>::lowest();
    int index = 0;
    for(int i = 0; i < points.size(); i++){
        float new_dot = glm::dot(points.at(i), vector);
        bool better = new_dot > dot_product;
        dot_product = better ? new_dot : dot_product;
        index = better ? i : index;
    }
    return points.at(index);
}

glm::vec2 ExtraVectorMath::minPoint(std::vector<glm::vec2>& points, glm::vec2 vector){
    float dot_product = std::numeric_limits<float>::infinity();
    int index = 0;
    for(int i = 0; i < points.size(); i++){
        float new_dot = glm::dot(points.at(i), vector);
        bool better = new_dot < dot_product;
        dot_product = better ? new_dot : dot_product;
        index = better ? i : index;
    }
    return points.at(index);

}
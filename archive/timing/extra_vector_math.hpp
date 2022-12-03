#ifndef GAMES_ENGIN_EXTRA_VECTOR_MATH_HPP
#define GAMES_ENGIN_EXTRA_VECTOR_MATH_HPP
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
namespace ExtraVectorMath{
    struct VectorMathResult{
        bool hit;
        float t;
    };
    VectorMathResult pointintersectLineT(glm::vec2 r_line_start, glm::vec2 r_line_velocity, glm::vec2 target_line_point, glm::vec2 target_line_normal);
    float projectionT(glm::vec2 l0, glm::vec2 p, glm::vec2 n);
    glm::vec2 projectionPoint(glm::vec2 l0, glm::vec2 p, glm::vec2 n);
    float pointOnLineT(glm::vec2 point, glm::vec2 start, glm::vec2 end);
    float pointOnLineT_2(glm::vec2 point, glm::vec2 start, glm::vec2 line_vector);
    glm::vec2 lineClamp(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 line_point, glm::vec2 vector);
    bool isPointOnLine(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 point);
    glm::vec2 lineClamp(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 line_point);
    glm::vec2 minPoint(std::vector<glm::vec2>& points, glm::vec2 vector);
    glm::vec2 maxPoint(std::vector<glm::vec2>& points, glm::vec2 vector);

}
#endif
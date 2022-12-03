#include <glm/glm.hpp>
#include <shapes/circle.hpp>
#include <shapes/aa_rect.hpp>
struct ShapeResolver{
    // This will update the time and the normal when the circle hits the rect
    bool resolve(float& dt, glm::vec2& normal, Circle& circle, AARect& rect, glm::vec2 cumu_velocity);
    //This will resolve a point to a bounded line on an axis
    template <int axis, int other_axis>
    bool resolve(float& dt, glm::vec2& normal, float start, float target, float min_bound, float max_bound, glm::vec2 start_point, glm::vec2 velocity, glm::vec2 new_normal);
    // This will update the time and the normal if the circle hits the rect in less time and the circle is travelling towards the rect
    // resolves based on start value of of bect to resolve in one dimension  and velocity in a single dimension.
    bool resolve(float& dt, glm::vec2& normal, float start, float target, float velocity, glm::vec2 new_normal);
};
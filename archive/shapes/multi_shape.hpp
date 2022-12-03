#include <vector>
#include <shapes/aa_rect.hpp>
#include <shapes/circle.hpp>
struct MultiShape
{
    std::vector<AARect> aa_rects;
    std::vector<Circle> circles;
    AARect bounding_rect;
    int shape_count = 0;
    void move(glm::vec2 movement);
    void addCircle(Circle circle);
    void addRect(AARect rect);
    bool containsPoint(glm::vec2 point);
    float getLeft();
    float getRight();
    float getBottom();
    float getTop();
    float getWidth();
};

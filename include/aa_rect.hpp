
#ifndef GAMES_ENGINE_AA_RECT
#define GAMES_ENGINE_AA_RECT
#include <glm/glm.hpp>
class AARect
{
    glm::vec2 m_position;
    glm::vec2 m_size;

public:
    void create(glm::vec2 position, glm::vec2 size);
    float getTop();
    float getBottom();
    float getLeft();
    float getRight();
    glm::vec2 getTopLeft();
    glm::vec2 getTopRight();
    glm::vec2 getBottomLeft();
    glm::vec2 getBottomRight();
};
#endif
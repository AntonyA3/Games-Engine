#ifndef GAMES_ENGINE_MOUSE_CURSOR
#define GAMES_ENGINE_MOUSE_CURSOR
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
class MouseCursor
{
private:
    glm::vec2 m_position;
    glm::vec2 m_delta = glm::vec2(0.0f, 0.0f);
public:
    void create();
    void update(float x, float y);
    glm::vec2 getPosition();
    glm::vec2 getDelta();
};
#endif
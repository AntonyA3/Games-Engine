#ifndef GAMES_ENGINE_I_MOVABLE
#define GAMES_ENGINE_I_MOVABLE
#include <glm/glm.hpp>
#include <iostream>
class IMovable
{
public:
    virtual void move(glm::vec2 movement) = 0;
    virtual ~IMovable();
};

#endif
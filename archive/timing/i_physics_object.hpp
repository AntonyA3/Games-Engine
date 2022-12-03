

#ifndef GAMES_ENGINE_I_PHYSICS_OBJECT
#define GAMES_ENGINE_I_PHYSICS_OBJECT
#include <glm/glm.hpp>
#include <iostream>
class IPhysicsObject
{
public:
    virtual void move(float dt) = 0;
    virtual void move(glm::vec2 movement) = 0;
    virtual float getLeft() = 0;
    virtual float getRight() = 0;
    virtual float getBottom() = 0;
    virtual float getTop() = 0;

    ~IPhysicsObject();
};

#endif
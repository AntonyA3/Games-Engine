#ifndef GAMES_ENGINE_BRICKS
#define GAMES_ENGINE_BRICKS
#include <glm/glm.hpp>
#include <shapes/aa_rect.hpp>
#include <vector>
struct Bricks
{
public:
    struct Brick{
        bool active;
        AARect rect;
        AARect& getRect();
        bool isVisible();
        void hit();
    };    
    std::vector<Brick> bricks;

    bool allDestroyed();

};
#endif
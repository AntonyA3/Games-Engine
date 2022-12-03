#ifndef GAMES_ENGINE_IMODE
#define GAMES_ENGINE_IMODE
#include <iostream>
#include <i_renderer.hpp>
#include <i_game_object.hpp>
struct IMode{
    IMode(){}
    ~IMode(){}
    virtual void update(float dt) = 0;

    template <typename TRenderer>
    void renderControl(TRenderer& renderer){}


};

#endif


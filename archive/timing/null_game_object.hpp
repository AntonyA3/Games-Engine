#ifndef NULL_GAME_OBJECT_HPP
#define NULL_GAME_OBJECT_HPP
#include <i_game_object.hpp>
struct NullGameObject:  public IGameObject{
    void update(float dt){}
    template <typename TRenderer>
    void renderControl(TRenderer& renderer){}
    template <typename TInput>
    void inputControl(TInput& input){}
};
#endif
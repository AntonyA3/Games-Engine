#ifndef GAMES_ENGINE_LEVEL_EDITOR_MODE
#define GAMES_ENGINE_LEVEL_EDITOR_MODE
#include <vector>
#include <i_mode.hpp>
#include <breakout_game/entity.hpp>
struct LevelEditorMode : IMode{
    std::vector<Entity *> * entities;

    LevelEditorMode(std::vector<Entity*>& entities){
        this->entities = &entities;
    }
    void update(float dt);
};
#endif

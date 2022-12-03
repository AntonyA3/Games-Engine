#ifndef GAMES_ENGINE_PAUSE_MODE
#define GAMES_ENGINE_PAUSE_MODE

#include <i_mode.hpp>
#include <i_renderer.hpp>
#include <breakout_game/entity.hpp>
#include <input/keyboard_button.hpp>
#include <level_editor_mode.hpp>
struct PauseMode :public IMode, public IGameObject{

    void update(float dt);
    
    template <typename TRenderer>
    void renderControl(TRenderer& renderer) {

    }

    template <typename TInput>
    void inputControl(TInput& renderer) {

    }

};
#endif

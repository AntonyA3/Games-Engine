#include <breakout_game/bricks.hpp>

AARect& Bricks::Brick::getRect(){
    return this->rect;
}

bool Bricks::Brick::isVisible(){
    return this->active;
}

void Bricks::Brick::hit(){
    this->active = false;
}

bool Bricks::allDestroyed(){
    bool destroyed = true;
    for(Brick& brick : this->bricks){
        destroyed = destroyed && !brick.active;
    }
    return destroyed;
}

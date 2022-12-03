#include <timing/time_controller.hpp>
#include <iostream>
Uint64 TimeController::getTime(){
    return this->time;
}

float TimeController::getDeltaTime(){
    return this->delta_time;
}

void TimeController::update(){
    update(SDL_GetTicks64());   
}

void TimeController::update(Uint64 new_time){

    if(new_time >= time){ // No overflow
        this->delta_time = ((float)new_time - (float)this->time) * 0.001f;
    }else{
        Uint64 actualElapsed = new_time + std::numeric_limits<Uint64>::max() - this->time;
        this->delta_time =actualElapsed * 0.001f;
    }
    this->time = new_time;

}

void TimeController::create(Uint64 time){
    this->delta_time = 1.0f / 60.0f;
    this->time = time;
}

void TimeController::create(){
    this->create(SDL_GetTicks64());
}

TimeController::TimeController(){
    this->create();
}

TimeController::TimeController(Uint64 time){
    this->create(time);
}

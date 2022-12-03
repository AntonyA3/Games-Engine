#include <game_mode.hpp>


GameMode::GameMode(GameLoop &game_loop, PauseMode &pause_mode,
    Renderer& renderer, Paddle &primary_paddle, float &left_wall, 
    float &right_wall, float &top_wall, float &bottom_wall,
    GameObjectCollection<Ball> &balls, GameObjectCollection<Paddle> &paddles,
    int &score,
    Bricks &bricks,
    KeyboardButton &pause_button, 
    KeyboardButton &left_button,
    KeyboardButton &right_button    
){
    this->pause_mode = &pause_mode;
    this->renderer = &renderer;
    this->primary_paddle = &primary_paddle;
    this->left_wall = &left_wall;
    this->right_wall = &right_wall;
    this->top_wall = &top_wall;
    this->bottom_wall = &bottom_wall;
    this->balls = &balls;
    this->paddles = &paddles;
    this->score = &score;
    this->bricks = &bricks;
    this->pause_button = &pause_button;
    this->left_button = &left_button;
    this->right_button = &right_button;        
    this->game_loop = &game_loop;

    this->mode = this->game_loop;
}   

void GameMode::update(float dt){
    


}

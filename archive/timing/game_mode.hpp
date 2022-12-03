#include <input/keyboard_button.hpp>
#include <game_loop.hpp>
#include <pause_mode.hpp>
struct GameMode : IMode{

    GameLoop * game_loop;
    PauseMode * pause_mode;

    float * left_wall;
    float * right_wall;
    float * top_wall;
    float * bottom_wall;
    bool paused = false;
    Paddle * primary_paddle;
    Renderer * renderer;
    IMode * mode;
    KeyboardButton * pause_button; 
    KeyboardButton * left_button;
    KeyboardButton * right_button;
    GameObjectCollection<Ball> * balls;
    GameObjectCollection<Paddle> * paddles;

    Bricks * bricks;
    int * score;
    GameMode(GameLoop &game_loop, PauseMode &pause_mode,
        Renderer& renderer, Paddle &primary_paddle,
        float &left_wall, float &right_wall, float &top_wall, float &bottom_wall,
        GameObjectCollection<Ball> &balls, GameObjectCollection<Paddle> &paddles,
        int &score,
        Bricks &bricks,
        KeyboardButton &pause_button, 
        KeyboardButton &left_button,
        KeyboardButton &right_button    
    );
    void update(float dt);
};
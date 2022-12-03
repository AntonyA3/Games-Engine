#ifndef GAMES_ENGINE_PHYSICS_PROCESSOR
#define GAMES_ENGINE_PHYSICS_PROCESSOR
#include <vector>
#include <breakout_game/entity.hpp>
#include <shapes/circle.hpp>
#include <shapes/aa_rect.hpp>
#include <breakout_game/bricks.hpp>
#include <intersector.hpp>
#include <i_mode.hpp>
#include <input/input_controller.hpp>
#include <input/keyboard_button.hpp>
#include <game_object_collection.hpp>
#include <scene.hpp>
class GameLoop :public IMode
{

public:
struct ShapeResolver{
    float time;
    glm::vec2 normal;

    void reset();

    // This will update the time and the normal when the circle hits the rect
    bool resolve(Circle& circle, AARect& rect, glm::vec2 cumu_velocity);
    //This will resolve a point to a bounded line on an axis
    template <int axis, int other_axis>
    bool resolve(float start, float target, float min_bound, float max_bound, glm::vec2 start_point, glm::vec2 velocity, glm::vec2 normal);

    // This will update the time and the normal if the circle hits the rect in less time and the circle is travelling towards the rect
    
    // resolves based on start value of of bect to resolve in one dimension  and velocity in a single dimension.
    bool resolve(float start, float target, float velocity, glm::vec2 normal);
};

private:
    Scene * scene;
    int * score;
    GameObjectCollection<Paddle> * paddles;
    GameObjectCollection<Ball> * balls;
    Bricks* bricks;
    GameLoop::ShapeResolver shape_resolver;
    KeyboardButton * left_button;
    KeyboardButton * right_button;
public:
    GameLoop(){}
    GameLoop(
        Scene &scene,
        int &score,
        GameObjectCollection<Paddle> &paddles,
        GameObjectCollection<Ball> &balls,
        Bricks &bricks,
        KeyboardButton &left_button,
        KeyboardButton &right_button
    );
    void update(float dt);
};
#endif
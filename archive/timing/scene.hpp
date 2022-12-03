#ifndef GAMES_ENGINE_SCENE_HPP
#define GAMES_ENGINE_SCENE_HPP
#include <breakout_game/entity.hpp>
#include <breakout_game/bricks.hpp>

#include <rapidxml-1.13/rapidxml_utils.hpp>
#include <rapidxml-1.13/rapidxml_ext.h>
#include <game_object_collection.hpp>
#include <i_renderer.hpp>
#include <intersector.hpp>
#include <shape_resolver.hpp>
#include <i_game_button.hpp>
#include <pause_mode.hpp>
#include <brick_grid.hpp>
#include <radial_bricks.hpp>
#include <i_input.hpp>
#include <null_game_object.hpp>
namespace Menu{
    struct OnClick{

    };
    struct Button{
        std::vector<OnClick> onClicks;
    };
    struct VerticalLayout{
        int selected;
        std::vector<Button> buttons;

    };
};


struct OnHit {
    virtual void update(glm::vec2 normal) = 0;
};

struct BallBounceOfPaddle : OnHit{
    Ball * ball;
    Paddle * paddle;
    void set(Ball * ball, Paddle * paddle){
        this->ball = ball;
        this->paddle = paddle;
    }
    void update(glm::vec2 normal){
        if(normal.y == 1.0f){
            ball->velocity = paddle->bounceOffTop(ball->velocity, ball->position.x);
        }else{
            ball->velocity = glm::reflect(ball->velocity, normal);
        }
    }
};

struct BallBounceOfWall : OnHit{
    Ball * ball;
    void set(Ball * ball){
        this->ball = ball;
    }
    void update(glm::vec2 normal){
        ball->velocity = glm::reflect(ball->velocity, normal);

    }
};

struct PaddleHitsWall : OnHit{
    Paddle * paddle;
    void set(Paddle * paddle){
        this->paddle = paddle;
    }
    void update(glm::vec2 normal){
        paddle->velocity.x = 0.0f;
    }
};

struct BounceBallDestroyBrick : OnHit{
    Bricks::Brick * brick;
    Ball * ball;
    int * score;

    void set(Ball * ball, Bricks::Brick * brick, int * score){
        this->brick = brick;
        this->ball = ball;
        this->score = score;
    }

    void update(glm::vec2 normal){
        ball->velocity = glm::reflect(ball->velocity, normal);
        brick->hit();
        *score += 10.0f;
        std::cout << "score is now: " << *score << std::endl;
        
    }
};

#include <i_game_object.hpp>

struct Scene : IGameObject{

    GameObjectCollection<Paddle> paddles;
    GameObjectCollection<Ball> balls;
    Bricks bricks; 
    ShapeResolver shape_resolver;
    Menu::Button resume_button;
    Menu::Button settings_button;
    Menu::Button quit_button;
    Paddle * primary_paddle;

    NullGameObject null_game_object;
    PauseMode pause_mode;
    BounceBallDestroyBrick bounce_ball_destroy_brick;
    BallBounceOfPaddle ball_bounce_paddle;
    BallBounceOfWall ball_bounce_wall;
    PaddleHitsWall paddle_hits_wall;

    IGameObject * mode;

    std::vector<Entity *> entities;
    float left_wall = 40.0f;
    float right_wall = 640.0f - 40.0f;
    float top_wall = 0.0f;
    float bottom_wall = 480.0f;     
    int score = 0;
    Scene();

    void update(float dt);
    void pausedRender();
    void gameLoop(float dt);
    void pauseToggle();
    bool isPaused();
    void addBrickGrid(BrickGrid& brick_grid);
   
    template <typename TRenderer>
    void renderControl(TRenderer& renderer){
        for(Ball& ball : this->balls){
            renderer.addCircle(ball.refCircle(), glm::vec3(1.0f, 1.0f, 1.0f));
        }
        for(Bricks::Brick& brick : this->bricks.bricks){
            if (brick.isVisible()){
                AARect rect = brick.getRect();
                renderer.addRect(rect, glm::vec3(1.0f, 1.0f, 1.0f));
            }
        }
        renderer.addRect(primary_paddle->refRect(), glm::vec3(1.0f, 1.0f, 1.0f));
        AARect left_wall_area; 
        left_wall_area.create(glm::vec2(left_wall - 4, 0), glm::vec2(4, 480));
        renderer.addRect(left_wall_area, glm::vec3(1.0f, 0.0f, 0.0f));
        AARect right_wall_area;
        right_wall_area.create(glm::vec2(right_wall, 0),glm::vec2(4, 480));
        renderer.addRect(right_wall_area, glm::vec3(1.0f, 0.0f, 0.0f));
        this->mode->renderControl(renderer);
    }
    
    template <typename TInput>
    void inputControl(TInput& input){
        if(input.pausePressed()){
            this->pauseToggle();
        }
        if(input.leftPressedOrDown()){
            this->primary_paddle->setVelocityX(-400.0f);
        }else if(input.rightPressedOrDown()){
            this->primary_paddle->setVelocityX(400.0f);
        }else{
            this->primary_paddle->setVelocityX(0.0f);
        }
    }

    GameObjectCollection<Paddle>& getPaddles();
};


#endif
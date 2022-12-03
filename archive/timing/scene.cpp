#include <scene.hpp>

Scene::Scene(){
    this->bricks = Bricks();
    this->score = 0;

    using namespace rapidxml;
    rapidxml::file<> xmlFile("data\\scenarios\\smoke_0.xml"); // Default template is char
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    {
        Paddle paddle;
        paddle.create(glm::vec2(
            atof(doc.first_node("Paddle")->first_node("Position")->first_node("X")->value()),
            atof(doc.first_node("Paddle")->first_node("Position")->first_node("Y")->value()))
        );
        paddle.setVelocityX(300.0f);
        this->paddles.push_back(paddle);
    }
    this->primary_paddle = &this->paddles.at(0);

    {
        Ball ball = Ball();
        ball.create(glm::vec2(200.0f, 200.0f), 8.0f, glm::vec2(-300.0f, 300.0f));
        this->balls.push_back(ball);
    }

    {
        Ball ball = Ball();
        ball.create(glm::vec2(200.0f, 200.0f), 8.0f, glm::vec2(300.0f, 300.0f));
        this->balls.push_back(ball);
    }

    for (int i = 0; i < 1; i++){
        Bricks::Brick brick;
        brick.active = true;
        brick.rect.create(glm::vec2(100.0f + i * 40.0f, 100.0f), glm::vec2(32.0f, 32.0f));
        this->bricks.bricks.push_back(brick);
    }

    this->mode = &null_game_object;
}

void Scene::gameLoop(float dt){
    int limit = 0;
    while (dt > 0.0f) {
        OnHit * on_hit = NULL;
        for (Ball& ball : this->balls){
            ball.move(dt);
        }
        for(Paddle& paddle : this->paddles){
            paddle.move(dt);
        }    

        dt = 0.0f;
        glm::vec2 normal = glm::vec2(0.0f, 0.0f);

        for (Ball& ball : this->balls){
            for(Bricks::Brick& brick : (this->bricks.bricks)){
                if(brick.active){
                    if(Intersector::circleIntersectsRect(ball.refCircle(), brick.getRect())){
                        if(this->shape_resolver.resolve(dt, normal, ball.refCircle(), brick.getRect(), ball.velocity)){
                            bounce_ball_destroy_brick.set(&ball, &brick, &this->score);
                            on_hit = &bounce_ball_destroy_brick;
                        }
                    }
                }
            }

            for(Paddle& paddle : this->paddles){
                if(Intersector::circleIntersectsRect(ball.refCircle(), paddle.refRect())){
                    if(this->shape_resolver.resolve(dt, normal, ball.refCircle(), paddle.refRect(), ball.velocity - paddle.velocity)){
                        ball_bounce_paddle.set(&ball, &paddle);
                        on_hit = &ball_bounce_paddle;
                    }
                }
            }

            if((ball.getTop() < top_wall) && (ball.velocity.y < 0.0f)){
                if(this->shape_resolver.resolve(dt, normal, ball.getTop(), top_wall, ball.velocity.y, glm::vec2(0.0f, 1.0f))){
                    ball_bounce_wall.set(&ball);
                    on_hit = &ball_bounce_wall;

                }
            }
            
            if((ball.getBottom() > bottom_wall) && (ball.velocity.y > 0.0f)){
                if(this->shape_resolver.resolve(dt, normal, ball.getBottom(), bottom_wall, ball.velocity.y, glm::vec2(0.0f, -1.0f))){
                    ball_bounce_wall.set(&ball);
                    on_hit = &ball_bounce_wall;

                }
            }

            if((ball.getLeft() < left_wall) && (ball.velocity.x < 0.0f)){
                if(this->shape_resolver.resolve(dt, normal, ball.getLeft(), left_wall, ball.velocity.x, glm::vec2(1.0f, 0.0f))){
                    ball_bounce_wall.set(&ball);
                    on_hit = &ball_bounce_wall;

                }
            }

            if((ball.getRight() > right_wall) && (ball.velocity.x > 0.0f)){
                if(this->shape_resolver.resolve(dt, normal, ball.getRight(), right_wall, ball.velocity.x, glm::vec2(-1.0f, 0.0f))){
                    ball_bounce_wall.set(&ball);
                    on_hit = &ball_bounce_wall; 
                }
            }
        }     

        for(Paddle& paddle : this->paddles){
            if((paddle.getLeft() < left_wall) && (paddle.velocity.x < 0.0f)){
                dt = fmaxf(dt, (paddle.getLeft() - left_wall) / paddle.velocity.x);
                paddle_hits_wall.set(&paddle);
                on_hit = &paddle_hits_wall;
            }

            if((paddle.getRight() > right_wall) && (paddle.velocity.x > 0.0f)){
                dt = fmaxf(dt, (paddle.getRight() - right_wall) / paddle.velocity.x);
                paddle_hits_wall.set(&paddle);
                on_hit = &paddle_hits_wall;
            }
        }

        for (Ball& ball : this->balls){
            ball.move(-dt);
        }
        for (Paddle& paddle : this->paddles){
            paddle.move(-dt);
        }

        if(on_hit){
            on_hit->update(normal);
        }
       
        limit++;
        if(limit > 100){
            break;
        }
    }
}

bool Scene::isPaused(){
    return this->mode == &this->pause_mode;
}

void Scene::addBrickGrid(BrickGrid& brick_grid){
    for(Bricks::Brick& brick :  brick_grid.makeBrick()){
        this->bricks.bricks.push_back(brick);
    }
}

void Scene::update(float dt){
    if(!this->isPaused()){
        this->gameLoop(dt);  
    }
    // this->mode->update(dt);
}

void Scene::pauseToggle(){
    if(this->mode == &this->null_game_object){
        this->mode = &this->pause_mode;
    }else{
        this->mode = &this->null_game_object;
    }
}







GameObjectCollection<Paddle>& Scene::getPaddles(){
    return this->paddles;
}

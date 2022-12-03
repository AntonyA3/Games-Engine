#include <game_loop.hpp>





struct CircleLineIntersection{
    bool hit; 
    float t0, t1;

    CircleLineIntersection& intersect(Circle& circle, glm::vec2 line_start, glm::vec2 vector){
        glm::vec2 circle_to_line_start = line_start - circle.position;
        float a_val = glm::dot(vector, vector);
        float b_val = 2.0f * glm::dot(vector, line_start - circle.position);
        float c_val =  glm::dot(circle.position, circle.position - 2.0f * line_start) + glm::dot(line_start, line_start) - circle.radius * circle.radius;
        float determinant = b_val * b_val - 4.0f * a_val * c_val;
        this->hit = determinant >= 0.0f;
        if (!hit){ 
            return *this;
        }
        this->t0 = ((-b_val) - sqrtf(determinant)) / (2.0f * a_val);
        this->t1 = ((-b_val) + sqrtf(determinant)) / (2.0f * a_val);
        return *this;
    }

    bool hitThis(){
        return this->hit;
    }

    float maxT(){
        return std::max(this->t0, this->t1);
    }
};


void GameLoop::ShapeResolver::reset(){
    this->time = 0.0f;
    this->normal = glm::vec2(0.0f, 0.0f);
}
template <int axis, int other_axis>
bool GameLoop::ShapeResolver::resolve(float start, float target, float min_bound, float max_bound, glm::vec2 start_point, glm::vec2 velocity, glm::vec2 normal){
    
    float t = (start - target) / velocity[axis];
    glm::vec2 pp = start_point - velocity * t;
    bool better = (t > this->time) && (pp[other_axis] >= min_bound) && (pp[other_axis] <= max_bound);
    if(better){
        this->time = t;
        this->normal = normal;
    }
    return better;
}

bool GameLoop::ShapeResolver::resolve(Circle& circle, AARect& rect, glm::vec2 velocity){
    // For each box points on the circle,find how far it is away from the rectangle
    bool better = false;
    // top
    {
        float t = (circle.getBottom() - rect.getTop()) / velocity.y;
        glm::vec2 point = circle.getBottomPoint() - velocity * t;

        if ((velocity.y > 0.0f) && (t > this->time) && (point.x >= rect.getLeft()) && (point.x <= rect.getRight())){
            this->time =  t;
            this->normal = glm::vec2(0.0f, -1.0f);
            better = true;
        }
        
    }
    //bottom
    {
        float t = (circle.getTop() - rect.getBottom()) / velocity.y;
        glm::vec2 point = circle.getTopPoint() - velocity * t;
        if ((velocity.y < 0.0f) && (t > this->time) && (point.x >= rect.getLeft()) && (point.x <= rect.getRight())){
            this->time = t;
            this->normal = glm::vec2(0.0f, 1.0f);
            better = true;

        }  
    }
    //right
    {
        float t = (circle.getLeft() - rect.getRight()) / velocity.x;
        glm::vec2 point = circle.getLeftPoint() - velocity * t;
        if((velocity.x < 0.0f) && (t > this->time) && (point.y >= rect.getTop()) && (point.y <= rect.getBottom())){
            this->time = t;
            this->normal = glm::vec2(1.0f, 0.0f);
            better = true;

        }
    }
    //left
    {
        float t = (circle.getRight() - rect.getLeft()) / velocity.x;
        glm::vec2 point = circle.getRightPoint() - velocity * t;
        if((velocity.x > 0.0f) && (t > this->time) && (point.y >= rect.getTop()) && (point.y <= rect.getBottom())){
            this->time = t;
            this->normal = glm::vec2(-1.0f, 0.0f);
            better = true;

        } 
    }
    
    glm::vec2 rect_verticies[4] = {
        rect.getTopLeft(),
        rect.getTopRight(),
        rect.getBottomLeft(),
        rect.getBottomRight()
    };

    for(int i = 0; i < 4; i++){
        CircleLineIntersection circle_intersection = CircleLineIntersection();
        circle_intersection.intersect(circle, rect_verticies[i], velocity);
        if (circle_intersection.hitThis()){
            float t = circle_intersection.hit ? circle_intersection.maxT() : 0.0f;
            if(t > this->time){
                this->time = t ;
                this->normal = glm::normalize(circle.position - (rect_verticies[i] + t * velocity));
                better = true;

            }   
        }
    }
    return better;
}



bool GameLoop::ShapeResolver::resolve(float start, float target, float velocity, glm::vec2 normal){
    bool better = false;
    if(velocity != 0){
        float t = (start - target) / velocity;
        better = t > this->time;
        if(better){
            this->time = t;
            this->normal = normal;
        }
    }
    return better;
}

void GameLoop::update(float dt){
    if(left_button->isPressedOrDown()){
        scene->paddles.at(0).setVelocityX(-100.0f);
    }else if(right_button->isPressedOrDown()){
        scene->paddles.at(0).setVelocityX(100.0f);
    }else{
        scene->paddles.at(0).setVelocityX(-0.0f);
    }
    

    this->shape_resolver.reset();
    int limit = 0;


    Ball * hit_ball;
    Paddle * hit_paddle;
    Bricks::Brick * hit_brick;

    float left_wall = this->scene->left_wall;
    float right_wall = this->scene->right_wall;
    float top_wall = this->scene->top_wall;
    float bottom_wall = this->scene->bottom_wall;

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
            *score +=10.0f;
            std::cout << "score is now: " << *score << std::endl;
            
        }
    };

    BounceBallDestroyBrick bounce_ball_destroy_brick;
    BallBounceOfPaddle ball_bounce_paddle;
    BallBounceOfWall ball_bounce_wall;
    PaddleHitsWall paddle_hits_wall;
    OnHit * on_hit;
    

    float time_chunk = dt;
    while (time_chunk > 0.0f)
    {
        OnHit * on_hit = NULL;

        // Move all Objects in the scene   
        for (Ball& ball : *this->balls){
            ball.move(time_chunk);
        }
        for(Paddle& paddle : *this->paddles){
            paddle.move(time_chunk);
        }
            
        // For each ball if the ball is intersecting anything in the scene
        // Find find the time that it has been intersecting object for 
        // The object normal
        for (Ball& ball : *this->balls){
            for(Bricks::Brick& brick : (this->bricks->bricks)){
                if(brick.active){
                    if(Intersector::circleIntersectsRect(ball.refCircle(), brick.getRect())){
                        if(this->shape_resolver.resolve(ball.refCircle(), brick.getRect(), ball.velocity)){
                            bounce_ball_destroy_brick.set(&ball, &brick, this->score);
                            on_hit = &bounce_ball_destroy_brick;
                        }
                    }
                }
            }

            for(Paddle& paddle : *this->paddles){
                if(Intersector::circleIntersectsRect(ball.refCircle(), paddle.refRect())){
                    if(this->shape_resolver.resolve(ball.refCircle(), paddle.refRect(), ball.velocity - paddle.velocity)){
                        ball_bounce_paddle.set(&ball, &paddle);
                        on_hit = &ball_bounce_paddle;
                    }
                }
            }

            if((ball.getTop() < top_wall) && (ball.velocity.y < 0.0f)){
                if(this->shape_resolver.resolve(ball.getTop(), top_wall, ball.velocity.y, glm::vec2(0.0f, 1.0f))){
                    ball_bounce_wall.set(&ball);
                    on_hit = &ball_bounce_wall;

                }
            }
            
            if((ball.getBottom() > bottom_wall) && (ball.velocity.y > 0.0f)){
                if(this->shape_resolver.resolve(ball.getBottom(), bottom_wall, ball.velocity.y, glm::vec2(0.0f, -1.0f))){
                    ball_bounce_wall.set(&ball);
                    on_hit = &ball_bounce_wall;

                }
            }

            if((ball.getLeft() < left_wall) && (ball.velocity.x < 0.0f)){
                if(this->shape_resolver.resolve(ball.getLeft(), left_wall, ball.velocity.x, glm::vec2(1.0f, 0.0f))){
                    ball_bounce_wall.set(&ball);
                    on_hit = &ball_bounce_wall;

                }
            }

            if((ball.getRight() > right_wall) && (ball.velocity.x > 0.0f)){
                if(this->shape_resolver.resolve(ball.getRight(), right_wall, ball.velocity.x, glm::vec2(-1.0f, 0.0f))){
                    ball_bounce_wall.set(&ball);
                    on_hit = &ball_bounce_wall; 
                }
            }
        }     

        //Paddle See is paddle hits the wall earlier than everything else
        for(Paddle& paddle : *this->paddles){
            if((paddle.getLeft() < left_wall) && (paddle.velocity.x < 0.0f)){
                if(this->shape_resolver.resolve(paddle.getLeft(), left_wall, paddle.velocity.x, glm::vec2(1.0f, 0.0f))){
                    paddle_hits_wall.set(&paddle);
                    on_hit = &paddle_hits_wall;
                }
            }

            if((paddle.getRight() > right_wall) && (paddle.velocity.x > 0.0f)){
                if(this->shape_resolver.resolve(paddle.getRight(), right_wall, paddle.velocity.x, glm::vec2(-1.0f, 0.0f))){
                    paddle_hits_wall.set(&paddle);
                    on_hit = &paddle_hits_wall;
                }
            }
        }

        time_chunk = this->shape_resolver.time;
    
        // Reverse all objects in the scene to the position where the first object hit something
        for (Ball& ball : *this->balls){
            ball.move(-time_chunk);
        }
        for (Paddle& paddle : *this->paddles){
            paddle.move(-time_chunk);
        }

        // Depending on the object that was hit in the frame, change the velocity of the object
        if(on_hit){
            on_hit->update(this->shape_resolver.normal);
        }
       
        limit++;
        if(limit > 10){
            break;
        }


    }
}    

GameLoop::GameLoop(
        Scene& scene,
        int &score,
        GameObjectCollection<Paddle> &paddles,
        GameObjectCollection<Ball> &balls,
        Bricks &bricks,
        KeyboardButton &left_button,
        KeyboardButton &right_button
    ){
    this->scene = &scene;
    this->score = &score;
    this->paddles = &paddles;
    this->balls = &balls;
    this->bricks = &bricks;
    this->left_button = &left_button;
    this->right_button = &right_button;
}


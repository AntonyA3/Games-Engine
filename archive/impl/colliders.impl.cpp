#define ENABLE_DEBUG_LOGGER
#include <macros/debug_logger.hpp>

#include <stdio.h>
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#define GAMES_ENGINE_USE_IMGUI_DEBUGING
#include <game_loop.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <shapes/aa_rect.hpp>
#include <shapes/circle.hpp>
#include <complete_window.hpp>
#include <complete_window_data.hpp>
#include <renderer.hpp>
#include <time_controller.hpp>
#include <intersector.hpp>
#include <input/input_controller.hpp>
#include <extra_vector_math.hpp>
#ifndef SHADER_FILE_PATH
#define SHADER_FILE_PATH "./data/shaders/"
#endif

void processWindowEvent(Renderer& renderer, SDL_WindowEvent &event, CompleteWindow& complete_window){
    switch (event.event)
    {
    case SDL_WINDOWEVENT_RESIZED:
        complete_window.m_sdl_window_wrapper.m_width = (int)event.data1;
        complete_window.m_sdl_window_wrapper.m_height = (int)event.data2;
        
        renderer.setWidthHeight(complete_window.m_sdl_window_wrapper.m_width, complete_window.m_sdl_window_wrapper.m_height);
        break;                
    default:
        break;
    }
}


enum Circle_Object_State{
    CIRCLE_OBJECT_STATE_DEFAULT,
    CIRCLE_OBJECT_STATE_MOVING,
    CIRCLE_OBJECT_STATE_VELOCITY_CHANGING
};

struct Collision{
    bool hit;
    float t;
    glm::vec2 normal;
};


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



struct ResolvePolygonPolygon{
    glm::vec2 normal = glm::vec2(0,0);
    float time_inside = 0.0f;

    
    bool subCalculation(Polygon& polygon_0, Polygon& polygon_1, glm::vec2 velocity){
        bool hit = false;
        std::vector<glm::vec2> vertices = polygon_0.getVerticies();
        std::vector<Edge> other_edges = polygon_1.getEdges();
        // for(int i = 0; i < vertices.size(); i++){
        for (glm::vec2 vertex : vertices ){
            for(Edge edge: other_edges){
                glm::vec2 normal = glm::normalize(edge.getNormal());
                ExtraVectorMath::VectorMathResult result = ExtraVectorMath::pointintersectLineT(vertex, -velocity, edge.p0, normal);
                if(result.hit){
                    glm::vec2 line_point = vertex - velocity * result.t;
                    result.hit = ExtraVectorMath::isPointOnLine(edge.p0, edge.p1, line_point);
                    if(result.hit){
                        if(result.t > time_inside){
                            this->time_inside = result.t;
                            this->normal = normal;
                    
                            hit = true;
                        }
                    }
                }
            }
        }
        return hit;
    }

    void calculate(Polygon& polygon_0, Polygon& polygon_1, glm::vec2 velocity){
        this->subCalculation(polygon_0, polygon_1, velocity);
        if(this->subCalculation(polygon_1, polygon_0, -velocity)){
            this->normal *= -1.0f;
        }
    }     

};

struct ResolveResult{
    glm::vec2 normal = glm::vec2(0,0);
    float time_inside = 0.0f;
};

struct IRidgedBody{
    glm::vec2 velocity;

    virtual void move(float delta) = 0;
    void reverseMove(float delta){
        this->move(-delta);
    }
    void reflectVelocity(glm::vec2 normal){
        this->velocity = glm::reflect(this->velocity, normal);
    }
    virtual float getLeft() = 0;
    virtual float getRight() = 0;
    virtual float getTop() = 0;
    virtual float getBottom() = 0;
    virtual glm::vec2 getVelocity() = 0;
    virtual bool intersects(AARect& rect) = 0;
    virtual bool intersects(Circle& circle) = 0;
    virtual bool intersects(Polygon& polygon) = 0;

    virtual bool intersects(IRidgedBody * other_body) = 0;
    virtual void resolve(ResolveResult& resolve_result, IRidgedBody * other_body) = 0;
    virtual void resolve(ResolveResult& resolve_result, Polygon& polygon) = 0;
    virtual void resolve(ResolveResult& resolve_result, AARect& rect) = 0;
    virtual void resolve(ResolveResult& resolve_result, Circle& circle) = 0;


};

struct PolygonCollider : public IRidgedBody{
    Polygon polygon;
    PolygonCollider& create(Polygon polygon, glm::vec2 velocity){
        this->polygon = polygon;
        this->velocity = velocity;
    }

    void move(float delta){
        polygon.move(velocity, delta);
    }
    float getLeft(){ return polygon.getLeft();}
    float getRight(){ return polygon.getRight();}
    float getTop(){ return polygon.getTop();}
    float getBottom(){ return polygon.getBottom();}
    glm::vec2 getVelocity(){return this->velocity;}
    bool intersects(AARect& rect){
        Polygon rect_polygon = Polygon().create(rect);
        return Intersector::polygonIntersectsPolygon(this->polygon, rect_polygon);
    }
    bool intersects(Circle& circle){
        return Intersector::circleIntersectsPolygon(circle, this->polygon);
    }
    bool intersects(Polygon& polygon){
        return Intersector::polygonIntersectsPolygon(polygon, this->polygon);
    }
    bool intersects(IRidgedBody * other_body){
        other_body->intersects(polygon);
    }

    void resolve(ResolveResult& resolve_result, IRidgedBody * other_body){
        other_body->resolve(resolve_result, this->polygon);
    }

    void resolve(ResolveResult& resolve_result, Polygon& polygon){
        ResolvePolygonPolygon resol;
        resol.calculate(this->polygon, polygon, velocity);
        resolve_result.time_inside = resol.time_inside;
        resolve_result.normal = resol.normal;
    }

    void resolve(ResolveResult& resolve_result, AARect& rect){
        Polygon rect_as_polygon = Polygon().create(rect);
        this->resolve(resolve_result, rect_as_polygon);
    }

    void resolve(ResolveResult& resolve_result, Circle& circle){
        std::cout << "not yet implemented" << std::endl;
    }



};

struct CircleCollider : public IRidgedBody{
    Circle circle;
    CircleCollider& create(Circle circle, glm::vec2 velocity){
        this->circle = circle;
        this->velocity = velocity;
    }

    void move(float delta){
        circle.move(velocity, delta);
    }
    float getLeft(){ return circle.getLeft();}
    float getRight(){ return circle.getRight();}
    float getTop(){ return circle.getTop();}
    float getBottom(){ return circle.getBottom();}
    glm::vec2 getVelocity(){return this->velocity;}
    bool intersects(AARect& rect){
        return Intersector::circleIntersectsRect(circle, rect);
    }
    bool intersects(Circle& circle){
        std::cout << "Circle intersects circle not yet implemented" << std::endl;
        return false;
    }
    bool intersects(Polygon& polygon){
        return Intersector::circleIntersectsPolygon(this->circle, polygon);
    }
    bool intersects(IRidgedBody * other_body){
        other_body->intersects(circle);
    }

    void resolve(ResolveResult& resolve_result, IRidgedBody * other_body){
        other_body->resolve(resolve_result, this->circle);
    }

    void resolve(ResolveResult& resolve_result, Polygon& polygon){
      
        std::cout <<" not yest implemented" << std::endl;
    }

    void resolve(ResolveResult& resolve_result, AARect& rect){
        GameLoop::ShapeResolver resol;
        resol.resolve(circle, rect, this->velocity);
        resolve_result.time_inside = resol.time;
        resolve_result.normal = resol.normal;
    }

    void resolve(ResolveResult& resolve_result, Circle& circle){
        std::cout << "not yet implemented" << std::endl;
    }
};

struct ClosestHit{
    float next_time_remaining = 0.0f;
    glm::vec2 hit_normal = glm::vec2(0.0f, 0.0f);

    bool addWall(bool hit_predicate, float time_from_hit, glm::vec2 normal){
        bool predicate = (hit_predicate && (time_from_hit > next_time_remaining));
    
        next_time_remaining = predicate ? time_from_hit : next_time_remaining;
        hit_normal = predicate ? normal : hit_normal; 
        return predicate;
    }  
    
                    
};



int main(int argc, char const *argv[])
{

    CompleteWindow complete_window;
    {        
        CompleteWindowData complete_window_data = {
            {
                SDL_INIT_VIDEO, 
                std::string("Collider Tester"),
                640,
                480,
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                true,
                true,
                SDL_FALSE
            },
            {
                3, 
                3
            }
        };
        complete_window.create(complete_window_data);
    }
    InputController input_controller = InputController().create();
    Renderer renderer = Renderer() 
        .create()        
        .setWidthHeight(640, 480)
        .setBackgroundColor(0.5f, 0.5f, 0.5f, 1.0f)
        .enableAlphaTransparency();


    TimeController time_controller;
    
    Circle t_circle;
    t_circle.create(glm::vec2(32.0f, 32.0f), 32.0f), glm::vec2(100.0f, 100.0f)
    CircleCollider circle_collider = CircleCollider().create(t_circle);
    glm::vec3 circle_color = glm::vec3(1.0f, 0.5f, 1.0f);

    SweepedRect sweeped_rect = SweepedRect();
    sweeped_rect.start = glm::vec2(100.0f, 100.0f);
    sweeped_rect.hh = 50.0f;
    sweeped_rect.direction = glm::vec2(50.0f, 50.0f);


    PolygonCollider polygon_collider = PolygonCollider().create( Polygon().create(sweeped_rect), glm::vec2(300.0f, 300.0f)); 
    glm::vec3 polygon_color = glm::vec3(1.0f, 0.5f, 1.0f);

    AARect rect;
    rect.create(glm::vec2(200.0f, 200.0f), glm::vec2(100.0f, 75.0f));
    bool paused = false;

    time_controller.create();

    while (complete_window.isActive())
    {
        while (complete_window.polledEvent())
        {   

            SDL_Event& event = complete_window.nextEvent();
            switch (event.type)
            {
            case SDL_QUIT:
                complete_window.m_sdl_window_wrapper.terminate();
                break;
            case SDL_WINDOWEVENT:
                processWindowEvent(renderer, event.window, complete_window);
                break;
            }
        }

        renderer.clearRender();
        renderer.begin();   
        
        
        input_controller.update();
        
        if(input_controller.keyboardController().inspectorButton().isPressed()){
            paused = !paused;
        }

        if(paused){
            if( input_controller.mouseController().leftButton().isDown()) {
                if(circle_collider.circle.containsPoint(input_controller.mouseController().mouseCursor().getPosition())){
                    circle_collider.circle.move(input_controller.mouseController().mouseCursor().getDelta());
                }else if(polygon_collider.polygon.containsPoint(input_controller.mouseController().mouseCursor().getPosition())){
                    polygon_collider.polygon.move(input_controller.mouseController().mouseCursor().getDelta());
                }
            }
        }
        if(!paused){
            std::vector<IRidgedBody *> ridged_bodies;
            ridged_bodies.push_back(&circle_collider);
            ridged_bodies.push_back(&polygon_collider);
            IRidgedBody * hit_object = NULL;
            int i = 0;
            float time_remaining = time_controller.getDeltaTime();
            while(time_remaining > 0.0f){  
                ClosestHit closest_target_hit;
                for(IRidgedBody * body: ridged_bodies){
                    body->move(time_remaining);
                    //cicle floor test
                    if(closest_target_hit.addWall( 
                        (body->getBottom() > 480.0f) && (body->getVelocity().y > 0.0f), 
                        (body->getBottom() - 480.0f) / body->getVelocity().y,
                        glm::vec2(0.0f, -1.0f)
                    )){
                        // no_hit0_circle1_polygon_2 = 1;
                        hit_object = body;
                    }
                    //ceiling test
                    if(closest_target_hit.addWall( 
                        (body->getTop() < 0.0f), 
                        (body->getTop() - 0.0f) / body->getVelocity().y,
                        glm::vec2(0.0f, 1.0f)
                    )){
                        hit_object = body;
                    }
                    //left test
                    if(closest_target_hit.addWall( 
                        (body->getLeft() < 0.0f), 
                        (body->getLeft() - 0.0f) / body->getVelocity().x,
                        glm::vec2(1.0f, 0.0f)
                    )){
                        hit_object = body;
                    }
                    //right test
                    if(closest_target_hit.addWall( 
                        (body->getRight() > 640.0f), 
                        (body->getRight() - 640.0f) / body->getVelocity().x,
                        glm::vec2(-1.0f, 0.0f)
                    )){
                        hit_object = body;
                    }

                    //Against All other ridged bodies
                    for(IRidgedBody * other_body: ridged_bodies){
                        if(body != other_body){
                            if(body->intersects(other_body)){
                                ResolveResult resolve_result;
                                body->resolve(resolve_result, other_body);
                                if(resolve_result.time_inside > closest_target_hit.next_time_remaining){
                                    closest_target_hit.next_time_remaining = resolve_result.time_inside;
                                    closest_target_hit.hit_normal = resolve_result.normal;
                                    hit_object = body;
                                }
                            }

                        }
                    }
                    // rect test
                    if(body->intersects(rect)){
                        ResolveResult resolve_result;
                        body->resolve(resolve_result, rect);
                        if(resolve_result.time_inside > closest_target_hit.next_time_remaining){
                            closest_target_hit.next_time_remaining = resolve_result.time_inside;
                            closest_target_hit.hit_normal = resolve_result.normal;
                            hit_object = body;
                        }
                    }
                } 
                
                for(IRidgedBody *  body: ridged_bodies){
                    body->reverseMove( closest_target_hit.next_time_remaining);
                }

                // Either all the time has elapsed or only some of the time elapsed
                time_remaining = closest_target_hit.next_time_remaining;
                if(hit_object){
                    hit_object->reflectVelocity(closest_target_hit.hit_normal);
                }
          
                i++;
                if(i > 100){
                    break;
                }
            }
        }

        complete_window.beginFrame();


        ImGui::Begin("Inspector");
        ImGui::Text("Circle Intersecting Rect: %s", (Intersector::circleIntersectsRect(circle_collider.circle, rect)) ? "true" : "false");
        ImGui::Text("Polygon Contains mouse: %s", (polygon_collider.polygon.containsPoint(input_controller.mouseController().mouseCursor().getPosition())) ? "true" : "false");

        ImGui::End();


        
        Polygon rect_as_polygon = Polygon().create(rect);;
        ImGui::Begin("Polygon Intersection");
        ImGui::Text("Polygon is intersecting the Rect %s", (Intersector::polygonIntersectsPolygon(polygon_collider.polygon, rect_as_polygon)) ? "true" : "false");
        ImGui::End();
    

        renderer.addCircle(circle_collider.circle, circle_color);
        renderer.addRect(rect, glm::vec3(1.0f, 1.0f, 1.0f));
        renderer.addPolygon(polygon_collider.polygon, glm::vec3(1.0f, 1.0f, 1.0f));
        renderer.render();
        complete_window.renderFrame();
        SDL_GL_SwapWindow(complete_window.m_sdl_window_wrapper.getWindow());  
        time_controller.update();   
    }
    
    complete_window.m_sdl_window_wrapper.destroy();
    SDL_Quit();
    return 0;
}

#include <stdio.h>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <imgui/imgui_internal.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_sdl.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>

#include <rapidxml-1.13/rapidxml_utils.hpp>
#include <rapidxml-1.13/rapidxml_ext.h>

/// [Section] Enums
enum Base_Events_ID {
    No_Event = 0,
    Quit_Event,
    Resize_Window_Event
};

enum FileReadStatus{
    FileReader_NotRead,
    FileRead_Success,
    FileRead_Failed
};

typedef enum ButtonState{
    ButtonState_Pressed,
    ButtonState_Down,
    ButtonState_Up,
    ButtonState_Released
};

// [Section] Basic Functions

std::string readFile(std::string filename);

std::string readFile(std::string filename){
    std::stringstream ss;
    std::ifstream my_read_file;
    my_read_file.open(filename);
    char read_buffer[2048];
    bool open = my_read_file.is_open();
    assert(open);
    if(open){
        while (!my_read_file.eof())
        {
            my_read_file.getline(read_buffer, 2048);
            ss << read_buffer;
            if(!my_read_file.eof()){
                ss << "\n";
            }
        }  
        my_read_file.close();
    }
    return ss.str();
} 

Base_Events_ID mapToBaseEvent(SDL_Event event){
    Base_Events_ID base_event = No_Event;
    base_event = (event.type == SDL_QUIT) ? Quit_Event : base_event;
    base_event = (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) ? 
        Resize_Window_Event : 
        base_event;
    return base_event;
}

struct AARect
{
    glm::vec2 position;
    glm::vec2 size;
    AARect(){};
    AARect(glm::vec2 position, glm::vec2 size);
    void create(glm::vec2 position, glm::vec2 size);
    float getTop();
    float getBottom();
    float getLeft();
    float getRight();
    glm::vec2 getTopLeft();
    glm::vec2 getTopRight();
    glm::vec2 getBottomLeft();
    glm::vec2 getBottomRight();
    glm::vec2 getCentre();
    float getWidth();
    float getHeight();
};


AARect::AARect(glm::vec2 position, glm::vec2 size){
    this->create(position, size);
}

void AARect::create(glm::vec2 position, glm::vec2 size){
    this->position = position;
    this->size = size;
}

float AARect::getTop(){
    return this->position.y;
}

float AARect::getBottom(){
    return this->position.y + this->size.y;
}

float AARect::getLeft(){
    return this->position.x;
}

float AARect::getRight(){
    return this->position.x + this->size.x;
}

glm::vec2 AARect::getTopLeft(){
    return this->position;
}
glm::vec2 AARect::getTopRight(){
    glm::vec2 out = this->position;
    out.x += this->size.x;
    return out;
}

glm::vec2 AARect::getBottomLeft(){
    glm::vec2 out = this->position;
    out.y += this->size.y;
    return out;
}

glm::vec2 AARect::getBottomRight(){
    return this->position + this->size;
}

glm::vec2 AARect::getCentre(){
    return glm::vec2(this->position.x + 0.5f * this->size.x, this->position.y + 0.5f * this->size.y);
}

float AARect::getWidth()
{
    return this->size.x;
}

float AARect::getHeight()
{
    return this->size.y;
}

AARect& join(AARect& rect, AARect& other_rect){
    float x = fminf(rect.position.x, other_rect.position.x);
    float y = fminf(rect.position.y, other_rect.position.y);
    float sx = fmaxf(other_rect.getRight(), rect.getRight()) - x;
    float sy = fmaxf(other_rect.getBottom(), rect.getBottom()) - y;
    rect.position.x = x;
    rect.position.y = y;
    rect.size.x = sx;
    rect.size.y = sy;
    return rect;
}

void move(AARect& rect, glm::vec2 movement){
    rect.position += movement;
}

bool contains(AARect& rect, glm::vec2 point){
    return point.x >= rect.getLeft() && point.x <= rect.getRight() &&
        point.y >= rect.getTop() && point.y <= rect.getBottom();
}

struct Circle
{
    glm::vec2 position;
    float radius;

    void create(glm::vec2 position, float radius);
    AARect toRect();
    float getTop();
    float getBottom();
    float getLeft();
    float getRight();
    glm::vec2 getBottomPoint();
    glm::vec2 getTopPoint();
    glm::vec2 getLeftPoint(); 
    glm::vec2 getRightPoint();
};

void move(Circle& circle, glm::vec2 movement){
    circle.position += movement;
}

void move(Circle& circle, glm::vec2 velocity, float delta_time){
    circle.position += velocity * delta_time;
}

bool contains(Circle circle, glm::vec2 point){
    return glm::length2(point - circle.position) <= circle.radius * circle.radius;
}

void Circle::create(glm::vec2 position, float radius){
    this->position = position;
    this->radius = radius;
}


AARect Circle::toRect(){
    AARect rect;
    glm::vec2 pos = glm::vec2(this->position.x - this->radius, this->position.y - this->radius);
    float diameter = 2.0f * this->radius;
    glm::vec2 size = glm::vec2(diameter, diameter);
    rect.create(pos, size);
    return rect;
}


float Circle::getTop(){
    return this->position.y - this->radius;
}

float Circle::getBottom(){
    return this->position.y + this->radius;
}

float Circle::getLeft(){
    return this->position.x - this->radius;
}

float Circle::getRight(){
    return this->position.x + this->radius;
}

glm::vec2 Circle::getBottomPoint(){
    return glm::vec2(this->position.x, getBottom());
}

glm::vec2 Circle::getTopPoint(){
    return glm::vec2(this->position.x, getTop());
}

glm::vec2 Circle::getLeftPoint(){
    return glm::vec2(getLeft(), this->position.y);
} 

glm::vec2 Circle::getRightPoint(){
    return glm::vec2(getRight(), this->position.y);
}


struct SweepedRect
{
    glm::vec2 start;
    float hh;
    glm::vec2 direction;
    void create(glm::vec2 start, float half_height, glm::vec2 direction);
};

void SweepedRect::create(glm::vec2 start, float half_height, glm::vec2 direction){
    this->start = start;
    this->hh = half_height;
    this->direction = direction;
}

struct Edge
{
    glm::vec2 p0, p1;
    Edge& create(glm::vec2 p0, glm::vec2 p1);
    glm::vec2 asVector();
    glm::vec2 getNormal();
};

Edge& Edge::create(glm::vec2 p0, glm::vec2 p1){
    this->p0 = p0;
    this->p1 = p1;
    return *this;
}

glm::vec2 Edge::asVector(){
    return this->p1 - this->p0;
}

glm::vec2 Edge::getNormal(){
    glm::vec2 vector = this->asVector();
    return glm::vec2(-vector.y, vector.x);
}

struct Polygon
{
    std::vector<glm::vec2> verticies;
    AARect rect;
    public:
    Polygon(){}
    AARect toRect();
    std::vector<glm::vec2>& getVerticies();
    std::vector<Edge> getEdges();
    float getLeft();
    float getRight();
    float getTop();
    float getBottom();
};

struct RectVerticies{
    glm::vec3 top_left;
    glm::vec3 top_right;
    glm::vec3 bottom_left;
    glm::vec3 bottom_right;
}; 

void create(RectVerticies& rect_verticies, AARect& rect);

void create(RectVerticies& rect_verticies, AARect& rect){
    rect_verticies.top_left = glm::vec3(rect.getTopLeft(), 0.0f);
    rect_verticies.top_right = glm::vec3(rect.getTopRight(), 0.0f);
    rect_verticies.bottom_left = glm::vec3(rect.getBottomLeft(), 0.0f);
    rect_verticies.bottom_right = glm::vec3(rect.getBottomRight(), 0.0f);
}


void create(Polygon& polygon, AARect& rect){
    polygon.verticies.clear();
    RectVerticies rect_verticies;
    create(rect_verticies, rect);
    polygon.verticies.clear();
    polygon.verticies.push_back(glm::vec2(rect_verticies.bottom_left.x, rect_verticies.bottom_left.y));
    polygon.verticies.push_back(glm::vec2(rect_verticies.bottom_right.x, rect_verticies.bottom_right.y));
    polygon.verticies.push_back(glm::vec2(rect_verticies.top_right.x, rect_verticies.top_right.y));
    polygon.verticies.push_back(glm::vec2(rect_verticies.top_left.x, rect_verticies.top_left.y));
    polygon.rect = rect;
}

void create(Polygon& polygon, SweepedRect& rect);
void move(Polygon& polygon, glm::vec2 movement);
void move(Polygon& polygon, glm::vec2 velocity, float dt);
bool contains(Polygon& polygon, glm::vec2 point);

namespace ExtraVectorMath{
    struct VectorMathResult{
        bool hit;
        float t;
    };
    VectorMathResult pointintersectLineT(glm::vec2 r_line_start, glm::vec2 r_line_velocity, glm::vec2 target_line_point, glm::vec2 target_line_normal);
    float projectionT(glm::vec2 l0, glm::vec2 p, glm::vec2 n);
    glm::vec2 projectionPoint(glm::vec2 l0, glm::vec2 p, glm::vec2 n);
    float pointOnLineT(glm::vec2 point, glm::vec2 start, glm::vec2 end);
    float pointOnLineT_2(glm::vec2 point, glm::vec2 start, glm::vec2 line_vector);
    glm::vec2 lineClamp(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 line_point, glm::vec2 vector);
    bool isPointOnLine(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 point);
    glm::vec2 lineClamp(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 line_point);
    glm::vec2 minPoint(std::vector<glm::vec2>& points, glm::vec2 vector);
    glm::vec2 maxPoint(std::vector<glm::vec2>& points, glm::vec2 vector);

}

void create(Polygon& polygon, SweepedRect& rect){
    glm::vec2 normal = glm::normalize(glm::vec2(-rect.direction.y, rect.direction.x));
    polygon.verticies.clear();
    polygon.verticies.push_back(rect.start + normal * rect.hh);
    polygon.verticies.push_back(rect.start + rect.direction + normal * rect.hh);
    polygon.verticies.push_back(rect.start + rect.direction - normal * rect.hh);
    polygon.verticies.push_back(rect.start - normal * rect.hh);

    float min_x = ExtraVectorMath::maxPoint(polygon.verticies, glm::vec2(-1.0f, 0.0f)).x;
    float max_x = ExtraVectorMath::maxPoint(polygon.verticies, glm::vec2(1.0f, 0.0f)).x;
    float min_y = ExtraVectorMath::maxPoint(polygon.verticies, glm::vec2(0.0f, -1.0f)).y;
    float max_y = ExtraVectorMath::maxPoint(polygon.verticies, glm::vec2(1.0f, 1.0f)).y;
    polygon.rect.create(glm::vec2(min_x, min_y), glm::vec2(max_x - min_x, max_y - min_y));

}

bool contains(Polygon& polygon, glm::vec2 point){
    std::vector<Edge> edges = polygon.getEdges();
    bool contains = true;
    for(int i = 0; i < edges.size(); i++){
        contains = contains && ExtraVectorMath::projectionT(point, edges.at(i).p0, edges.at(i).getNormal()) > 0.0f;
    }
    return contains;
}

void move(Polygon& polygon, glm::vec2 movement){
    for(int i = 0; i < polygon.verticies.size(); i++){
        polygon.verticies.at(i) += movement;
    }
}

void move(Polygon& polygon, glm::vec2 velocity, float dt){
    ::move(polygon, velocity * dt);
}


ExtraVectorMath::VectorMathResult ExtraVectorMath::pointintersectLineT(glm::vec2 r_line_start, glm::vec2 r_line_velocity, glm::vec2 target_line_point, glm::vec2 target_line_normal){
    VectorMathResult vector_math_result;
    
    float determinant = glm::dot(target_line_normal, r_line_velocity);
    if(determinant == 0.0f) {
        vector_math_result.hit = false;
        return vector_math_result;
    };
    vector_math_result.hit = true;
    vector_math_result.t = glm::dot(target_line_point - r_line_start, target_line_normal) / determinant;

    return vector_math_result;
}


/// @brief Given a point on the line, a line normal and a point not on the line, Calculate
/// @param l0 The point away from the line
/// @param p The point on the line
/// @param n The line normal
/// @return The relative distance to the closest point on the line
float ExtraVectorMath::projectionT(glm::vec2 l0, glm::vec2 p, glm::vec2 n){
    return glm::dot(p - l0, n) / glm::dot(n, n);
}

glm::vec2 ExtraVectorMath::projectionPoint(glm::vec2 l0, glm::vec2 p, glm::vec2 n){
    float t = projectionT(l0, p, n);
    return l0 + n * t;
}


/// @brief Given a point on a line, the start of the line and the end of the line
/// @param point The point on the line
/// @param start The point at start of the line
/// @param end The point at end of the line
/// @return The reletive distance of the point along the line
float ExtraVectorMath::pointOnLineT(glm::vec2 point, glm::vec2 start, glm::vec2 end){
    glm::vec2 line_vector = end - start;
    return glm::dot(point - start, line_vector) / glm::dot(line_vector, line_vector);
}


float ExtraVectorMath::pointOnLineT_2(glm::vec2 point, glm::vec2 start, glm::vec2 line_vector){
    return glm::dot(point - start, line_vector) / glm::dot(line_vector, line_vector);
}

glm::vec2 ExtraVectorMath::lineClamp(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 line_point, glm::vec2 vector){
    float t = glm::dot(line_point - line_start, vector) / glm::dot(vector, vector);
    return 
        (t <= 0.0f) ? line_start :
        (t >= 1.0f) ? line_end :
        line_point;
}

bool ExtraVectorMath::isPointOnLine(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 point){
    float t = pointOnLineT(point, line_start, line_end);
    return  (t >= 0.0f) && (t <= 1.0f);
}

glm::vec2 ExtraVectorMath::lineClamp(glm::vec2 line_start, glm::vec2 line_end, glm::vec2 line_point){
    glm::vec2 vector = line_end - line_start;
    return lineClamp(line_start, line_end, line_point, vector);
}



glm::vec2 ExtraVectorMath::maxPoint(std::vector<glm::vec2>& points, glm::vec2 vector){
    float dot_product = std::numeric_limits<float>::lowest();
    int index = 0;
    for(int i = 0; i < points.size(); i++){
        float new_dot = glm::dot(points.at(i), vector);
        bool better = new_dot > dot_product;
        dot_product = better ? new_dot : dot_product;
        index = better ? i : index;
    }
    return points.at(index);
}

glm::vec2 ExtraVectorMath::minPoint(std::vector<glm::vec2>& points, glm::vec2 vector){
    float dot_product = std::numeric_limits<float>::infinity();
    int index = 0;
    for(int i = 0; i < points.size(); i++){
        float new_dot = glm::dot(points.at(i), vector);
        bool better = new_dot < dot_product;
        dot_product = better ? new_dot : dot_product;
        index = better ? i : index;
    }
    return points.at(index);

}

AARect Polygon::toRect(){
    return rect;
}

std::vector<glm::vec2>& Polygon::getVerticies(){
    return this->verticies;
}


std::vector<Edge> Polygon::getEdges(){
    std::vector<Edge> edges;
    for(int i = 0; i < this->verticies.size(); i++){
        Edge edge;
        edge.create(this->verticies.at(i), this->verticies.at((i + 1) % this->verticies.size()));
        edges.push_back(edge);
    }
    return edges;
}


float Polygon::getLeft(){
    return ExtraVectorMath::maxPoint(this->verticies, glm::vec2(-1.0f, 0.0f)).x;
}
float Polygon::getRight(){
    return ExtraVectorMath::maxPoint(this->verticies, glm::vec2(1.0f, 0.0f)).x;

}
float Polygon::getTop(){
    return ExtraVectorMath::maxPoint(this->verticies, glm::vec2(0.0f, -1.0f)).y;

}
float Polygon::getBottom(){
    return ExtraVectorMath::maxPoint(this->verticies, glm::vec2(0.0f, 1.0f)).y;

}

struct Capsule
{
    glm::vec2 position;
    float radius;
    glm::vec2 direction;    

    void create(glm::vec2 position, float radius, glm::vec2 direction);
    Circle getStartCircle();
    Circle getEndCircle();
    Polygon getMidSection();
    glm::vec2 end();
    std::string toString();
};




void Capsule::create(glm::vec2 position, float radius, glm::vec2 direction){
    this->position = position;
    this->radius = radius;
    this->direction = direction;
}

void sweep(Capsule& capsule, glm::vec2 movement){
    glm::vec2 new_end = capsule.end() + movement;
    capsule.position = capsule.end();  
    capsule.direction = new_end - capsule.position;
}


glm::vec2 Capsule::end(){
    return this->position + this->direction;
}


Circle Capsule::getStartCircle(){
    Circle circle;
    circle.create(this->position, this->radius);
    return circle;
}

Circle Capsule::getEndCircle(){
    Circle circle = this->getStartCircle();
    move(circle, this->direction);
    return circle;
}

Polygon Capsule::getMidSection(){
    SweepedRect sweep_rect;
    sweep_rect.create(this->position, this->radius, this->direction);
    Polygon polygon;
    ::create(polygon, sweep_rect);
    return polygon;
}

std::string Capsule::toString(){
    std::stringstream ss;
    ss << "Capsule: {\n";
    ss << "\tposition: {x:" << this->position.x << ", y: " << this->position.y << "}\n";
    ss << "\tradius: " << this->radius << "\n"; 
    ss << "\tdirection: {x:" << this->direction.x << ", y: " << this->direction.y << "}\n";
    ss << "}";
    return ss.str();
}

struct GLutils
{
    GLuint makeProgram(std::string vertex_file, std::string fragment_file);
    GLuint makeShader(std::string shader_file, GLenum shader_type);
    GLuint makeProgramFromContent(const char *  vertex_content, const char * fragment_content);
    GLuint makeShaderFromContent(const char * shader_content, GLenum shader_type);
    GLuint attachShadersAndLinkProgram(GLuint& vertex_shader, GLuint& fragment_shader);
};


GLuint GLutils::attachShadersAndLinkProgram(GLuint& vertex_shader, GLuint& fragment_shader){
    GLuint program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    int status;
    GLchar info_log[1000]; 
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    glGetProgramInfoLog(program, 1000, NULL, &info_log[0]);
    if (!status){
        std::cout << "Shader status compile failed" << "\n";       
        std::cout << info_log << "\n";
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;

}


GLuint GLutils::makeProgramFromContent(const char *  vertex_content, const char * fragment_content){
    GLuint vertex_shader = this->makeShaderFromContent(vertex_content, GL_VERTEX_SHADER);
    GLuint fragment_shader = this->makeShaderFromContent(fragment_content, GL_FRAGMENT_SHADER);
    return GLutils::attachShadersAndLinkProgram(vertex_shader, fragment_shader);
}

GLuint GLutils::makeProgram(std::string vertex_file, std::string fragment_file){
    GLuint program = glCreateProgram();
    GLuint vertex_shader = makeShader(vertex_file, GL_VERTEX_SHADER);
    GLuint fragment_shader = makeShader(fragment_file, GL_FRAGMENT_SHADER);
    return GLutils::attachShadersAndLinkProgram(vertex_shader, fragment_shader);
}

GLuint GLutils::makeShaderFromContent(const char * shader_content, GLenum shader_type){
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_content, NULL);
    glCompileShader(shader);
    int status;
    GLchar info_log[1000];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    glGetShaderInfoLog(shader, 1000, NULL, &info_log[0]);
    if(!status){
        std::cout << "failed to load this vertex shader" << std::endl;
        std::cout << info_log << '\n';
    }
    return shader;
}


GLuint GLutils::makeShader(std::string shader_file, GLenum shader_type){
    std::string content = readFile(shader_file);
    const char * shader_src = content.c_str();
    return makeShaderFromContent(shader_src, shader_type);
}


namespace Intersector{
    template <typename ShapeA, typename ShapeB>
    bool asRectIntersectsAsRect(ShapeA& a, ShapeB& b);
    bool rectIntersectsRect(AARect& rect_0, AARect& rect_1);
    bool circleIntersectsRect(Circle& circle, AARect& rect);
    bool circleIntersectsPolygon(Circle& circle, Polygon& polygon);
    bool polygonIntersectsPolygon(Polygon& polygon_0, Polygon& polygon_1);
    bool polygonIntersectsPolygonEdgeTest(Polygon& polygon_0, Polygon& polygon_1);
    bool capsuleIntersectsRect(Capsule& capsule, AARect& rect);
    bool polygonIntersectsRect(Polygon& polygon, AARect& rect);
};


bool Intersector::rectIntersectsRect(AARect& rect_0, AARect& rect_1){
    return (fmaxf(rect_0.getRight(), rect_1.getRight()) - fmin(rect_0.getLeft(), rect_1.getLeft())) <= (rect_0.getWidth() + rect_1.getWidth()) &&
        (fmaxf(rect_0.getBottom(), rect_1.getBottom()) - fmin(rect_0.getTop(), rect_1.getTop())) <= (rect_0.getHeight() + rect_1.getHeight());

}

bool Intersector::circleIntersectsRect(Circle& circle, AARect& rect){
    Polygon rect_polygon; 
    create(rect_polygon, rect);
    return Intersector::circleIntersectsPolygon(circle, rect_polygon); 
}

// This should work as long as the shappe has a toRect function
template <typename ShapeA, typename ShapeB>
bool Intersector::asRectIntersectsAsRect(ShapeA& a, ShapeB& b){
    AARect rect_a = a.toRect();
    AARect rect_b = b.toRect();
    return Intersector::rectIntersectsRect(rect_a, rect_b);
}

// This Should Work, but needs testing
bool Intersector::circleIntersectsPolygon(Circle& circle, Polygon& polygon){
    if(!Intersector::asRectIntersectsAsRect<Circle, Polygon>(circle, polygon)){
        return false;
    }

    std::vector<Edge> polygon_edges = polygon.getEdges();
    for(int i = 0; i < polygon_edges.size(); i++){
        glm::vec2 point = ExtraVectorMath::lineClamp(
            polygon_edges.at(i).p0, 
            polygon_edges.at(i).p1,
            circle.position + 
                polygon_edges.at(i).getNormal() * 
                ExtraVectorMath::projectionT(circle.position, polygon_edges.at(i).p0, polygon_edges.at(i).getNormal())
        ); 
        if(contains(circle, point)){
            return true;
        }
    }
    return false;
}



bool Intersector::polygonIntersectsPolygonEdgeTest(Polygon& polygon_0, Polygon& polygon_1){

    std::vector<Edge> polygon_0_edges = polygon_0.getEdges();
    std::vector<glm::vec2>& polygon_0_verticies= polygon_0.getVerticies();
    std::vector<glm::vec2>& polygon_1_verticies= polygon_1.getVerticies();
    bool intersecting = true;
    for(int i = 0; i < polygon_0_edges.size(); i++){
        glm::vec2 vector = polygon_0_edges.at(i).asVector();
        glm::vec2 normal = glm::normalize(polygon_0_edges.at(i).getNormal());   

        float min_polygon_0 = ExtraVectorMath::projectionT(
            ExtraVectorMath::projectionPoint(ExtraVectorMath::minPoint(polygon_0_verticies, vector), glm::vec2(0.0f), normal), 
            glm::vec2(0.0f),
            -vector
        ),
        max_polygon_0 = ExtraVectorMath::projectionT(
            ExtraVectorMath::projectionPoint(ExtraVectorMath::maxPoint(polygon_0_verticies, vector), glm::vec2(0.0f), normal),
            glm::vec2(0.0f),
            -vector
        ),
        min_polygon_1 = ExtraVectorMath::projectionT(
            ExtraVectorMath::projectionPoint(ExtraVectorMath::minPoint(polygon_1_verticies, vector), glm::vec2(0.0f), normal), 
            glm::vec2(0.0f),
            -vector
        ),
        max_polygon_1 = ExtraVectorMath::projectionT( 
            ExtraVectorMath::projectionPoint(ExtraVectorMath::maxPoint(polygon_1_verticies, vector), glm::vec2(0.0f), normal),
            glm::vec2(0.0f),
            -vector
        );
        float polygon_0_w = max_polygon_0 - min_polygon_0;
        float polygon_1_w = max_polygon_1 - min_polygon_1;
        float max_max = fmaxf(max_polygon_0, max_polygon_1);
        float min_min = fminf(min_polygon_0, min_polygon_1);
        float intersected_width = (max_max - min_min);
        float total_width = (polygon_0_w + polygon_1_w);
        intersecting = intersecting && ( intersected_width <= total_width);
    }
    return intersecting;

}

bool Intersector::polygonIntersectsPolygon(Polygon& polygon_0, Polygon& polygon_1){

    return Intersector::polygonIntersectsPolygonEdgeTest(polygon_0, polygon_1) && 
    Intersector::polygonIntersectsPolygonEdgeTest(polygon_1, polygon_0);
    
}

bool Intersector::polygonIntersectsRect(Polygon& polygon, AARect& rect){
    Polygon rect_as_polygon;
    create(rect_as_polygon, rect);
    return Intersector::polygonIntersectsPolygon(polygon, rect_as_polygon);
}

bool Intersector::capsuleIntersectsRect(Capsule& capsule, AARect& rect){
    Circle circle_1 = capsule.getStartCircle(); 
    Circle circle_2 = capsule.getEndCircle();
    Polygon polygon = capsule.getMidSection();
    
    return Intersector::circleIntersectsRect(circle_2, rect) ||
        Intersector::polygonIntersectsRect(polygon, rect) || 
        Intersector::circleIntersectsRect(circle_1, rect);
}


// This will update the time and the normal when the circle hits the rect
bool resolve(float& dt, glm::vec2& normal, Circle& circle, AARect& rect, glm::vec2 cumu_velocity);
//This will resolve a point to a bounded line on an axis
template <int axis, int other_axis>
bool resolve(float& dt, glm::vec2& normal, float start, float target, float min_bound, float max_bound, glm::vec2 start_point, glm::vec2 velocity, glm::vec2 new_normal);
// This will update the time and the normal if the circle hits the rect in less time and the circle is travelling towards the rect
// resolves based on start value of of bect to resolve in one dimension  and velocity in a single dimension.
bool resolve(float& dt, glm::vec2& normal, float start, float target, float velocity, glm::vec2 new_normal);



struct CircleLineIntersection{
    bool hit; 
    float t0, t1;
    float max(){
        return std::max(this->t0, this->t1);
    }
};


CircleLineIntersection resolve(Circle& circle, glm::vec2 line_start, glm::vec2 vector){
    CircleLineIntersection res;
    glm::vec2 circle_to_line_start = line_start - circle.position;
    float a_val = glm::dot(vector, vector);
    float b_val = 2.0f * glm::dot(vector, line_start - circle.position);
    float c_val =  glm::dot(circle.position, circle.position - 2.0f * line_start) + glm::dot(line_start, line_start) - circle.radius * circle.radius;
    float determinant = b_val * b_val - 4.0f * a_val * c_val;
    res.hit = determinant >= 0.0f;
    if (!res.hit){ 
        return res;
    }
    res.t0 = ((-b_val) - sqrtf(determinant)) / (2.0f * a_val);
    res.t1 = ((-b_val) + sqrtf(determinant)) / (2.0f * a_val);
    return res;
}







template <int axis, int other_axis>
bool resolve(float& dt, glm::vec2& normal, float start, float target, float min_bound, float max_bound, glm::vec2 start_point, glm::vec2 velocity, glm::vec2 new_normal){
    
    float t = (start - target) / velocity[axis];
    glm::vec2 pp = start_point - velocity * t;
    bool better = (t > dt) && (pp[other_axis] >= min_bound) && (pp[other_axis] <= max_bound);
    if(better){

        dt = t;
        normal = new_normal;
    }
    return better;
}

bool resolve(float& dt, glm::vec2& normal, Circle& circle, AARect& rect, glm::vec2 velocity){
    // For each box points on the circle,find how far it is away from the rectangle
    bool better = false;
    // top
    {
        float t = (circle.getBottom() - rect.getTop()) / velocity.y;
        glm::vec2 point = circle.getBottomPoint() - velocity * t;

        if ((velocity.y > 0.0f) && (t > dt) && (point.x >= rect.getLeft()) && (point.x <= rect.getRight())){
            dt =  t;
            normal = glm::vec2(0.0f, -1.0f);
            better = true;
        }
        
    }
    //bottom
    {
        float t = (circle.getTop() - rect.getBottom()) / velocity.y;
        glm::vec2 point = circle.getTopPoint() - velocity * t;
        if ((velocity.y < 0.0f) && (t > dt) && (point.x >= rect.getLeft()) && (point.x <= rect.getRight())){
            dt = t;
            normal = glm::vec2(0.0f, 1.0f);
            better = true;

        }  
    }
    //right
    {
        float t = (circle.getLeft() - rect.getRight()) / velocity.x;
        glm::vec2 point = circle.getLeftPoint() - velocity * t;
        if((velocity.x < 0.0f) && (t > dt) && (point.y >= rect.getTop()) && (point.y <= rect.getBottom())){
            dt = t;
            normal = glm::vec2(1.0f, 0.0f);
            better = true;

        }
    }
    //left
    {
        float t = (circle.getRight() - rect.getLeft()) / velocity.x;
        glm::vec2 point = circle.getRightPoint() - velocity * t;
        if((velocity.x > 0.0f) && (t > dt) && (point.y >= rect.getTop()) && (point.y <= rect.getBottom())){
            dt = t;
            normal = glm::vec2(-1.0f, 0.0f);
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
        CircleLineIntersection circle_intersection = resolve(circle, rect_verticies[i], velocity);
        if (circle_intersection.hit){
            float t = circle_intersection.hit ? circle_intersection.max() : 0.0f;
            if(t > dt){
                dt = t;
                normal = glm::normalize(circle.position - (rect_verticies[i] + t * velocity));
                better = true;

            }   
        }
    }
    return better;
}



bool resolve(float& dt, glm::vec2& normal, float start, float target, float velocity, glm::vec2 new_normal){
    bool better = false;
    if(velocity != 0){
        float t = (start - target) / velocity;
        better = t > dt;
        if(better){
            dt = t;
            normal = new_normal;
        }
    }
    return better;
}

struct TimeController
{
    float delta_time;
    Uint64 time;
    TimeController();
    TimeController(Uint64 time);
    Uint64 getTime();
    float getDeltaTime();
};

Uint64 TimeController::getTime(){
    return this->time;
}

float TimeController::getDeltaTime(){
    return this->delta_time;
}



void update(TimeController& time_controller, Uint64 new_time){

    if(new_time >= time_controller.time){ // No overflow
        time_controller.delta_time = ((float)new_time - (float)time_controller.time) * 0.001f;
    }else{
        Uint64 actualElapsed = new_time + std::numeric_limits<Uint64>::max() - time_controller.time;
        time_controller.delta_time =actualElapsed * 0.001f;
    }
    time_controller.time = new_time;

}

void create(TimeController& time_controller, Uint64 time){
    time_controller.delta_time = 1.0f / 60.0f;
    time_controller.time = time;
}

TimeController::TimeController(Uint64 time){
    ::create(*this, time);
}

template<typename ValueType>
struct TimeFilter
{
    ValueType value;
    Uint64 time, filter_duration;
    ValueType getValue();
};

template<typename ValueType>
void create(TimeFilter<ValueType>& time_filter, Uint64 filter_duration){
    time_filter.filter_duration = filter_duration;
}

template<typename ValueType>
void update(TimeFilter<ValueType>& time_filter, ValueType new_value, Uint64 new_time){
    bool pred = abs((int)(new_time - time_filter.time)) >= time_filter.filter_duration;
    time_filter.value = (pred) ? new_value : time_filter.value;
    time_filter.time = (pred) ? new_time : time_filter.time;
}

template<typename ValueType>
ValueType TimeFilter<ValueType>::getValue(){
    return value;
}

struct FrameBufferData{
    GLuint object = 0;
    GLuint color_texture = 0;
};


struct OnHit {
    virtual void update(glm::vec2 normal) = 0;
};


class IGameObject{};

struct MultiShape
{
    std::vector<AARect> aa_rects;
    std::vector<Circle> circles;
    AARect bounding_rect;
    int shape_count = 0;
    float getLeft();
    float getRight();
    float getBottom();
    float getTop();
    float getWidth();
};



void move(MultiShape& shape_group, glm::vec2 movement){
    for(AARect& rect : shape_group.aa_rects){
        ::move(rect, movement);
    }
    for(Circle& circle : shape_group.circles){
        ::move(circle, movement);
    }
    ::move(shape_group.bounding_rect, movement);
}


void addCircle(MultiShape& shape_group, Circle circle){
    AARect rect = circle.toRect();
    shape_group.circles.push_back(circle);
    if(shape_group.shape_count == 0){
        shape_group.bounding_rect = circle.toRect();
    }else{
        ::join(shape_group.bounding_rect, rect);
    }
    shape_group.shape_count++;
}

void addRect(MultiShape& shape_group, AARect rect){
    shape_group.aa_rects.push_back(rect);
    if(shape_group.shape_count == 0){
        shape_group.bounding_rect = rect;
    }else{
        ::join(shape_group.bounding_rect, rect);
    }
    shape_group.shape_count++;

}

bool contains(MultiShape& shape_group, glm::vec2 point){
    for(Circle& circle : shape_group.circles){
        if(contains(circle, point)){
            return true;
        }
    }

    for(AARect& rect : shape_group.aa_rects){
        if(contains(rect, point)){
            return true;
        }
    }
    return false;
}
    
float MultiShape::getLeft(){
    return this->bounding_rect.getLeft(); 
}

float MultiShape::getRight(){
    return this->bounding_rect.getRight();
}

float MultiShape::getBottom(){
    return this->bounding_rect.getBottom();
}

float MultiShape::getTop(){
    return this->bounding_rect.getTop();
}

float MultiShape::getWidth(){
    return this->getRight() - this->getLeft();
}

struct Entity{

public:
    Entity();
    glm::vec2 position, velocity;
    MultiShape multi_shape;
    
    glm::vec2 getPosition();
    void create(glm::vec2 position, glm::vec2 velocity);
    float getTop();
    float getBottom();
    float getLeft();
    float getRight();
    float getWidth();
};

void move(Entity& entity, glm::vec2 movement);    
void move(Entity& entity, float dt);
void moveX(Entity& entity, float x);
void moveY(Entity& entity, float y);
void moveXTo(Entity& entity, float x);
void moveYTo(Entity& entity, float y);
void moveTo(Entity& entity, glm::vec2 point);
bool contains(Entity& entity, glm::vec2 point);
void setVelocityX(Entity& entity, float x);
void setVelocity(Entity& entity, glm::vec2 velocity);


Entity::Entity(){}

glm::vec2 Entity::getPosition(){
    return this->position;
}

struct Ball : public Entity, public IGameObject{
    Ball();
    void create(glm::vec2 position, float radius, glm::vec2 velocity);
    Circle& refCircle();
};

struct Paddle : public Entity, public IGameObject{
    Paddle();
    void create(glm::vec2 position);
    AARect& refRect();
    glm::vec2 bounceOffTop(glm::vec2 velocity, float x);
};

void move(Entity& entity, glm::vec2 movement){
    entity.position += movement; 
    move(entity.multi_shape, movement);
}   
void move(Entity& entity, float dt){
    glm::vec2 movement = entity.velocity * dt;
    move(entity, movement);
}
void moveX(Entity& entity, float x){move(entity, glm::vec2(x, 0));}
void moveY(Entity& entity, float y){move(entity, glm::vec2(0, y));}
void moveXTo(Entity& entity, float x){moveTo(entity, glm::vec2(x, entity.position.y));}
void moveYTo(Entity& entity, float y){moveTo(entity, glm::vec2(entity.position.x, y));}
void moveTo(Entity& entity, glm::vec2 point){move(entity, point - entity.position);}
bool contains(Entity& entity, glm::vec2 point){contains(entity.multi_shape, point);}
void setVelocityX(Entity& entity, float x){entity.velocity.x = x;}
void setVelocity(Entity& entity, glm::vec2 velocity){entity.velocity = velocity;}

void Entity::create(glm::vec2 position, glm::vec2 velocity){
    this->position = position;
    this->velocity = velocity;
}

float Entity::getTop(){
    return this->multi_shape.getTop();
}

float Entity::getBottom(){
    return this->multi_shape.getBottom();
}

float Entity::getLeft(){
    return this->multi_shape.getLeft();
}

float Entity::getRight(){
    return this->multi_shape.getRight();
}

float Entity::getWidth(){
    return this->multi_shape.getWidth();
}


Ball::Ball(){}

void Ball::create(glm::vec2 position, float radius, glm::vec2 velocity){
    Entity::create(position, velocity);
    Circle circle;
    circle.create(position, radius);
    addCircle(multi_shape, circle);
}


Circle& Ball::refCircle(){
    return this->multi_shape.circles.at(0);
}

Paddle::Paddle(){}

AARect& Paddle::refRect(){
    return this->multi_shape.aa_rects.at(0);
}

void Paddle::create(glm::vec2 position){
    Entity::create(position, glm::vec2(0, 0));
    AARect rect;
    rect.create(position, glm::vec2(80, 8));
    addRect(this->multi_shape, rect);
}

glm::vec2 Paddle::bounceOffTop(glm::vec2 velocity, float x){
    float perc = (x - this->multi_shape.aa_rects.at(0).getCentre().x) / this->multi_shape.aa_rects.at(0).getWidth() * 2.0f;
    std::cout << perc << std::endl;
    return glm::normalize(glm::vec2(perc * 10.0f, -1.0f)) * glm::length(velocity);
}


struct BallBounceOfPaddle : OnHit{
    Ball * ball;
    Paddle * paddle;
    void set(Ball * ball, Paddle * paddle);
    void update(glm::vec2 normal);
};

void BallBounceOfPaddle::set(Ball * ball, Paddle * paddle){
    this->ball = ball;
    this->paddle = paddle;
}

void BallBounceOfPaddle::update(glm::vec2 normal){
    if(normal.y == 1.0f){
        this->ball->velocity = paddle->bounceOffTop(ball->velocity, ball->position.x);
    }else{
        this->ball->velocity = glm::reflect(ball->velocity, normal);
    }
}

struct BallBounceOfWall : OnHit{
    Ball * ball;
    void set(Ball * ball);
    void update(glm::vec2 normal);
};

void BallBounceOfWall::set(Ball * ball){
    this->ball = ball;
}
void BallBounceOfWall::update(glm::vec2 normal){
    ball->velocity = glm::reflect(ball->velocity, normal);
}

struct PaddleHitsWall : OnHit{
    Paddle * paddle;
    void set(Paddle * paddle);
    void update(glm::vec2 normal);
};

void PaddleHitsWall::set(Paddle * paddle){
    this->paddle = paddle;
}
void PaddleHitsWall::update(glm::vec2 normal){
    paddle->velocity.x = 0.0f;
}



struct PolygonRenderer{
    GLuint program = 0, uniform_matrix = 0, vertex_buffer = 0, index_buffer = 0;
    std::vector<float> vertex_batch;
    std::vector<unsigned int> index_batch;
    unsigned int index_offset = 0;
    PolygonRenderer();
    void begin();
};


PolygonRenderer::PolygonRenderer(){
    this->program = GLutils().makeProgram("./data/shaders/polygon_position_color.vert", "./data/shaders/polygon_position_color.frag");
    this->uniform_matrix = glGetUniformLocation(this->program, "u_view_mat");
    glGenBuffers(1, &this->vertex_buffer);
    glGenBuffers(1, &this->index_buffer);
    this->vertex_batch.clear();
    this->index_batch.clear();
    this->index_offset = 0;

}

void PolygonRenderer::begin(){
    this->index_offset = 0;
    this->vertex_batch.clear();
    this->index_batch.clear();
}

struct CircleRenderer{
    GLuint program = 0, vertex_buffer, index_buffer = 0;
    GLint uniform_matrix = 0;
    std::vector<float> vertex_batch = std::vector<float>();
    std::vector<unsigned int> index_batch = std::vector<unsigned int>();
    unsigned int index_offset = 0;
    CircleRenderer();
    void begin();
};

CircleRenderer::CircleRenderer(){
    program = GLutils().makeProgram("./data/shaders/circle_position_color_texcoord.vert", "./data/shaders/circle_position_color_texcoord.frag");
    uniform_matrix = glGetUniformLocation(program, "u_view_mat");
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    vertex_batch.clear();
    index_batch.clear();
    index_offset = 0;
}

void CircleRenderer::begin(){
    this->index_offset = 0;
    this->vertex_batch.clear();
    this->index_batch.clear();
}

struct TextureRenderer{
    GLuint program = 0, vertex_buffer = 0, index_buffer = 0;
    GLint uniform_matrix = 0;
    std::vector<float> vertex_batch = std::vector<float>();
    std::vector<unsigned int> index_batch = std::vector<unsigned int>();
    unsigned int index_offset = 0;
    GLint u_texture;
    TextureRenderer();
    void begin();
};


TextureRenderer::TextureRenderer(){
    program =  GLutils().makeProgram("data\\shaders\\texture_color.vert", "data\\shaders\\texture_color.frag");
    u_texture = glGetUniformLocation(program, "uTexture");
    uniform_matrix = glGetUniformLocation(program, "uViewmat");
}

void TextureRenderer::begin(){
    this->index_offset = 0;
    this->vertex_batch.clear();
    this->index_batch.clear(); 
}


struct RadialBrickEditor{
    bool active = false, central_circle = true;
    glm::vec3 central_circle_color;
    int origin_x = 0, origin_y = 0, radius = 10;
    std::vector<int> brick_thickness = {10, 5, 8, 4};
    std::vector<int> segment_offsets = {10, 20, 30};
    std::vector<int> segment_horizontal_gap = {4, 8, 5};
    // radial_gap = 1;
    int min_layer = 0, max_layer = 4;

    std::vector<int> segments = {4, 5, 6};
    std::vector<int> radial_gap = {4, 8};
    std::vector<float> layer_angular_ranges = {
        {0.0f, 360.0f}
    };
    std::vector<glm::vec3> color_pattern = {
        glm::vec3(1.0f, 0.0f, 1.0f)
    };
};

struct CircleBrick{
    int x, y, radius;
};

struct ArcBrick{
    int x, y, radius, sub_radius,
    start_angle, end_angle;
    float r, g, b;
};

struct RadialBrickGroup{
    CircleBrick centre_brick;
    std::vector<ArcBrick> arc_bricks;
    AARect bounding_rect;
};

struct Game{
    std::vector<RadialBrickGroup> radial_brick_groups;
};

// Adds arc with the vertex format of "xyz rgb"
void addArc(PolygonRenderer& polygon_renderer, float min_degrees, float max_degrees, float steps, float origin_x, float origin_y, float circle_radius, float mask_radius,
float r = 1.0f, float g = 1.0f, float b = 1.0f){
    std::vector<float>& vertex_batch = polygon_renderer.vertex_batch;
    std::vector<unsigned int>& index_batch  = polygon_renderer.index_batch;
    unsigned int& index_offset = polygon_renderer.index_offset;
    for(float theta = min_degrees; theta <= max_degrees; theta += steps){
        theta = fminf(theta, max_degrees);
        float as_rad = (float)theta / 180.0f * M_PI;
        float cosine = cos(as_rad);
        float sine = sin(as_rad);
        vertex_batch.insert(vertex_batch.end(),{
            origin_x - cosine * mask_radius, origin_y + sine * mask_radius, 0.0f, r, g, b,
            origin_x - cosine * circle_radius, origin_y + sine * circle_radius, 0.0f, r, g, b,
        });
    }
    int quads = ((max_degrees - min_degrees) / steps);
    for(int i = 0; i < quads; i++){
        index_batch.insert(index_batch.end(), 
            {
                index_offset, index_offset + 2, index_offset + 1,   
                index_offset + 2, index_offset + 3, index_offset + 1
            }
        );
        index_offset += 2;
    }
    index_offset += 2;
}

// Adds slice with the vertex format of "xyz rgb"
void addSlice(PolygonRenderer& polygon_renderer, float min_degrees, float max_degrees, float steps, float origin_x, float origin_y, float circle_radius){
    std::vector<float>& vertex_batch = polygon_renderer.vertex_batch;
    std::vector<unsigned int>& index_batch  = polygon_renderer.index_batch;
    unsigned int& index_offset = polygon_renderer.index_offset;
    vertex_batch.insert(vertex_batch.end(),{
        origin_x, origin_y, 0.0f, 1.0f, 1.0f, 1.0f,
    });
    
    for(float theta = min_degrees; theta <= max_degrees; theta += steps){
        theta = fminf(theta, max_degrees);
        float as_rad = (float)theta / 180.0f * M_PI;
        float cosine = cos(as_rad);
        float sine = sin(as_rad);
        vertex_batch.insert(vertex_batch.end(),{
            origin_x - cosine * circle_radius, origin_y + sine * circle_radius, 0.0f, 1.0f, 1.0f, 1.0f,
        });
    }
    int tri = (max_degrees - min_degrees) / steps;
    unsigned int start = index_offset;
    for(int i = 0; i < tri; i++){
        index_batch.insert(index_batch.end(), 
            {
                start, index_offset + 2, index_offset + 1,   
            }
        );
        polygon_renderer.index_offset += 1;
    }
    polygon_renderer.index_offset += 2;
}

struct BrickArrayEditor{
    bool active = true;
    int origin_x = 0, origin_y = 0;
    int brick_width = 8, brick_height = 8;
    int vertical_spacing = 1, horizontal_spacing = 1;
    int row_count = 20, column_count = 20; 
};


struct KeyboardButton
{
    ButtonState state = ButtonState_Released;
    SDL_Keycode keycode;
    KeyboardButton(SDL_Keycode keycode);
};

KeyboardButton::KeyboardButton(SDL_Keycode keycode){
    this->keycode = keycode;
}

struct MouseButton{
    int state = ButtonState_Up;
};

struct Editor{
    bool pause = false; 
    std::vector<RadialBrickEditor> radial_brick_group_editor;
};



void addRectangle(std::vector<float>& vertex_batch, std::vector<unsigned int>& index_batch, AARect& rect, glm::vec3& color, unsigned int& index_offset){
    vertex_batch.insert(vertex_batch.end(), {
        rect.getLeft(), rect.getBottom(), 0.0f, color.r, color.g, color.b,
        rect.getRight(), rect.getBottom(), 0.0f, color.r, color.g, color.b,
        rect.getRight(), rect.getTop(), 0.0f, color.r, color.g, color.b,
        rect.getLeft(), rect.getTop(), 0.0f, color.r, color.g, color.b
    });

    index_batch.insert(index_batch.end(), {
        index_offset, index_offset + 1, index_offset + 2,
        index_offset, index_offset + 2, index_offset + 3
    });

    index_offset += 4;
}


void addCircle(std::vector<float>& vertex_batch, std::vector<unsigned int>& index_batch,
float x, float y, float w, float h, float r, float g, float b, unsigned int& index_offset){
    
    vertex_batch.insert(vertex_batch.end(),{
        x, y + h, 0.0f, r, g, b, -1.0f, 1.0f,
        x + w, y + h, 0.0f, r, g, b, 1.0f, 1.0f,
        x + w, y, 0.0f, r, g, b, 1.0f, -1.0f,
        x, y, 0.0f, r, g, b, -1.0f, -1.0f
    });

    index_batch.insert(index_batch.end(),{                       
        index_offset, index_offset + 1, index_offset + 2,
        index_offset, index_offset + 2, index_offset + 3
    });
    index_offset += 4;
}


void renderRadialBrickGroup(PolygonRenderer& polygon_renderer, RadialBrickGroup& brick_group){
    CircleBrick& cb = brick_group.centre_brick;
    std::vector<ArcBrick>& arc_bricks = brick_group.arc_bricks;
    addSlice(polygon_renderer, 0, 360, 5, cb.x, cb.y, cb.radius);      
    // render all arc bricks

    for(ArcBrick& arc : arc_bricks){
        addArc(
            polygon_renderer,
            arc.start_angle,
            arc.end_angle,
            5.0f,
            arc.x,
            arc.y,
            arc.radius,
            arc.sub_radius,
            arc.r,
            arc.g,
            arc.b
        );
    }
}


void renderLines(PolygonRenderer& polygon_renderer, AARect& rect, float thickness){
    // for(AARect selection_rect : selection_rects){
        float ht = thickness * 0.5f;
        polygon_renderer.vertex_batch.insert(polygon_renderer.vertex_batch.end(), {
            // Outer verticies
            rect.getLeft() - ht, rect.getBottom() + ht, 0.0f, 0.0f, 1.0f, 0.0f,
            rect.getRight() + ht, rect.getBottom() + ht, 0.0f, 0.0f, 1.0f, 0.0f,
            rect.getRight() + ht, rect.getTop() - ht, 0.0f, 0.0f, 1.0f, 0.0f,
            rect.getLeft() - ht, rect.getTop() - ht, 0.0f, 0.0f, 1.0f, 0.0f,
            // Inner verticies
            rect.getLeft() + ht, rect.getBottom() - ht, 0.0f, 0.0f, 1.0f, 0.0f,
            rect.getRight() - ht, rect.getBottom() - ht, 0.0f, 0.0f, 1.0f, 0.0f,
            rect.getRight() - ht, rect.getTop() + ht, 0.0f, 0.0f, 1.0f, 0.0f,
            rect.getLeft() + ht, rect.getTop() + ht, 0.0f, 0.0f, 1.0f, 0.0f, 
        });

        std::vector<unsigned int> new_indicies = {
            0, 1, 4,    1, 5, 4,
            1, 2, 5,    2, 6, 5,
            2, 3, 6,    3, 7, 6,
            3, 0, 7,    0, 4, 7,
        };

        for(unsigned int& ind : new_indicies ){
            ind += polygon_renderer.index_offset;
        }

        polygon_renderer.index_batch.insert(polygon_renderer.index_batch.end(), new_indicies.begin(), new_indicies.end());
        polygon_renderer.index_offset += 8;   
    
}



void renderPolygonBatch(PolygonRenderer& polygon_renderer, glm::mat4 matrix){
    if(polygon_renderer.index_batch.size() > 0){
        glBindBuffer(GL_ARRAY_BUFFER, polygon_renderer.vertex_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, polygon_renderer.index_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * polygon_renderer.vertex_batch.size(), &polygon_renderer.vertex_batch.at(0), GL_DYNAMIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * polygon_renderer.index_batch.size(), &polygon_renderer.index_batch.at(0), GL_DYNAMIC_DRAW);

        glUseProgram(polygon_renderer.program);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(0 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glUniformMatrix4fv(polygon_renderer.uniform_matrix, 1, GL_FALSE, &matrix[0][0]);
        // draw the polygon   
        glDrawElements(GL_TRIANGLES, polygon_renderer.index_batch.size(), GL_UNSIGNED_INT, 0);
    }
}

void renderCircleBatch(CircleRenderer& circle_renderer, glm::mat4 matrix){
    if(circle_renderer.index_batch.size() > 0){
        glBindBuffer(GL_ARRAY_BUFFER, circle_renderer.vertex_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, circle_renderer.index_buffer);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * circle_renderer.vertex_batch.size(), &circle_renderer.vertex_batch.at(0), GL_DYNAMIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * circle_renderer.index_batch.size(), &circle_renderer.index_batch.at(0), GL_DYNAMIC_DRAW);
        glUseProgram(circle_renderer.program);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(0 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);  
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);     
                
        glUniformMatrix4fv(circle_renderer.uniform_matrix, 1, GL_FALSE, &matrix[0][0]);
        // draw the circle   
        glDrawElements(GL_TRIANGLES, circle_renderer.index_batch.size(), GL_UNSIGNED_INT, 0);
    }
             
}

template <typename TButton>
void updateButton(TButton& button, bool down){
    button.state = down ?
        button.state == ButtonState_Pressed || button.state == ButtonState_Down ?
                ButtonState_Down :
                ButtonState_Pressed
            : button.state == ButtonState_Pressed || button.state == ButtonState_Down ? 
                ButtonState_Released : 
                ButtonState_Up;

}

template <typename TButton>
bool pressedOrDown(TButton& button){
    return (button.state == ButtonState_Pressed || button.state == ButtonState_Down); 
}

template <typename TButton>
bool pressed(TButton& button){
    return button.state == ButtonState_Pressed;
}


void radialBrickEditor(std::vector<RadialBrickGroup>& radial_brick_groups, RadialBrickGroup& editor_radial_bricks, RadialBrickEditor& radial_brick_editor){
    bool& active = radial_brick_editor.active;
    bool& has_circle = radial_brick_editor.central_circle;
    int& x = radial_brick_editor.origin_x;
    int& y = radial_brick_editor.origin_y;
    int& r = radial_brick_editor.radius;
    std::vector<int>& brick_thickness_array = radial_brick_editor.brick_thickness;
    std::vector<int>& segment_offset_array = radial_brick_editor.segment_offsets;
    std::vector<int>& radial_gap_array = radial_brick_editor.radial_gap;
    std::vector<int>& segment_horizontal_gap_array = radial_brick_editor.segment_horizontal_gap;
    ImGui::Checkbox("Active", &active);
    ImGui::Checkbox("central_circle", &has_circle);
    ImGui::InputInt("origin x", &x);
    ImGui::InputInt("origin y", &y);
    ImGui::InputInt("radius", &r);
    ImGui::InputInt("min layer", &radial_brick_editor.min_layer);
    ImGui::InputInt("max layer", &radial_brick_editor.max_layer);
    for(int i = 0; i < segment_horizontal_gap_array.size(); i++){
        int& h_gap = segment_horizontal_gap_array.at(i);
        std::string gap_label =  "h gap #" + std::to_string(i);
        ImGui::PushID(&h_gap);
        if(ImGui::CollapsingHeader(gap_label.c_str(), 0)){
            ImGui::InputInt("gap", &h_gap);
        }
        ImGui::PopID();
    }
    for(int i = 0; i < radial_gap_array.size(); i++){
        int& radial_gap = radial_gap_array.at(i);
        std::string gap_label =  "radial gap #" + std::to_string(i);
        ImGui::PushID(&radial_gap);
        if(ImGui::CollapsingHeader(gap_label.c_str(), 0)){
            ImGui::InputInt("gap", &radial_gap);
        }
        ImGui::PopID();
    }

    for(int i = 0; i < brick_thickness_array.size(); i++){
        int& thickness = brick_thickness_array.at(i);
        std::string thickness_label =  "brick thickness #" + std::to_string(i);
        ImGui::PushID(&thickness);
        if(ImGui::CollapsingHeader(thickness_label.c_str(), 0)){
            ImGui::InputInt("Thickness", &thickness);
        }
        ImGui::PopID();
    }

    for(int i = 0; i < segment_offset_array.size(); i++){
        int& segment_offset = segment_offset_array.at(i);
        std::string segment_offset_label = "segment offset #" + std::to_string(i);
        ImGui::PushID(&segment_offset_array.at(i));
        if(ImGui::CollapsingHeader(segment_offset_label.c_str(), 0)){
            ImGui::InputInt("offset", &segment_offset);
        }
        ImGui::PopID();
    }

}

void radialBrickGroupUpdate(RadialBrickGroup& editor_radial_bricks, RadialBrickEditor& radial_brick_editor){
    // Update the radial_bricks being edited
    
    if(radial_brick_editor.active){
        CircleBrick& cir = editor_radial_bricks.centre_brick; 
        cir.x = radial_brick_editor.origin_x;
        cir.y = radial_brick_editor.origin_y;
        cir.radius = radial_brick_editor.radius;  
        editor_radial_bricks.centre_brick = cir;

        editor_radial_bricks.arc_bricks.clear();
        // regenerate the arc bricks
        bool& central_circle = radial_brick_editor.central_circle;
        int& x = radial_brick_editor.origin_x;
        int& y = radial_brick_editor.origin_y;
        int& r = radial_brick_editor.radius;
        int& min_layer = radial_brick_editor.min_layer;
        int& max_layer = radial_brick_editor.max_layer;
        std::vector<int>& radial_gap = radial_brick_editor.radial_gap;
        std::vector<int>& brick_thickness_array = radial_brick_editor.brick_thickness;
        std::vector<int>& segments = radial_brick_editor.segments;
        std::vector<int>& segment_offset_array = radial_brick_editor.segment_offsets;
        std::vector<int>& h_gap_array = radial_brick_editor.segment_horizontal_gap;
        // generate bounding_ radius
        {
            float bounding_radius = r;
            for(int l = 0; l < max_layer - 1; l++){
                bounding_radius = bounding_radius + radial_gap.at(l % radial_gap.size());
                bounding_radius += brick_thickness_array.at(l % brick_thickness_array.size());
            } 
            AARect rect;
            rect.position.x = x - bounding_radius;
            rect.position.y = y - bounding_radius;
            rect.size.x = 2 * bounding_radius;
            rect.size.y = 2 * bounding_radius;
            editor_radial_bricks.bounding_rect = rect;

        }
        for(int layer = min_layer; layer < max_layer; layer++){
            std::vector<int> segment_layers = radial_brick_editor.segments;
            int psuedo_slice_radius = r;
            int mask_radius = r;
            int arc_count = segment_layers.at(layer % segments.size());
            int segment_offset_layer = segment_offset_array.at(layer % segment_offset_array.size());
            float half_gap = h_gap_array.at(layer % h_gap_array.size()) * 0.5f;

            for(int l = 0; l < layer ; l++){
                mask_radius = psuedo_slice_radius + radial_gap.at(l % radial_gap.size());
                psuedo_slice_radius = mask_radius + brick_thickness_array.at(l % brick_thickness_array.size());
            }
        
            for(int arc = 0; arc < arc_count; arc++){
                int segments_in_layer = radial_brick_editor.segments.size();
                float start = arc * 360.0f /segments.at(layer % segments_in_layer) + (float)half_gap + segment_offset_layer;
                float end = (arc + 1) * 360.0f / segments.at(layer % segments_in_layer) - (float)half_gap + segment_offset_layer;
                float red = (float)(arc % 2);
                float green =  (float)(arc % 3);
                float blue = 1.0f;
                ArcBrick arc_brick;
                arc_brick.x = x;
                arc_brick.y = y;
                arc_brick.radius = psuedo_slice_radius;
                arc_brick.sub_radius = mask_radius;
                arc_brick.start_angle = start;
                arc_brick.end_angle = end;
                arc_brick.r = red;
                arc_brick.g = green;
                arc_brick.b = blue;
                editor_radial_bricks.arc_bricks.push_back(arc_brick);
            }
        }
    }
}


int main(int argc, char const *argv[])
{

    SDL_Window * window; // An **allocated reference** to the SDLWindow object that created, **on creation**
    bool active = true; // To store whether the window is **currently** active
    int width = 640, // To store the **current** width of the window 
    height = 480; //  To store the **current**  height of the Window  
    SDL_GLContext gl_context;
    int gl_major_version = 3;
    int gl_minor_version = 3;

    if(SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }

    window = SDL_CreateWindow(
        "Breakout Game", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        width, 
        height, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );
    SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_SetWindowMinimumSize(window, 640, 480);
    if(window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }    

    if (gl_major_version > 3 || (gl_major_version == 3 && gl_minor_version >= 3))
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_major_version); // GL version is a property
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_minor_version); // GL minor version us a property
    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(1);
    }
    SDL_GL_MakeCurrent(window, gl_context);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext(NULL);
    ImGuiIO * io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->IniFilename = NULL;
    io->ConfigWindowsMoveFromTitleBarOnly = true;
    ImGui::StyleColorsDark(NULL);
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 150");

    glm::mat4 matrix = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
    FrameBufferData frame_buffer;
    PolygonRenderer polygon_renderer = PolygonRenderer();
    CircleRenderer circle_renderer = CircleRenderer();
    TextureRenderer texture_renderer = TextureRenderer();
    
    glm::vec4 game_bg_color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

    struct {int x, y, w, h;} game_viewport;
    struct {float position_x = 0.0f, position_y = 0.0f; float delta_x = 0.0f, delta_y = 0.0f; }game_mouse;
    
    glGenBuffers(1, &texture_renderer.vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, texture_renderer.vertex_buffer);
    
    struct {
        float vertex_data[8 * 4] = {
            0.0f, 480.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            640.0f, 480.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            640.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
        }; 
        unsigned int index_data[6] {
            0, 1, 2,
            0, 2, 3
        };
    } frame_quad;

    glBufferData(GL_ARRAY_BUFFER, 8 * 4 * sizeof(float), frame_quad.vertex_data,  GL_DYNAMIC_DRAW);
    glGenBuffers(1, &texture_renderer.index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, texture_renderer.index_buffer);    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), frame_quad.index_data,  GL_DYNAMIC_DRAW);
  
    glGenTextures(1, &frame_buffer.color_texture);
    glBindTexture(GL_TEXTURE_2D, frame_buffer.color_texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glGenFramebuffers(1, &frame_buffer.object);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer.object);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frame_buffer.color_texture, 0);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout << "Framw buffer failed to generate" << std::endl;
    }

    // Initialise the texture renderer
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer.object);

    // Set the Viewport defaults 
    glViewport(0, 0, width, height);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
    int window_x, window_y;
    SDL_GetWindowSize(window, &window_x, &window_y);
    Editor editor;

    const Uint8 * keyboard_state = SDL_GetKeyboardState(NULL);

    std::vector<KeyboardButton> keyboard_buttons = {
        KeyboardButton(SDL_SCANCODE_ESCAPE),
        KeyboardButton(SDL_SCANCODE_W),
        KeyboardButton(SDL_SCANCODE_S),
        KeyboardButton(SDL_SCANCODE_A),
        KeyboardButton(SDL_SCANCODE_D),
        KeyboardButton(SDL_SCANCODE_I)
    };


    KeyboardButton& start_button = keyboard_buttons.at(0);
    KeyboardButton& up_button = keyboard_buttons.at(1);
    KeyboardButton& down_button = keyboard_buttons.at(2);
    KeyboardButton& left_button = keyboard_buttons.at(3);
    KeyboardButton& right_button = keyboard_buttons.at(4);
    KeyboardButton& activate_editor_button = keyboard_buttons.at(5);
    KeyboardButton& pause_button = keyboard_buttons.at(0);
    MouseButton left_mouse_button;
    MouseButton right_mouse_button;    
    TimeController time_controller = TimeController(SDL_GetTicks64());
    
    std::vector<Paddle> paddles;
    std::vector<Ball> balls;
    float left_wall = 40.0f;
    float right_wall = 640.0f - 40.0f;
    float top_wall = 0.0f;
    float bottom_wall = 480.0f;

    Game game;
    int score = 0;
    
    

    {
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
            setVelocityX(paddle, 300.0f);
            paddles.push_back(paddle);
        
        }
        {
            Ball ball = Ball();
            ball.create(glm::vec2(200.0f, 200.0f), 8.0f, glm::vec2(-300.0f, 300.0f));
            balls.push_back(ball);
        }

        {
            Ball ball = Ball();
            ball.create(glm::vec2(200.0f, 200.0f), 8.0f, glm::vec2(300.0f, 300.0f));
            balls.push_back(ball);
        }

    }

    Paddle& player_paddle = paddles.at(0);

    // Selected Objects
    std::vector<Ball*> balls_selected;
    std::vector<Paddle*> paddles_selected;
    std::vector<RadialBrickGroup*> radial_group_selected;

    // Moving Objects
    std::vector<Ball*> balls_moving;
    std::vector<Paddle*> paddles_moving;
    std::vector<RadialBrickGroup*> radial_group_moving;

    int window_mouse_x, window_mouse_y;
    
    BallBounceOfPaddle ball_bounce_paddle;
    BallBounceOfWall ball_bounce_wall;
    PaddleHitsWall paddle_hits_wall;

    struct {
        bool paused = false;
    }scene;

    // this is modified with ImGui in order to create Brick grids hat vcan be added to this game
    BrickArrayEditor brick_array_editor;
    RadialBrickEditor radial_brick_editor;
    RadialBrickGroup editor_radial_bricks;


    while (active)
    {
        SDL_Event event;
        Base_Events_ID base_event;
        while (SDL_PollEvent(&event))
        {   
            ImGui_ImplSDL2_ProcessEvent(&event);
            
            switch (mapToBaseEvent(event))
            {
            case Quit_Event:
                active = false;
                break;
            case Resize_Window_Event:
                break;
            }
        }

        Uint32 mouse_button_down_states = SDL_GetMouseState(&window_mouse_x, &window_mouse_y);
    
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Create the Editor Window and it's layout
        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->WorkPos);
        ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize);
        ImGui::Begin("Editor", (bool *)__null, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking);
        if(ImGui::ArrowButton("play", ImGuiDir_Right)){
            editor.pause = false;
        }
        ImGui::SameLine();
        if(ImGui::Button("pause")){
            editor.pause = true;
        }

        ImGui::SameLine();
        ImGui::Button("stop");

        if(ImGui::DockBuilderGetNode(ImGui::GetID("editor_dockspace")) == NULL){
            ImGui::DockBuilderAddNode(ImGui::GetID("editor_dockspace"), ImGuiDockNodeFlags_DockSpace | ImGuiDockNodeFlags_NoResizeY);
            ImGui::DockBuilderSetNodeSize(ImGui::GetID("editor_dockspace"), ImGui::GetMainViewport()->WorkSize);
            ImGuiID left_dock_1;
            ImGuiID right_dock_1;
            ImGui::DockBuilderSplitNode(ImGui::GetID("editor_dockspace"), ImGuiDir_Left, 0.25f, &left_dock_1, &right_dock_1);
            ImGuiID top_dock_2;
            ImGuiID bottom_dock_2;
            ImGui::DockBuilderSplitNode(right_dock_1, ImGuiDir_Up, 0.75f, &top_dock_2, &bottom_dock_2);
            ImGuiID left_dock_3;
            ImGuiID right_dock_3;
            ImGui::DockBuilderSplitNode(top_dock_2, ImGuiDir_Left, 0.75f, &left_dock_3, &right_dock_3);
            ImGuiID top_dock_4;
            ImGuiID bottom_dock_4;
            ImGui::DockBuilderSplitNode(right_dock_3, ImGuiDir_Up, 0.5f, &top_dock_4, &bottom_dock_4);

            ImGui::DockBuilderDockWindow("EditorLeft", left_dock_1);
            ImGui::DockBuilderDockWindow("Viewport", left_dock_3);
            ImGui::DockBuilderDockWindow("Inspector", bottom_dock_2);
            ImGui::DockBuilderDockWindow("Slot1", top_dock_4);
            ImGui::DockBuilderDockWindow("Slot2", bottom_dock_4);
            ImGui::DockBuilderFinish(ImGui::GetID("editor_dockspace"));
        }
        ImGui::DockSpace(ImGui::GetID("editor_dockspace"), ImVec2(0,0), ImGuiDockNodeFlags_NoDockingSplitMe | ImGuiDockNodeFlags_NoTabBar);
        ImGui::End();

        ImGui::Begin("EditorLeft", (bool*)__null, ImGuiWindowFlags_NoMove );
        if(ImGui::DockBuilderGetNode(ImGui::GetID("editor_left_dockspace")) == NULL){
            ImGui::DockBuilderAddNode(ImGui::GetID("editor_left_dockspace"), 0);
            ImGui::DockBuilderDockWindow("Assets", ImGui::GetID("editor_left_dockspace"));

            ImGui::DockBuilderFinish(ImGui::GetID("editor_left_dockspace"));
        
        }
        
        ImGui::DockSpace(ImGui::GetID("editor_left_dockspace"));
        ImGui::End();

   

        ImGui::Begin("Slot1", (bool*)__null, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
        if(ImGui::DockBuilderGetNode(ImGui::GetID("slot_1_dockspace")) == NULL){
            ImGui::DockBuilderAddNode(ImGui::GetID("slot_1_dockspace"), 0);
            ImGui::DockBuilderDockWindow("Scene", ImGui::GetID("slot_1_dockspace"));

            ImGui::DockBuilderFinish(ImGui::GetID("slot_1_dockspace"));
        }
        ImGui::DockSpace(ImGui::GetID("slot_1_dockspace"));
        ImGui::End();

        ImGui::Begin("Slot2", (bool*)__null, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
        if(ImGui::DockBuilderGetNode(ImGui::GetID("slot_2_dockspace")) == NULL){
            ImGui::DockBuilderAddNode(ImGui::GetID("slot_2_dockspace"), 0);
            ImGui::DockBuilderDockWindow("Brick Array", ImGui::GetID("slot_2_dockspace"));
            ImGui::DockBuilderDockWindow("Radial Brick Rule", ImGui::GetID("slot_2_dockspace"));

            ImGui::DockBuilderFinish(ImGui::GetID("slot_2_dockspace"));
        }
        
        ImGui::DockSpace(ImGui::GetID("slot_2_dockspace"));
        ImGui::End();

        ImGui::Begin("Assets");
        if(ImGui::Button("Brick Array Editor")){
            brick_array_editor.active = true;
        };
        if(ImGui::Button("Brick Radial Editor")){
            radial_brick_editor.active = true;

        };
        ImGui::End();

        ImGui::Begin("Inspector", (bool*)__null, ImGuiWindowFlags_NoMove);
        ImGui::Text("window mouse position x: %f y: %f", (float)window_mouse_x, (float)window_mouse_y);
        ImGui::Text("game mouse position x: %f y: %f", game_mouse.position_x, game_mouse.position_y);
        ImGui::End();


        // The Scene Editor Menu
        ImGui::Begin("Scene");
        {
            glm::vec2 position = player_paddle.position;
            if(ImGui::CollapsingHeader("Player")){
                if(ImGui::DragFloat2("Position", &position.x)){
                    moveTo(player_paddle, position);
                }
            }
        }
        {
            std::string ball_string = "Ball #";
            for (int i = 0; i < balls.size(); i++){
                Ball& ball = balls.at(i);
                ImGui::CollapsingHeader((ball_string + std::to_string(i)).c_str());
            }
        }

        {
            std::string radial_brick_group_string = "Radial Brick Group #";
            for(int i = 0; i < game.radial_brick_groups.size(); i++){
                RadialBrickGroup& radial_brick_group = game.radial_brick_groups.at(i);
                ImGui::CollapsingHeader((radial_brick_group_string + std::to_string(i)).c_str(),
                ImGuiTreeNodeFlags_Selected);
            }
        }
        ImGui::End();
      
        ImGui::Begin("Viewport", (bool *)__null, ImGuiWindowFlags_NoMove);
        ImVec2 size = ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowWidth() / 4 * 3);
   
        ImGui::Image((ImTextureID)frame_buffer.color_texture, size, ImVec2(0, 1), ImVec2(1, 0));
        
        // Update the Game Viewport to match what is in the window
        {
            ImVec2 window_position = ImGui::GetWindowPos();
            ImVec2 region_min =  ImGui::GetWindowContentRegionMin();
            ImVec2 region_max = ImGui::GetWindowContentRegionMax();

            game_viewport.x = window_position.x + region_min.x;
            game_viewport.y = window_position.y + region_min.y;
            game_viewport.w = (window_position.x + region_max.x) - game_viewport.x;
            game_viewport.h = (window_position.y + region_max.y) - game_viewport.y;

            //update the game mouse position as something that is scaled to a 640, 480 screen
            
            float old_position_x = game_mouse.position_x;
            float old_posiition_y = game_mouse.position_y;
            game_mouse.position_x = ((float)window_mouse_x - game_viewport.x) / game_viewport.w * width;
            game_mouse.position_y = ((float)window_mouse_y - game_viewport.y) / game_viewport.h * height;
            game_mouse.delta_x = game_mouse.position_x - old_position_x ;
            game_mouse.delta_y = game_mouse.position_y - old_posiition_y;

        }
        ImGui::End();

        // Eddit the Brick Array creator
        {
            int origin[2] = {
                brick_array_editor.origin_x,
                brick_array_editor.origin_y
            };
            ImGui::Begin("Brick Array");

            ImGui::Checkbox("Active", &brick_array_editor.active);
            if(ImGui::InputInt2("Origin", &origin[0], 0)){
                brick_array_editor.origin_x = origin[0];
                brick_array_editor.origin_y = origin[1];
            }
            ImGui::End();

        }
    
        updateButton(left_mouse_button, (mouse_button_down_states & SDL_BUTTON_LMASK) != 0);
        updateButton(right_mouse_button, (mouse_button_down_states & SDL_BUTTON_RMASK) != 0);

        for (KeyboardButton& button : keyboard_buttons){
            updateButton(button, keyboard_state[button.keycode]);
        }

        // consider the various game objects for selection
        

        // clear existing selection 
        if(pressed(left_mouse_button)){
            balls_selected.clear();
            paddles_selected.clear();
            radial_group_selected.clear();
        }

        // add balls to selection, 
        for(Ball& ball : balls){
            AARect rect = ball.refCircle().toRect();
            if(contains(rect, glm::vec2(game_mouse.position_x, game_mouse.position_y))){
                if(left_mouse_button.state == ButtonState_Pressed){
                    balls_selected.push_back(&ball);
                }
            }
        }

        // add paddles to selection, clear existing selection
        for (Paddle& paddle: paddles){
            if(contains(paddle.refRect(), glm::vec2(game_mouse.position_x, game_mouse.position_y))){
                paddles_selected.push_back(&paddle);
            }
        }
        // add radial group to selection, clear existing selection
        for(RadialBrickGroup& radial_brick: game.radial_brick_groups){
            if(contains(radial_brick.bounding_rect, glm::vec2(game_mouse.position_x, game_mouse.position_y))){
                radial_group_selected.push_back(&radial_brick);
            }    
        }

        // move the movable balls
        for(Ball * ball : balls_moving){
            if(left_mouse_button.state == ButtonState_Pressed || left_mouse_button.state == ButtonState_Down){
                move(*ball, glm::vec2(game_mouse.delta_x, game_mouse.delta_y));
            }
        }

        // move the movable paddles
        for(Paddle * paddle : paddles_moving) {
            if(left_mouse_button.state == ButtonState_Pressed || left_mouse_button.state == ButtonState_Down){
                move(*paddle, glm::vec2(game_mouse.delta_x, game_mouse.delta_y));
            }
        }

        // move the radial bricks paddles
        for(RadialBrickGroup * group : radial_group_moving) {
            if(left_mouse_button.state == ButtonState_Pressed || left_mouse_button.state == ButtonState_Down){
                move(group->bounding_rect, glm::vec2((int)game_mouse.delta_x, (int)game_mouse.delta_y));
                group->centre_brick.x += (int)game_mouse.delta_x;
                group->centre_brick.y += (int)game_mouse.delta_y;
                for(ArcBrick& arcs : group->arc_bricks){
                    arcs.x += (int)game_mouse.delta_x;
                    arcs.y += (int)game_mouse.delta_y;
                }   
            }
        }


        // clear moving  if the mouse is up or released
        if(left_mouse_button.state == ButtonState_Released || left_mouse_button.state == ButtonState_Up){
            balls_moving.clear();
            paddles_moving.clear();
            radial_group_selected.clear();
        }

        // add selected balls to moving balls is met
        for(Ball * ball : balls_selected){
            if(left_mouse_button.state == ButtonState_Pressed && 
                contains(ball->refCircle(), glm::vec2(game_mouse.position_x, game_mouse.position_y))){
                balls_moving.push_back(ball);
            }
        // Move move the selected balls if the mouse is down      
        }

        // add selected paddles to moving paddles
        for(Paddle * paddle : paddles_selected){
            if(left_mouse_button.state == ButtonState_Pressed &&
                contains(paddle->refRect(), glm::vec2(game_mouse.position_x, game_mouse.position_y))){
                paddles_moving.push_back(paddle);
            }
        }

        // add selected radial to moving radial group
        for(RadialBrickGroup * radial_group : radial_group_selected){
            if(left_mouse_button.state == ButtonState_Pressed &&
                contains(radial_group->bounding_rect, glm::vec2(game_mouse.position_x, game_mouse.position_y))){
                radial_group_moving.push_back(radial_group);
            }
        }

        player_paddle.velocity.x = pressedOrDown(left_button) ?
            -400.0f :
            pressedOrDown(right_button) ?
                400.0f :
                0.0f;
  
        {
            // Radial Brick rule
            
            ImGui::Begin("Radial Brick Rule", (bool *)__null, 0);
            radialBrickEditor(game.radial_brick_groups, editor_radial_bricks, radial_brick_editor);
            if(ImGui::Button("Paste")){
                // insert the circle as a circle brick into the game
                editor.radial_brick_group_editor.push_back(radial_brick_editor);
                game.radial_brick_groups.push_back(editor_radial_bricks);
            }
            ImGui::End(); 
            radialBrickGroupUpdate(editor_radial_bricks, radial_brick_editor);
            // Update the Game Itself
            bool update_physics = (!editor.pause) && (!scene.paused); 
            if(update_physics){
                int limit = 0;
                float dt = time_controller.getDeltaTime();
                while (dt > 0.0f) {
                    OnHit * on_hit = NULL;
                    for (Ball& ball : balls){
                        move(ball, dt);
                    }
                    for(Paddle& paddle : paddles){
                        move(paddle, dt);                           
                    }    

                    dt = 0.0f;
                    glm::vec2 normal = glm::vec2(0.0f, 0.0f);

                    for (Ball& ball : balls){
                       
                        for(Paddle& paddle : paddles){
                            if(Intersector::circleIntersectsRect(ball.refCircle(), paddle.refRect())){
                                if(resolve(dt, normal, ball.refCircle(), paddle.refRect(), ball.velocity - paddle.velocity)){
                                    ball_bounce_paddle.set(&ball, &paddle);
                                    on_hit = &ball_bounce_paddle;
                                }
                            }
                        }

                        if((ball.getTop() < top_wall) && (ball.velocity.y < 0.0f)){
                            if(resolve(dt, normal, ball.getTop(), top_wall, ball.velocity.y, glm::vec2(0.0f, 1.0f))){
                                ball_bounce_wall.set(&ball);
                                on_hit = &ball_bounce_wall;

                            }
                        }
                        
                        if((ball.getBottom() > bottom_wall) && (ball.velocity.y > 0.0f)){
                            if(resolve(dt, normal, ball.getBottom(), bottom_wall, ball.velocity.y, glm::vec2(0.0f, -1.0f))){
                                ball_bounce_wall.set(&ball);
                                on_hit = &ball_bounce_wall;

                            }
                        }

                        if((ball.getLeft() < left_wall) && (ball.velocity.x < 0.0f)){
                            if(resolve(dt, normal, ball.getLeft(), left_wall, ball.velocity.x, glm::vec2(1.0f, 0.0f))){
                                ball_bounce_wall.set(&ball);
                                on_hit = &ball_bounce_wall;

                            }
                        }

                        if((ball.getRight() > right_wall) && (ball.velocity.x > 0.0f)){
                            if(resolve(dt, normal, ball.getRight(), right_wall, ball.velocity.x, glm::vec2(-1.0f, 0.0f))){
                                ball_bounce_wall.set(&ball);
                                on_hit = &ball_bounce_wall; 
                            }
                        }
                    }     

                    for(Paddle& paddle : paddles){
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

                    for (Ball& ball : balls){
                        move(ball, -dt);
                    }
                    for (Paddle& paddle : paddles){
                        move(paddle, -dt);
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
        }


        /// [ Rendering ]
        glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer.object);
        glViewport(0, 0, width, height);
        glClearColor(game_bg_color.r, game_bg_color.g, game_bg_color.b, game_bg_color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        circle_renderer.begin();
        for(Ball& ball : balls){
            glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
            AARect rct = ball.refCircle().toRect();
            addCircle(circle_renderer.vertex_batch, circle_renderer.index_batch, rct.getLeft(), rct.getRight(), rct.getWidth(), rct.getHeight(), color.r, color.g, color.b, circle_renderer.index_offset);            
        }
        // render with the polygon renderer
        polygon_renderer.begin();
        {
            AARect rect = player_paddle.refRect();
            glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
            addRectangle(polygon_renderer.vertex_batch, polygon_renderer.index_batch, rect, color, polygon_renderer.index_offset);                
        }
        // left wall render
        {
            AARect rect = AARect(glm::vec2(left_wall - 4, 0), glm::vec2(4, 480));
            glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
            addRectangle(polygon_renderer.vertex_batch, polygon_renderer.index_batch, rect, color, polygon_renderer.index_offset);                
        }
        // right wall render
        {            
            AARect rect = AARect(glm::vec2(right_wall, 0),glm::vec2(4, 480));
            glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
            addRectangle(polygon_renderer.vertex_batch, polygon_renderer.index_batch, rect, color, polygon_renderer.index_offset);                
        }
        //get rects that can be selected
        std::vector<AARect> selection_rects;
        // add selection box for selected balls render
        for(Ball * ball : balls_selected){
           selection_rects.push_back(ball->refCircle().toRect()); 
        }

        // add selection box for paddles
        for (Paddle * paddle : paddles_selected){
            selection_rects.push_back(paddle->refRect()); 
        }

        // add selection box for radial group
        for (RadialBrickGroup * radial_group : radial_group_selected){
            selection_rects.push_back(radial_group->bounding_rect); 
        }
        
        // render for rectangles to represent the outline of the selection box of the ball
        for(AARect selection_rect : selection_rects){
            renderLines(polygon_renderer, selection_rect, 2.0f);
        }

        // Render brick_array if it is active
        if(brick_array_editor.active){

            AARect rect = AARect(
                glm::vec2(brick_array_editor.origin_x, brick_array_editor.origin_y),
                glm::vec2(brick_array_editor.brick_width, brick_array_editor.brick_height)
            );
            glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
            for (int x = 0; x < brick_array_editor.column_count; x++){
                for (int y = 0; y < brick_array_editor.row_count; y++){
                    rect.position.x = brick_array_editor.origin_x + (brick_array_editor.brick_width + brick_array_editor.horizontal_spacing) * x;
                    rect.position.y = brick_array_editor.origin_y + (brick_array_editor.brick_height + brick_array_editor.vertical_spacing) * y;
                    addRectangle(polygon_renderer.vertex_batch, polygon_renderer.index_batch, rect, color, polygon_renderer.index_offset);
                }
            }
        }       

        //render all radial bricks
        
        for(RadialBrickGroup& bricks : game.radial_brick_groups){
            renderRadialBrickGroup(polygon_renderer, bricks);
        }

        // render editor radial bricks
    
        if(radial_brick_editor.active){
            renderRadialBrickGroup(polygon_renderer, editor_radial_bricks);
            // render it's bounding box
            renderLines(polygon_renderer, editor_radial_bricks.bounding_rect, 2.0f );
        }

        if(!scene.paused){
            // Brick grid render
        }

        // Get ready to draw polygon
        renderPolygonBatch(polygon_renderer, matrix);
        renderCircleBatch(circle_renderer, matrix);

        
        // Default Render off screen frame as a texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, 640, 480);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glBindBuffer(GL_ARRAY_BUFFER, texture_renderer.vertex_buffer);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, texture_renderer.index_buffer);    
        // glUseProgram(texture_program);
        // glm::mat4 m = glm::ortho(0.0f, (float)640.0f, (float)480.0f, 0.0f);
        // glUniformMatrix4fv(texture_renderer.u_matrix, 1, GL_FALSE, &m[0][0]);
        // glUniform1i(texture_renderer.u_texture, 0);
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, frame_buffer.color_texture);
        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(0 * sizeof(float)));
        // glEnableVertexAttribArray(0);
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        // glEnableVertexAttribArray(1);
        // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        // glEnableVertexAttribArray(2);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
        update(time_controller, SDL_GetTicks64());       
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
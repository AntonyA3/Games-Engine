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

// Each function has a low level functional requirement all or nothing

/// [Section] Enums
enum Base_Events_ID {
    No_Event = 0,
    Quit_Event,
    Resize_Window_Event
}; // migrated

enum ButtonState{
    ButtonState_Pressed,
    ButtonState_Down,
    ButtonState_Up,
    ButtonState_Released
}; // migrated

//==========================================
//    BEGIN [SECTION] File Input Output Declerations
//==========================================
std::string readFile(std::string filename); // migrated
//==========================================
//    END [SECTION] File Input Output Declerations
//==========================================

//==========================================
//    BEGIN [SECTION] File Input Output Implementation
//==========================================
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
//==========================================
//    END [SECTION] File Input Output Implementation
//==========================================


//==========================================
//    BEGIN [SECTION] Boxed Object Template Functions
//==========================================
template <typename TBoxedObject>
void create(TBoxedObject& obj, glm::vec2 position, glm::vec2 size) {
    obj.position = position;
    obj.size = size;
}

template <typename TBoxedObject>
float getTopBoxed(const TBoxedObject& obj) {
    return obj.position.y;
}

template <typename TBoxedObject>
float getBottomBoxed(const TBoxedObject& obj){
    return obj.position.y + obj.size.y;
}

template <typename TBoxedObject>
float getLeftBoxed(const TBoxedObject& obj){
    return obj.position.x;
}

template <typename TBoxedObject>
float getRightBoxed(const TBoxedObject& obj){
    return obj.position.x + obj.size.x;
}

template <typename TBoxedObject>
glm::vec2 getTopLeftBoxed(const TBoxedObject& obj){
    return obj.position;
}

template <typename TBoxedObject>
glm::vec2 getBottomLeftBoxed(const TBoxedObject& obj){
    glm::vec2 out = obj.position;
    out.y += obj.size.y;
    return out;
}

template <typename TBoxedObject>
glm::vec2 getTopRightBoxed(const TBoxedObject& obj){
    glm::vec2 out = obj.position;
    out.x += obj.size.x;
    return out;
}

template <typename TBoxedObject>
glm::vec2 getBottomRightBoxed(const TBoxedObject& obj){
    return obj.position + obj.size;
}

template <typename TBoxedObject>
glm::vec2 getCentreBoxed(const TBoxedObject& obj){
    return obj.position + obj.size * 0.5f;
}
//==========================================
//    END [SECTION] Boxed Object Template Functions
//==========================================

//==========================================
//    BEGIN [SECTION] Sized Object Template Functions
//==========================================
template <typename TSizedObject>
float getWidth(const TSizedObject& obj) {
    return obj.size.x;
}

template <typename TSizedObject>
float getHeight(const TSizedObject& obj) {
    return obj.size.y;
}
//==========================================
//    END [SECTION] Sized Object Template Functions
//==========================================


//==========================================
//    BEGIN [SECTION] Boxed Circle Object Template Functions
//==========================================
template <typename TBoxCircleObject>
float getTopCircular(const TBoxCircleObject& obj) {
    return obj.position.y - obj.radius;
}

template <typename TBoxCircleObject>
float getBottomCircular(const TBoxCircleObject& obj) {
    return obj.position.y + obj.radius;
}

template <typename TBoxCircleObject>
float getLeftCircular(const TBoxCircleObject& obj) {
    return obj.position.x - obj.radius;
}

template <typename TBoxCircleObject>
float getRightCircular(const TBoxCircleObject& obj) {
    return obj.position.x + obj.radius;
}

template <typename TBoxCircleObject>
glm::vec2 getTopPointCircular(const TBoxCircleObject& obj) {
    glm::vec2 p = obj.position;
    p.y -= obj.radius;
    return p;
}

template <typename TBoxCircleObject>
glm::vec2 getBottomPointCircular(const TBoxCircleObject& obj) {
    glm::vec2 p = obj.position;
    p.y += obj.radius;
    return p;
}

template <typename TBoxCircleObject>
glm::vec2 getLeftPointCircular(const TBoxCircleObject& obj) {
    glm::vec2 p = obj.position;
    p.x -= obj.radius;
    return p;
}

template <typename TBoxCircleObject>
glm::vec2 getRightPointCircular(const TBoxCircleObject& obj) {
    glm::vec2 p = obj.position;
    p.x += obj.radius;
    return p;
}
//==========================================
//    END [SECTION] Boxed Circle Object Template Functions
//==========================================


//==========================================
//    BEGIN [SECTION] 2D Geometric Structs
//==========================================

/*
A Linear Res is an object that is used to return
the results of a linear based operation.
*/
struct LinearRes{
    bool solution; // This object has a boolean to determine whether it has 0 solutions: false or 1 solution: true
    float value; // This object has a float that represents the value, this should onlybe retrieved if and only if there is a solution
    float getValue(); // This object has the ability to get the value as long as there is a solution
};

/*
A Quadratic is an object that is used to 
return the results of a quadratic based operation
*/
struct QuadraticRes{
    int solution; // This boolean is true if there are either 1 or 2 solutions, it is false otherwise 
    float t0, t1; // These are the two solutions, that would returned when the quadratic formula is applied
    float max(); // This will return the maximum out of the 2 solutions or only one solution 
    float min(); // This will return the minimum of the two solutions or only one solution
};

/*
 A Rect is an object that represents a rectangle
*/
struct Rect
{
    glm::vec2 position; // The position of the rectangle is the top left corner
    glm::vec2 size; // the size is the diffrence between the bottom right corner and the top left corner
    Rect(); // Default
    Rect(glm::vec2 position, glm::vec2 size); // Maintain
};


struct Circle
{
    glm::vec2 position;
    float radius;

    Circle();
    Circle(glm::vec2 position, float radius);
    void create(glm::vec2 position, float radius);
};

struct Capsule
{
    glm::vec2 position;
    float radius;
    glm::vec2 direction;
    Capsule();
    Capsule(glm::vec2 position, float radius, glm::vec2 direction);
    void create(glm::vec2 position, float radius, glm::vec2 direction);
};

struct Polygon
{
    std::vector<glm::vec2> verticies;
    public:
    Polygon(){}
};

struct Ellipse
{
    glm::vec2 position;
    glm::vec2 size;
    Ellipse();
    Ellipse(glm::vec2 position, glm::vec2 size);
};

struct Edge
{
    glm::vec2 p0, p1;
    Edge& create(glm::vec2 p0, glm::vec2 p1);
    glm::vec2 asVector();
    glm::vec2 getNormal();
};

struct Slice
{
    glm::vec2 position;
    float radius, start_angle, end_angle;
};

struct Arc{
    glm::vec2 position;
    float start_radius, end_radius, start_angle, end_angle;
};

struct SweepedRect
{
    glm::vec2 start;
    float hh;
    glm::vec2 direction;
    void create(glm::vec2 start, float half_height, glm::vec2 direction);
};

struct ShapeGroup
{    
    glm::vec2 position;
    std::vector<Rect> rects;
    std::vector<Circle> circles;
    void addCircle(Circle circle);
    void addRect(Rect rect);
};
//==========================================
//    END [SECTION] 2D Geometric Structs
//==========================================

//==========================================
//    BEGIN [SECTION] Member Functions of Geometric Structs
//==========================================
float QuadraticRes::max(){ return std::max(this->t0, this->t1);}
float QuadraticRes::min(){ return std::min(this->t0, this->t1);}

Circle::Circle(){
    this->position = glm::vec2(0,0);
    this->radius = 1;
}

Circle::Circle(glm::vec2 position, float radius){
    this->position = position;
    this->radius = radius;
    assert(this->radius >= 0);
}

void Circle::create(glm::vec2 position, float radius){
    this->position = position;
    this->radius = radius;
}

Capsule::Capsule(){
    this->position = glm::vec2(0, 0);
    this->radius = 1;
    this->direction = glm::vec2(1, 1);
}

Capsule::Capsule(glm::vec2 position, float radius, glm::vec2 direction){
    this->position = position;
    assert(radius >= 0.0f);
    this->radius = radius;
    this->direction = direction;
}

void Capsule::create(glm::vec2 position, float radius, glm::vec2 direction){
    this->position = position;
    this->radius = radius;
    this->direction = direction;
}

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

void SweepedRect::create(glm::vec2 start, float half_height, glm::vec2 direction){
    this->start = start;
    this->hh = half_height;
    this->direction = direction;
}

void ShapeGroup::addCircle(Circle circle){
    this->circles.push_back(circle);
}

void ShapeGroup::addRect(Rect rect){
    this->rects.push_back(rect);
}
//==========================================
//    END [SECTION] Member Functions of Geometric Structs
//==========================================

//==========================================
//    BEGIN [SECTION] Extra Math Deceleration
//==========================================
namespace ExtraVectorMath{
    LinearRes pointintersectLineT(glm::vec2 r_line_start, glm::vec2 r_line_velocity, glm::vec2 target_line_point, glm::vec2 target_line_normal);
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
//==========================================
//    END [SECTION] Extra Math Decelration
//=========================================

//==========================================
//    BEGIN [SECTION] Extra Math Implementation
//==========================================
LinearRes ExtraVectorMath::pointintersectLineT(glm::vec2 r_line_start, glm::vec2 r_line_velocity, glm::vec2 target_line_point, glm::vec2 target_line_normal){
    LinearRes vector_math_result;
    
    float determinant = glm::dot(target_line_normal, r_line_velocity);
    if(determinant == 0.0f) {
        vector_math_result.solution = false;
        return vector_math_result;
    };
    vector_math_result.solution = true;
    vector_math_result.value = glm::dot(target_line_point - r_line_start, target_line_normal) / determinant;

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
//==========================================
//    END [SECTION] Extra Math Implementation
//==========================================

//==========================================
//    BEGIN [SECTION] Geometric Free Functions Decleration
//==========================================
bool containsPoint(Rect& rect, glm::vec2 point);
bool containsPoint(Circle circle, glm::vec2 point);
// bool containsPoint(Polygon& polygon, glm::vec2 point);
// bool containsPoint(Capsule& slice, glm::vec2 point);
bool containsPoint(Slice& slice, glm::vec2 point);
bool containsPoint(Arc& arc, glm::vec2 point);
// bool containsPoint(ShapeGroup& shape_group, glm::vec2 point);
Rect& getBoundingRect(Rect& rect, const Circle& circle);
// Rect& getBoundingRect(Rect& rect, const Polygon& circle);
// Rect& getBoundingRect(Rect& rect, const Capsule& capsule);
// Rect& getBoundingRect(Rect& rect, const Slice& polygon);
// Rect& getBoundingRect(Rect& rect, const Arc& polygon);
// Rect& getBoundingRect(Rect& rect, const ShapeGroup& polygon);
Rect& geomUnion(Rect& out_rect, const Rect& rect, const Rect& other_rect);
// void getStartCircle(Circle& circle, Capsule& capsule);
// void getEndCircle(Circle& circle, Capsule& capsule);
// void getMidPolygon(Polygon& polygon, Capsule& capsule);
void create(Polygon& polygon, SweepedRect& rect);
float getLeft(Polygon& polygon);
float getRight(Polygon& polygon);
float getTop(Polygon& polygon);
float getBottom(Polygon& polygon);
void getEdges(std::vector<Edge>& edges, Polygon& polygon);

//==========================================
//    END [SECTION] Geometric Free Functions Decleration
//==========================================



//==========================================
//    BEGIN [SECTION] Geometric Free Functions Implementation
//==========================================


bool containsPoint(Rect& rect, glm::vec2 point){
    return point.x >= getLeftBoxed(rect) && point.x <= getRightBoxed(rect) &&
        point.y >= getTopBoxed(rect) && point.y <= getBottomBoxed(rect);
}

bool containsPoint(Circle circle, glm::vec2 point){
    return glm::length2(point - circle.position) <= circle.radius * circle.radius;
}

// bool containsPoint(Polygon& polygon, glm::vec2 point){
//     std::vector<Edge> edges;
//     getEdges(edges, polygon);
//     bool contains = true;
//     for(int i = 0; i < edges.size(); i++){
//         contains = contains && ExtraVectorMath::projectionT(point, edges.at(i).p0, edges.at(i).getNormal()) > 0.0f;
//     }
//     return contains;
// }





// bool containsPoint(Capsule& capsule, glm::vec2 point){
//     Circle start_circle;
//     getStartCircle(start_circle, capsule);
//     Circle end_circle;
//     getEndCircle(end_circle, capsule);
//     Polygon mid_polygon;
//     getMidPolygon(mid_polygon, capsule);
//     return containsPoint(start_circle, point) ||
//     containsPoint(end_circle, point) ||
//     containsPoint(mid_polygon, point);
// }

bool containsPoint(Slice& slice, glm::vec2 point){
    return false;
}

bool containsPoint(Arc& arc, glm::vec2 point){
    return false;
}

// bool containsPoint(ShapeGroup& shape_group, glm::vec2 point){
//     for(Circle& circle : shape_group.circles){
//         if(containsPoint(circle, point)){
//             return true;
//         }
//     }

//     for(Rect& rect : shape_group.rects){
//         if(containsPoint(rect, point)){
//             return true;
//         }
//     }
//     return false;
// }

Rect& getBoundingRect(Rect& out_rect, const Circle& circle){
    glm::vec2 pos = glm::vec2(circle.position.x - circle.radius, circle.position.y - circle.radius);
    float diameter = 2.0f * circle.radius;
    glm::vec2 size = glm::vec2(diameter, diameter);
    out_rect.position = pos;
    out_rect.size = size;
    return out_rect;
}

Rect& geomUnion(Rect& out_rect, const Rect& rect, const Rect& other_rect){
    getWidth(rect);
    float x = fminf(rect.position.x, other_rect.position.x);
    float y = fminf(rect.position.y, other_rect.position.y);
    float sx = fmaxf(getRightBoxed(other_rect), getRightBoxed(rect)) - x;
    float sy = fmaxf(getBottomBoxed(other_rect), getBottomBoxed(rect)) - y;
    out_rect.position.x = x;
    out_rect.position.y = y;
    out_rect.size.x = sx;
    out_rect.size.y = sy;
    return out_rect;
}

void create(Polygon& polygon, SweepedRect& rect){
    glm::vec2 normal = glm::normalize(glm::vec2(-rect.direction.y, rect.direction.x));
    polygon.verticies.clear();
    polygon.verticies.push_back(rect.start + normal * rect.hh);
    polygon.verticies.push_back(rect.start + rect.direction + normal * rect.hh);
    polygon.verticies.push_back(rect.start + rect.direction - normal * rect.hh);
    polygon.verticies.push_back(rect.start - normal * rect.hh);

    // float min_x = ExtraVectorMath::maxPoint(polygon.verticies, glm::vec2(-1.0f, 0.0f)).x;
    // float max_x = ExtraVectorMath::maxPoint(polygon.verticies, glm::vec2(1.0f, 0.0f)).x;
    // float min_y = ExtraVectorMath::maxPoint(polygon.verticies, glm::vec2(0.0f, -1.0f)).y;
    // float max_y = ExtraVectorMath::maxPoint(polygon.verticies, glm::vec2(1.0f, 1.0f)).y;

}

void create(Polygon& polygon, const Rect& rect){
    // polygon.verticies.clear();
    // RectVerticies rect_verticies;
    // create(rect_verticies, rect);
    // polygon.verticies.clear();
    // polygon.verticies.push_back(glm::vec2(rect_verticies.bottom_left.x, rect_verticies.bottom_left.y));
    // polygon.verticies.push_back(glm::vec2(rect_verticies.bottom_right.x, rect_verticies.bottom_right.y));
    // polygon.verticies.push_back(glm::vec2(rect_verticies.top_right.x, rect_verticies.top_right.y));
    // polygon.verticies.push_back(glm::vec2(rect_verticies.top_left.x, rect_verticies.top_left.y));
}

float getLeft(Polygon& polygon){
    return ExtraVectorMath::maxPoint(polygon.verticies, glm::vec2(-1.0f, 0.0f)).x;
}

float getRight(Polygon& polygon){
    return ExtraVectorMath::maxPoint(polygon.verticies, glm::vec2(1.0f, 0.0f)).x;
}

float getTop(Polygon& polygon){
    return ExtraVectorMath::maxPoint(polygon.verticies, glm::vec2(0.0f, -1.0f)).y;
}

float getBottom(Polygon& polygon){
    return ExtraVectorMath::maxPoint(polygon.verticies, glm::vec2(0.0f, 1.0f)).y;
}

// void create(RectVerticies& rect_verticies, const Rect& rect){
//     rect_verticies.top_left = glm::vec3(getTopLeft(rect), 0.0f);
//     rect_verticies.top_right = glm::vec3(getTopRight(rect), 0.0f);
//     rect_verticies.bottom_left = glm::vec3(getBottomLeft(rect), 0.0f);
//     rect_verticies.bottom_right = glm::vec3(getBottomRight(rect), 0.0f);
// }
void getEdges(std::vector<Edge>& edges, Polygon& polygon){
    for(size_t i = 0; i < polygon.verticies.size(); i++){
        Edge edge;
        edge.create(polygon.verticies.at(i), polygon.verticies.at((i + 1) % polygon.verticies.size()));
        edges.push_back(edge);
    }
}

//==========================================
//    END [SECTION] Geometric Free Functions Implementation
//==========================================

// struct RectVerticies{
//     glm::vec3 top_left;
//     glm::vec3 top_right;
//     glm::vec3 bottom_left;
//     glm::vec3 bottom_right;
// }; 

//==========================================
//    BEGIN [SECTION] Physics Related Free Function Decleration
//==========================================
bool resolve(float& dt, glm::vec2& normal, float start, float target, float min_bound, float max_bound, glm::vec2 start_point, glm::vec2 velocity, glm::vec2 new_normal);
bool resolve(float& dt, glm::vec2& normal, float start, float target, float velocity, glm::vec2 new_normal);
QuadraticRes resolve(Circle& circle, glm::vec2 line_start, glm::vec2 vector);

//==========================================
//    END [SECTION] Physics Related Free Function Decleration
//==========================================

//==========================================
//    BEGIN [SECTION] Physics Related Free Function Implementation
//==========================================
bool resolve(float& dt, glm::vec2& normal, Circle& circle, Rect& rect, glm::vec2 velocity){
    // For each box points on the circle,find how far it is away from the rectangle
    bool better = false;
    // top
    {
        float t = (getBottomCircular(circle) - getTopBoxed(rect)) / velocity.y;
        glm::vec2 point = getBottomPointCircular(circle) - velocity * t;

        if ((velocity.y > 0.0f) && (t > dt) && (point.x >= getLeftBoxed(rect)) && (point.x <= getRightBoxed(rect))){
            dt =  t;
            normal = glm::vec2(0.0f, -1.0f);
            better = true;
        }
        
    }
    //bottom
    {
        float t = (getTopCircular(circle) - getBottomBoxed(rect)) / velocity.y;
        glm::vec2 point = getTopPointCircular(circle) - velocity * t;
        if ((velocity.y < 0.0f) && (t > dt) && (point.x >= getLeftBoxed(rect)) && (point.x <= getRightBoxed(rect))){
            dt = t;
            normal = glm::vec2(0.0f, 1.0f);
            better = true;

        }  
    }
    //right
    {
        float t = (getLeftCircular(circle) - getRightBoxed(rect)) / velocity.x;
        glm::vec2 point = getLeftPointCircular(circle) - velocity * t;
        if((velocity.x < 0.0f) && (t > dt) && (point.y >= getTopBoxed(rect)) && (point.y <= getBottomBoxed(rect))){
            dt = t;
            normal = glm::vec2(1.0f, 0.0f);
            better = true;

        }
    }
    //left
    {
        float t = (getRightCircular(circle) - getLeftBoxed(rect)) / velocity.x;
        glm::vec2 point = getRightPointCircular(circle) - velocity * t;
        if((velocity.x > 0.0f) && (t > dt) && (point.y >= getTopBoxed(rect)) && (point.y <= getBottomBoxed(rect))){
            dt = t;
            normal = glm::vec2(-1.0f, 0.0f);
            better = true;

        } 
    }
    
    glm::vec2 rect_verticies[4] = {
        getTopLeftBoxed(rect),
        getTopRightBoxed(rect),
        getBottomLeftBoxed(rect),
        getBottomRightBoxed(rect)
    };

    for(int i = 0; i < 4; i++){
        QuadraticRes circle_intersection = resolve(circle, rect_verticies[i], velocity);
        if (circle_intersection.solution){
            float t = circle_intersection.solution ? circle_intersection.max() : 0.0f;
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


QuadraticRes resolve(Circle& circle, glm::vec2 line_start, glm::vec2 vector){
    QuadraticRes res;
    glm::vec2 circle_to_line_start = line_start - circle.position;
    float a_val = glm::dot(vector, vector);
    float b_val = 2.0f * glm::dot(vector, line_start - circle.position);
    float c_val =  glm::dot(circle.position, circle.position - 2.0f * line_start) + glm::dot(line_start, line_start) - circle.radius * circle.radius;
    float determinant = b_val * b_val - 4.0f * a_val * c_val;
    res.solution = determinant >= 0.0f;
    if (!res.solution){ 
        return res;
    }
    res.t0 = ((-b_val) - sqrtf(determinant)) / (2.0f * a_val);
    res.t1 = ((-b_val) + sqrtf(determinant)) / (2.0f * a_val);
    return res;
}
//==========================================
//    END [SECTION] Physics Related Free Function Implementation
//==========================================

//==========================================
//    BEGIN [SECTION] Physics Related Template Functions
//==========================================

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

//==========================================
//    END [SECTION] Physics Related Template Functions
//==========================================

//==========================================
//    BEGIN [SECTION] GL Utils Decleration
//==========================================
namespace GLutils
{
    GLuint makeProgram(std::string vertex_file, std::string fragment_file);
    GLuint makeProgram(const char *  vertex_content, const char * fragment_content);
    GLuint makeShader(std::string shader_file, GLenum shader_type);
    GLuint makeShader(const char * shader_content, GLenum shader_type);
    GLuint attachLinkProgram(GLuint& vertex_shader, GLuint& fragment_shader);
};
//==========================================
//    END [SECTION] GL Utils Decleration
//==========================================

//==========================================
//    BEGIN [SECTION] GL Utils Implementation
//==========================================
GLuint GLutils::makeProgram(std::string vertex_file, std::string fragment_file){
    GLuint program = glCreateProgram();
    GLuint vertex_shader = makeShader(vertex_file, GL_VERTEX_SHADER);
    GLuint fragment_shader = makeShader(fragment_file, GL_FRAGMENT_SHADER);
    return GLutils::attachLinkProgram(vertex_shader, fragment_shader);
}

GLuint GLutils::makeProgram(const char *  vertex_content, const char * fragment_content){
    GLuint vertex_shader = GLutils::makeShader(vertex_content, GL_VERTEX_SHADER);
    GLuint fragment_shader = GLutils::makeShader(fragment_content, GL_FRAGMENT_SHADER);
    return GLutils::attachLinkProgram(vertex_shader, fragment_shader);
}

GLuint GLutils::makeShader(std::string shader_file, GLenum shader_type){
    std::string content = readFile(shader_file);
    const char * shader_src = content.c_str();
    return makeShader(shader_src, shader_type);
}

GLuint GLutils::makeShader(const char * shader_content, GLenum shader_type){
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

GLuint GLutils::attachLinkProgram(GLuint& vertex_shader, GLuint& fragment_shader){
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
//==========================================
//    END [SECTION] GL Utils Implementation
//==========================================

//==========================================
//    BEGIN [SECTION] Intersector Decleration
//==========================================
namespace Intersector{
    bool rectIntersectsRect(Rect& rect_0, Rect& rect_1);
    bool circleIntersectsRect(Circle& circle, Rect& rect);
    bool circleIntersectsPolygon(Circle& circle, Polygon& polygon);
    bool polygonIntersectsPolygon(Polygon& polygon_0, Polygon& polygon_1);
    bool polygonIntersectsPolygonEdgeTest(Polygon& polygon_0, Polygon& polygon_1);
    // bool capsuleIntersectsRect(Capsule& capsule, Rect& rect);
    bool polygonIntersectsRect(Polygon& polygon, Rect& rect);
};
//==========================================
//    END [SECTION] Intersector Decleration
//==========================================

//==========================================
//    BEGIN [SECTION] Intersector Implementation
//==========================================
bool Intersector::rectIntersectsRect(Rect& rect_0, Rect& rect_1){
    return (fmaxf(getRightBoxed(rect_0), getRightBoxed(rect_1)) - fmin(getLeftBoxed(rect_0), getLeftBoxed(rect_1))) <= (getWidth(rect_0) + getWidth(rect_1)) &&
        (fmaxf(getBottomBoxed(rect_0), getBottomBoxed(rect_1)) - fmin(getTopBoxed(rect_0), getTopBoxed(rect_1))) <= (getHeight(rect_0) + getHeight(rect_1));
}

bool Intersector::circleIntersectsRect(Circle& circle, Rect& rect){
    Polygon rect_polygon; 
    create(rect_polygon, rect);
    return Intersector::circleIntersectsPolygon(circle, rect_polygon); 
}

bool Intersector::circleIntersectsPolygon(Circle& circle, Polygon& polygon){
    std::vector<Edge> polygon_edges;
    getEdges(polygon_edges, polygon);
    for(int i = 0; i < polygon_edges.size(); i++){
        glm::vec2 point = ExtraVectorMath::lineClamp(
            polygon_edges.at(i).p0, 
            polygon_edges.at(i).p1,
            circle.position + 
                polygon_edges.at(i).getNormal() * 
                ExtraVectorMath::projectionT(circle.position, polygon_edges.at(i).p0, polygon_edges.at(i).getNormal())
        ); 
        if(containsPoint(circle, point)){
            return true;
        }
    }
    return false;
}

bool Intersector::polygonIntersectsPolygon(Polygon& polygon_0, Polygon& polygon_1){

    return Intersector::polygonIntersectsPolygonEdgeTest(polygon_0, polygon_1) && 
    Intersector::polygonIntersectsPolygonEdgeTest(polygon_1, polygon_0);
    
}

bool Intersector::polygonIntersectsRect(Polygon& polygon, Rect& rect){
    Polygon rect_as_polygon;
    create(rect_as_polygon, rect);
    return Intersector::polygonIntersectsPolygon(polygon, rect_as_polygon);
}

bool Intersector::polygonIntersectsPolygonEdgeTest(Polygon& polygon_0, Polygon& polygon_1){

    std::vector<Edge> polygon_0_edges;
    getEdges(polygon_0_edges, polygon_0);
    std::vector<glm::vec2>& polygon_0_verticies= polygon_0.verticies;
    std::vector<glm::vec2>& polygon_1_verticies= polygon_1.verticies;
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

// bool Intersector::capsuleIntersectsRect(Capsule& capsule, Rect& rect){
//     Circle circle_1;
//     getStartCircle(circle_1, capsule); 
//     Circle circle_2;
//     getEndCircle(circle_2, capsule);
//     Polygon polygon;
//     getMidPolygon(polygon, capsule);
    
//     return Intersector::circleIntersectsRect(circle_2, rect) ||
//         Intersector::polygonIntersectsRect(polygon, rect) || 
//         Intersector::circleIntersectsRect(circle_1, rect);
// }
//==========================================
//    END [SECTION] Intersector Implementation
//==========================================


//==========================================
//    BEGIN [SECTION] Time Related Structs
//==========================================
struct TimeController
{
    float delta_time;
    Uint64 time;
    TimeController();
    TimeController(Uint64 time);
    Uint64 getTime();
    float getDeltaTime();
};

template<typename ValueType>
struct TimeFilter
{
    ValueType value;
    Uint64 time, filter_duration;
    ValueType getValue();
};
//==========================================
//    END [SECTION] Time Related Structs
//==========================================
//==========================================
//    BEGIN [SECTION] Time Related Free Function Declerations
//==========================================
void create(TimeController& time_controller, Uint64 time);
void update(TimeController& time_controller, Uint64 new_time);
//==========================================
//    END [SECTION] Time Related Free Function Declerations
//==========================================


//==========================================
//    BEGIN [SECTION] Time Related Member Functions
//==========================================
Uint64 TimeController::getTime(){
    return this->time;
}

float TimeController::getDeltaTime(){
    return this->delta_time;
}

TimeController::TimeController(Uint64 time){
    ::create(*this, time);
}
//==========================================
//    END [SECTION] Time Related Member Functions
//==========================================


//==========================================
//    BEGIN [SECTION] Time Related Free Function Implementation
//==========================================
void create(TimeController& time_controller, Uint64 time){
    time_controller.delta_time = 1.0f / 60.0f;
    time_controller.time = time;
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
//==========================================
//    END [SECTION] Time Related Free Function Implementation
//==========================================

//==========================================
//    BEGIN [SECTION] Time Related Template Function Implementations
//==========================================

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

//==========================================
//    END [SECTION] Time Related Template Function Implementations
//==========================================






//==========================================
//    BEGIN [SECTION] Move Template Functions
//==========================================
template<typename TMovable>
void move(TMovable& obj, glm::vec2 movement){
    obj.position += movement;
}

template<typename TMovable>
void move(TMovable& obj, glm::vec2 velocity, float dt){
    obj.position += velocity * dt;
}

template<typename TVelocityMovable>
void move(TVelocityMovable& obj, float dt){
    obj.position += obj.velocity * dt;
}
//==========================================
//    END [SECTION] Move Template Functions
//==========================================


//==========================================
//    BEGIN [SECTION] MeshGeneration Related Member Function Decleration
//==========================================
void addRectangle(std::vector<float>& vertex_batch, std::vector<unsigned int>& index_batch, Rect& rect, glm::vec3& color, unsigned int& index_offset);
void addCircle(std::vector<float>& vertex_batch, std::vector<unsigned int>& index_batch,
float x, float y, float w, float h, float r, float g, float b, unsigned int& index_offset);
void getXYZRGBQuad(float * vertex_data, unsigned int * index_data);
//==========================================
//    END [SECTION] MeshGeneration Related Member Function Decleration
//==========================================

//==========================================
//    BEGIN [SECTION] MeshGeneration Related Member Function Implementations
//==========================================

void addRectangle(std::vector<float>& vertex_batch, std::vector<unsigned int>& index_batch, Rect& rect, glm::vec3& color, unsigned int& index_offset){
    vertex_batch.insert(vertex_batch.end(), {
        getLeftBoxed(rect), getBottomBoxed(rect), 0.0f, color.r, color.g, color.b,
        getRightBoxed(rect), getBottomBoxed(rect), 0.0f, color.r, color.g, color.b,
        getRightBoxed(rect), getTopBoxed(rect), 0.0f, color.r, color.g, color.b,
        getLeftBoxed(rect), getTopBoxed(rect), 0.0f, color.r, color.g, color.b
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

void getXYZRGBQuad(float * vertex_data, unsigned int * index_data){
    float vd[] = {
        0.0f, 480.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        640.0f, 480.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        640.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
    }; 

    unsigned int ind[] = {
        0, 1, 2,
        0, 2, 3
    };
    memcpy(vertex_data, vd, 8 * 4 * sizeof(float));
    memcpy(vertex_data, ind, 6 * sizeof(unsigned int));

}
//==========================================
//    END [SECTION] MeshGeneration Related Member Function Implementations
//==========================================

//==========================================
//    BEGIN [SECTION] Renderer Struct Declearations
//==========================================

struct CommonRenderer{
    GLuint program = 0, uniform_matrix = 0, vertex_buffer = 0, index_buffer = 0;
    std::vector<float> vertex_batch;
    std::vector<unsigned int> index_batch;
    unsigned int index_offset = 0;    
    void begin();

};

struct PolygonRenderer : public CommonRenderer{
    PolygonRenderer();
    void init();
};

struct CircleRenderer : public CommonRenderer{
    CircleRenderer();
    void init();

};

struct TextureRenderer : public CommonRenderer{
    GLint u_texture;
    TextureRenderer();
    void init();

};

struct FrameColorTextureBuffer{
    GLuint object = 0;
    GLuint color_texture = 0;
};


//==========================================
//    END [SECTION] Renderer Struct Declearations
//==========================================

//==========================================
//    BEGIN [SECTION] Renderer Member Functions
//==========================================
void CommonRenderer::begin(){
    this->index_offset = 0;
    this->vertex_batch.clear();
    this->index_batch.clear();
}

PolygonRenderer::PolygonRenderer(){}

void PolygonRenderer::init(){
    this->program = GLutils::makeProgram("./data/shaders/polygon_position_color.vert", "./data/shaders/polygon_position_color.frag");
    this->uniform_matrix = glGetUniformLocation(this->program, "u_view_mat");
    glGenBuffers(1, &this->vertex_buffer);
    glGenBuffers(1, &this->index_buffer);
    this->vertex_batch.clear();
    this->index_batch.clear();
    this->index_offset = 0;
}


CircleRenderer::CircleRenderer(){}

void CircleRenderer::init(){
    program = GLutils::makeProgram("./data/shaders/circle_position_color_texcoord.vert", "./data/shaders/circle_position_color_texcoord.frag");
    uniform_matrix = glGetUniformLocation(program, "u_view_mat");
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    vertex_batch.clear();
    index_batch.clear();
    index_offset = 0;
}

TextureRenderer::TextureRenderer(){}

void TextureRenderer::init(){
    glGenBuffers(1, &this->vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);
    program =  GLutils::makeProgram("data\\shaders\\texture_color.vert", "data\\shaders\\texture_color.frag");
    u_texture = glGetUniformLocation(program, "uTexture");
    uniform_matrix = glGetUniformLocation(program, "uViewmat");
}
//==========================================
//    END [SECTION] Renderer Member Functions
//==========================================


//==========================================
//    BEGIN [SECTION] Renderer Free Function Decleration
//==========================================

void render(PolygonRenderer& polygon_renderer, glm::mat4 matrix);
void render(CircleRenderer& circle_renderer, glm::mat4 matrix);
void addLines(PolygonRenderer& polygon_renderer, Rect& rect, float thickness);


//==========================================
//    END [SECTION] Renderer Free Function Decleration
//==========================================

//==========================================
//    BEGIN [SECTION] Renderer Free Function Implementation
//==========================================

void render(PolygonRenderer& polygon_renderer, glm::mat4 matrix){
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

void render(CircleRenderer& circle_renderer, glm::mat4 matrix){
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


void render(TextureRenderer& texture_renderer, FrameColorTextureBuffer& frame_buffer, glm::mat4 matrix){
    glBindBuffer(GL_ARRAY_BUFFER, texture_renderer.vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, texture_renderer.index_buffer);    
    glUseProgram(texture_renderer.program);
    glm::mat4 m = glm::ortho(0.0f, (float)640.0f, (float)480.0f, 0.0f);
    glUniformMatrix4fv(texture_renderer.uniform_matrix, 1, GL_FALSE, &m[0][0]);
    glUniform1i(texture_renderer.u_texture, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, frame_buffer.color_texture);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
}

void addLines(PolygonRenderer& polygon_renderer, Rect& rect, float thickness){
    // for(Rect selection_rect : selection_rects){
        float ht = thickness * 0.5f;
        polygon_renderer.vertex_batch.insert(polygon_renderer.vertex_batch.end(), {
            // Outer verticies
            getLeftBoxed(rect) - ht, getBottomBoxed(rect) + ht, 0.0f, 0.0f, 1.0f, 0.0f,
            getRightBoxed(rect) + ht, getBottomBoxed(rect) + ht, 0.0f, 0.0f, 1.0f, 0.0f,
            getRightBoxed(rect) + ht, getTopBoxed(rect) - ht, 0.0f, 0.0f, 1.0f, 0.0f,
            getLeftBoxed(rect) - ht, getTopBoxed(rect) - ht, 0.0f, 0.0f, 1.0f, 0.0f,
            // Inner verticies
            getLeftBoxed(rect) + ht, getBottomBoxed(rect) - ht, 0.0f, 0.0f, 1.0f, 0.0f,
            getRightBoxed(rect) - ht, getBottomBoxed(rect) - ht, 0.0f, 0.0f, 1.0f, 0.0f,
            getRightBoxed(rect) - ht, getTopBoxed(rect) + ht, 0.0f, 0.0f, 1.0f, 0.0f,
            getLeftBoxed(rect) + ht, getTopBoxed(rect) + ht, 0.0f, 0.0f, 1.0f, 0.0f, 
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

//==========================================
//    END [SECTION] Renderer Free Function Implementation
//==========================================

//==========================================
//    BEGIN [SECTION] Input Related Structs
//==========================================
struct Button{
    ButtonState state = ButtonState_Released;
    bool pressedOrDown();
    bool pressed();
    bool released();
    bool releasedOrUp();
};

struct KeyboardButton : Button
{
    SDL_Scancode scancode;
    KeyboardButton(SDL_Scancode scancode);
};

struct MouseButton : Button{
    MouseButton();
};

struct Mouse {
    glm::vec2 position = glm::vec2(0, 0);
    glm::vec2 delta = glm::vec2(0, 0);
};

//==========================================
//    END [SECTION] Input Related Structs
//==========================================

//==========================================
//    BEGIN [SECTION] Input Related Member Functions
//==========================================



bool Button::pressedOrDown(){
    return (this->state == ButtonState_Pressed || this->state == ButtonState_Down); 
}

bool Button::pressed(){
    return this->state == ButtonState_Pressed;
}

bool Button::released(){
    return this->state == ButtonState_Released;
}

bool Button::releasedOrUp(){
    return (this->state == ButtonState_Released || this->state == ButtonState_Up); 
}
//==========================================
//    END [SECTION] Input Related Member Functions
//==========================================

//==========================================
//    BEGIN [SECTION] Input Related Template Functions
//==========================================

// template <typename TButton>
void updateButton(Button& button, bool down){
    button.state = down ?
        button.state == ButtonState_Pressed || button.state == ButtonState_Down ?
                ButtonState_Down :
                ButtonState_Pressed
            : button.state == ButtonState_Pressed || button.state == ButtonState_Down ? 
                ButtonState_Released : 
                ButtonState_Up;

}


//==========================================
//    END [SECTION] Input Related Template Functions
//==========================================

//==========================================
//    BEGIN [SECTION] Input Related Member Functions
//==========================================
KeyboardButton::KeyboardButton(SDL_Scancode scancode){
    this->scancode = scancode;
}

MouseButton::MouseButton(){
}

//==========================================
//    END [SECTION] Input Related Member Functions
//==========================================

//==========================================
//    BEGIN [SECTION] Game Object Related Structs
//==========================================

struct Entity{
    glm::vec2 position;
    glm::vec2 velocity;
    ShapeGroup shape_group;
    Entity();
    void create(glm::vec2 position);
    void create(glm::vec2 position, glm::vec2 velocity); 
    glm::vec2 getPosition();
};


struct Ball : Entity {
    // ShapeGroup shape_group;
    // glm::vec2 position, velocity;
    Circle circle;
    Ball();
    void create(glm::vec2 position, float radius, glm::vec2 velocity);

    // void create(glm::vec2 position, glm::vec2 velocity); 
    // glm::vec2 getPosition();
    // float getTop();
    // float getBottom();
    // float getLeft();
    // float getRight();
    // Circle& refCircle();
};

struct Paddle : Entity {
    // glm::vec2 position, velocity;
    // ShapeGroup shape_group;
    Rect rect;
    Paddle();
    // void create(glm::vec2 position);
    // Rect& refRect();
    // glm::vec2 bounceOffTop(glm::vec2 velocity, float x);
    glm::vec2 getPosition();
    float getTop();
    float getBottom();
    float getLeft();
    float getRight();
};

struct Brick{
    int x, y;
};

struct CircleBrick: Brick{
    int radius;
};

struct ArcBrick : Brick{
    int radius, sub_radius,
    start_angle, end_angle;
    float r, g, b;
};

struct RadialBrickGroup{
    glm::vec2 position;
    CircleBrick centre_brick;
    std::vector<ArcBrick> arc_bricks;
};

struct Game{
    glm::vec4 bg_color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    std::vector<RadialBrickGroup> radial_brick_groups;
};

//==========================================
//    END [SECTION] Game Object Related Structs
//==========================================

//==========================================
//    BEGIN [SECTION] Game Object Related Member Functions
//==========================================

Entity::Entity(){
    this->position = glm::vec2();
    this->velocity = glm::vec2();
}


void Entity::create(glm::vec2 position){
    this->position = position;
    this->velocity = glm::vec2(0, 0);
}

void Entity::create(glm::vec2 position, glm::vec2 velocity){
    this->position = position;
    this->velocity = velocity;
}
glm::vec2 Entity::getPosition(){
    return this->position;
}


Ball::Ball(){}


// glm::vec2 Ball::getPosition(){
//     return this->position;
// }



// void Ball::create(glm::vec2 position, glm::vec2 velocity){
//     this->position = position;
//     this->velocity = velocity;
// }
void Ball::create(glm::vec2 position, float radius, glm::vec2 velocity){
    // this->entity->create(position, velocity);
    Circle circle;
    circle.create(position, radius);
}


// Circle& Ball::refCircle(){
//     return this->shape_group.circles.at(0);
// }

Paddle::Paddle(){}


// glm::vec2 Paddle::getPosition(){
//     return this->position;
// }


// void Paddle::create(glm::vec2 position, glm::vec2 velocity){
//     this->position = position;
//     this->velocity = velocity;
// }

// Rect& Paddle::refRect(){
//     return this->shape_group.rects.at(0);
// }

// void Paddle::create(glm::vec2 position){
//     this->create(position, glm::vec2(0, 0));
//     Rect rect = Rect(position, glm::vec2(80, 8));
// }

// glm::vec2 Paddle::bounceOffTop(glm::vec2 velocity, float x){
//     float perc = (x - getCentre(this->shape_group.rects.at(0)).x) / getWidth(this->shape_group.rects.at(0)) * 2.0f;
//     std::cout << perc << std::endl;
//     return glm::normalize(glm::vec2(perc * 10.0f, -1.0f)) * glm::length(velocity);
// }

//==========================================
//    END [SECTION] Game Object Related Member Functions
//==========================================


//==========================================
//    BEGIN [SECTION] Game Object Related Free Function Decleration
//==========================================

void addArc(PolygonRenderer& polygon_renderer, float min_degrees, float max_degrees, float steps, float origin_x, float origin_y, float circle_radius, float mask_radius, float r, float g, float b );
void addSlice(PolygonRenderer& polygon_renderer, float min_degrees, float max_degrees, float steps, float origin_x, float origin_y, float circle_radius);
void addRectangle(std::vector<float>& vertex_batch, std::vector<unsigned int>& index_batch, Rect& rect, glm::vec3& color, unsigned int& index_offset);
void addCircle(std::vector<float>& vertex_batch, std::vector<unsigned int>& index_batch,
float x, float y, float w, float h, float r, float g, float b, unsigned int& index_offset);
void addRadialBrickGroup(PolygonRenderer& polygon_renderer, RadialBrickGroup& brick_group);
//==========================================
//    END [SECTION] Game Object Related Free Function Decleration
//==========================================

//==========================================
//    BEGIN [SECTION] Game Object Related Free Function Implementation
//==========================================
void addArc(PolygonRenderer& polygon_renderer, float min_degrees, float max_degrees, float steps, float origin_x, float origin_y, float circle_radius, float mask_radius,
float r = 1.0f, float g = 1.0f, float b = 1.0f
){
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

void addRadialBrickGroup(PolygonRenderer& polygon_renderer, RadialBrickGroup& brick_group){
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

//==========================================
//    END [SECTION] Game Object Related Free Function Implementation
//==========================================

//==========================================
//    BEGIN [SECTION] Editor Related Structs
//==========================================

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

struct BrickArrayEditor{
    bool active = true;
    int origin_x = 0, origin_y = 0;
    int brick_width = 8, brick_height = 8;
    int vertical_spacing = 1, horizontal_spacing = 1;
    int row_count = 20, column_count = 20; 
};

struct Editor{
    bool pause = false; 
    std::vector<RadialBrickEditor> radial_brick_group_editor;
};
//==========================================
//    END [SECTION] Editor Related Structs
//==========================================

//==========================================
//    BEGIN [SECTION] Editor Related Free Function Decleration
//==========================================
void radialBrickEditor(std::vector<RadialBrickGroup>& radial_brick_groups, RadialBrickGroup& editor_radial_bricks, RadialBrickEditor& radial_brick_editor);
void radialBrickGroupUpdate(RadialBrickGroup& editor_radial_bricks, RadialBrickEditor& radial_brick_editor);
//==========================================
//    END [SECTION] Editor Related Free Functions Decleration
//==========================================

//==========================================
//    BEGIN [SECTION] Editor Related Free Function Implementations
//==========================================
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
            Rect rect;
            rect.position.x = x - bounding_radius;
            rect.position.y = y - bounding_radius;
            rect.size.x = 2 * bounding_radius;
            rect.size.y = 2 * bounding_radius;
            // editor_radial_bricks.bounding_rect = rect;

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

//==========================================
//    END [SECTION] Editor Related Free Function Implementations
//==========================================

//==========================================
//    BEGIN [SECTION] On Hit Virtual Abstract and Concerte Structs
//==========================================


struct OnHit {
    virtual void update(glm::vec2 normal) = 0;
};

struct BallBounceOfPaddle : OnHit{
    Ball * ball;
    Paddle * paddle;
    void set(Ball * ball, Paddle * paddle);
    void update(glm::vec2 normal);
};

struct BallBounceOfWall : OnHit{
    Ball * ball;
    void set(Ball * ball);
    void update(glm::vec2 normal);
};

struct PaddleHitsWall : OnHit{
    Paddle * paddle;
    void set(Paddle * paddle);
    void update(glm::vec2 normal);
};

//==========================================
//    END [SECTION] On Hit Virtual Function Structs
//==========================================


//==========================================
//    BEGIN [SECTION] On Hit Virtual Abstract and Concerte Member Functions
//=====================================

void BallBounceOfPaddle::set(Ball * ball, Paddle * paddle){
    this->ball = ball;
    this->paddle = paddle;
}

// void BallBounceOfPaddle::update(glm::vec2 normal){
//     if(normal.y == 1.0f){
//         this->ball->velocity = paddle->bounceOffTop(ball->velocity, ball->position.x);
//     }else{
//         this->ball->velocity = glm::reflect(ball->velocity, normal);
//     }
// }

void BallBounceOfWall::set(Ball * ball){
    this->ball = ball;
}
// void BallBounceOfWall::update(glm::vec2 normal){
//     ball->velocity = glm::reflect(ball->velocity, normal);
// }

void PaddleHitsWall::set(Paddle * paddle){
    this->paddle = paddle;
}

// void PaddleHitsWall::update(glm::vec2 normal){
//     paddle->velocity.x = 0.0f;
// }

//==========================================
//    END [SECTION] On Hit Virtual Abstract and Concerte Member Functions
//=====================================

//==========================================
//    BEGIN [SECTION] SDL Related Interpretation Related Functions
//=====================================
Base_Events_ID mapToBaseEvent(SDL_Event event);
//==========================================
//    END [SECTION] SDL Related Interpretation Related Functions
//=====================================


//==========================================
//    BEGIN [SECTION] SDL Related Interpretation Related Function Implementations
//=====================================
Base_Events_ID mapToBaseEvent(SDL_Event event){
    Base_Events_ID base_event = No_Event;
    base_event = (event.type == SDL_QUIT) ? Quit_Event : base_event;
    base_event = (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) ? 
        Resize_Window_Event : 
        base_event;
    return base_event;
}

//==========================================
//    END [SECTION] SDL Related Interpretation Related Function Implementations
//=====================================


int main(int argc, char const *argv[])
{
    //==========================================
    //    BEGIN [SECTION] Allocate all the memory
    //=====================================
    bool active = true; // To store whether the appplication is active
    int width = 640, height = 480; // To store the dimensions  of the window 
    glm::mat4 matrix; // This is the matrix that will be used in all of the renderers
    SDL_Window * window; // An **allocated reference** to the SDLWindow object that created, **on creation**
    SDL_GLContext gl_context; // To Store the SDL GLContext
    FrameColorTextureBuffer frame_buffer;
    PolygonRenderer polygon_renderer;
    CircleRenderer circle_renderer;
    TextureRenderer texture_renderer;
    Mouse mouse;
    MouseButton left_mouse_button = MouseButton();
    MouseButton right_mouse_button = MouseButton();
    Editor editor;
    std::vector<Button*> buttons;
    KeyboardButton start_button = KeyboardButton(SDL_SCANCODE_ESCAPE);
    KeyboardButton forward_button = KeyboardButton(SDL_SCANCODE_W);
    KeyboardButton down_button = KeyboardButton(SDL_SCANCODE_S);
    KeyboardButton left_button = KeyboardButton(SDL_SCANCODE_A);
    KeyboardButton right_button = KeyboardButton(SDL_SCANCODE_D);
    KeyboardButton inspector_button = KeyboardButton(SDL_SCANCODE_I);
    Paddle player_paddle = Paddle();
    Ball primary_ball = Ball();
    TimeController time_controller = TimeController(SDL_GetTicks64());
    float left_wall = 40.0f;
    float right_wall = 640.0f - 40.0f;
    float top_wall = 0.0f;
    float bottom_wall = 480.0f;
    Game game;
    int score = 0;
    BallBounceOfPaddle ball_bounce_paddle;
    BallBounceOfWall ball_bounce_wall;
    PaddleHitsWall paddle_hits_wall;

    struct {
        bool paused = false;
    }scene;
    BrickArrayEditor brick_array_editor;
    RadialBrickEditor radial_brick_editor;
    RadialBrickGroup editor_radial_bricks;
    struct {int x, y, w, h;} game_viewport;
    

    //full screen texture renderer quad

    struct {
        float vertex_data[8 * 4];
        unsigned int index_data[6];
    } frame_quad;
    GLenum err = glewInit();

    //==========================================
    //    END [SECTION] Allocate all the memory
    //=====================================

    //==========================================
    //    BEGIN [SECTION] Get All the Pointers
    //=====================================
    std::vector<KeyboardButton*> keyboard_buttons = {
        &start_button,
        &forward_button,
        &down_button,
        &left_button,
        &right_button,
        &inspector_button    
    };

    std::vector<MouseButton*> mouse_buttons = {
        &left_mouse_button,
        &right_mouse_button 
    };


    std::vector<Paddle*> paddles = {
        &player_paddle
    };

    std::vector<Ball*> balls = {
        &primary_ball
    };

    
    std::vector<Ball*> balls_selected;
    std::vector<Paddle*> paddles_selected;
    
    std::vector<RadialBrickGroup*> radial_group_selected;
    std::vector<Ball*> balls_moving;
    std::vector<Paddle*> paddles_moving;
    std::vector<RadialBrickGroup*> radial_group_moving;    
    //==========================================
    //    End [SECTION] Get All the Pointers
    //=====================================


    if(SDL_Init( SDL_INIT_VIDEO ) < 0 ) {printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );}
    window = SDL_CreateWindow("Breakout Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_SetWindowMinimumSize(window, width, height); // Set the window with tho current widht and height, which should be the same as the minimum
    if(window == NULL ){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );}    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY); // This is required of the opengl versions are greater than or equal to 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // GL version is a property
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); // GL minor version us a property
    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(1);
    }
    SDL_GL_MakeCurrent(window, gl_context);
    const Uint8 * keyboard_state = SDL_GetKeyboardState(NULL);

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

    polygon_renderer.init();
    circle_renderer.init();
    texture_renderer.init(); 
    matrix = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
    getXYZRGBQuad(frame_quad.vertex_data, frame_quad.index_data);
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
        std::cout << "Frame buffer failed to generate" << std::endl;
    }

    // Initialise the texture renderer
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer.object);

    // Set the Viewport defaults 
    glViewport(0, 0, width, height);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    {
        using namespace rapidxml;
        rapidxml::file<> xmlFile("data\\scenarios\\smoke_0.xml"); // Default template is char
        rapidxml::xml_document<> doc;
        doc.parse<0>(xmlFile.data());
        {
            // Paddle paddle;
            float x = atof(doc.first_node("Paddle")->first_node("Position")->first_node("X")->value());
            float y = atof(doc.first_node("Paddle")->first_node("Position")->first_node("Y")->value());
            player_paddle.create(glm::vec2(x, y));
            player_paddle.velocity.x = 300.0f;
        
        }
        primary_ball.create(glm::vec2(200.0f, 200.0f), 8.0f, glm::vec2(-300.0f, 300.0f));

    }
    
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

        Uint32 mouse_button_down_states;
        {
            int x, y;
            mouse_button_down_states = SDL_GetMouseState(&x, &y);
            mouse.position.x = (float)x;
            mouse.position.y = (float)y;
        }
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

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
        ImGui::Text("window mouse position x: %f y: %f", (float)mouse.position.x, (float)mouse.position.y);
        ImGui::End();


        // The Scene Editor Menu
        ImGui::Begin("Scene");
        {
            glm::vec2 position = player_paddle.position;
            if(ImGui::CollapsingHeader("Player")){
                if(ImGui::DragFloat2("Position", &position.x)){
                    // player_paddle.position = position;
                }
            }
        }
        {
            std::string ball_string = "Ball #";
            for (int i = 0; i < balls.size(); i++){
                Ball& ball = *balls.at(i);
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
            
            // float old_position_x = mouse.position_x;
            // float old_posiition_y = game_mouse.position_y;
            // game_mouse.position_x = ((float)window_mouse_x - game_viewport.x) / game_viewport.w * width;
            // game_mouse.position_y = ((float)window_mouse_y - game_viewport.y) / game_viewport.h * height;
            // game_mouse.delta_x = game_mouse.position_x - old_position_x ;
            // game_mouse.delta_y = game_mouse.position_y - old_posiition_y;

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
        
        for (KeyboardButton * keyboard_button : keyboard_buttons){
            updateButton(*keyboard_button, keyboard_state[keyboard_button->scancode]);
        }

        // consider the various game objects for selection
        

        // clear existing selection 
        if(left_mouse_button.pressed()){
            balls_selected.clear();
            paddles_selected.clear();
            radial_group_selected.clear();
        }

        // add balls to selection, 
        for(Ball * ball_ptr : balls){
            Rect rect;
            Ball& ball = *ball_ptr;
            Circle ball_circle = ball.getCircle();
            getBoundingRect(rect, ball_circle);
            if(containsPoint(rect, glm::vec2(mouse.position.x, mouse.position.y))){
                if(left_button.pressed()){
                    balls_selected.push_back(&ball);
                }
            }
        }

        // add paddles to selection, clear existing selection
        for (Paddle * paddle_ptr: paddles){
            Paddle& paddle = *paddle_ptr;
            if(containsPoint(paddle.refRect(), glm::vec2(mouse.position.x, mouse.position.y))){
                paddles_selected.push_back(&paddle);
            }
        }
        // add radial group to selection, clear existing selection
        // for(RadialBrickGroup& radial_brick: game.radial_brick_groups){
        //     if(contains(radial_brick.bounding_rect, glm::vec2(game_mouse.position_x, game_mouse.position_y))){
        //         radial_group_selected.push_back(&radial_brick);
        //     }    
        // }

        // move the movable balls
        for(Ball * ball_ptr : balls_moving){
            Ball& ball = *ball_ptr;
            if(left_mouse_button.pressedOrDown()){
                move(ball, glm::vec2(mouse.delta.x, mouse.delta.y));
            }
        }

        // move the movable paddles
        for(Paddle * paddle_ptr : paddles_moving) {
            Paddle paddle = *paddle_ptr;
            if(left_mouse_button.pressedOrDown()){
                move(paddle, glm::vec2(mouse.delta.x, mouse.delta.y));
            }
        }

        // move the radial bricks paddles
        for(RadialBrickGroup * group_ptr : radial_group_moving) {
            RadialBrickGroup& group = *group_ptr;
            if(left_mouse_button.pressedOrDown()){
                move(group, glm::vec2((int)mouse.delta.x, (int)mouse.delta.y));
                // group->centre_brick.x += (int)game_mouse.delta_x;
                // group->centre_brick.y += (int)game_mouse.delta_y;
                // for(ArcBrick& arcs : group->arc_bricks){
                //     arcs.x += (int)game_mouse.delta_x;
                //     arcs.y += (int)game_mouse.delta_y;
                // }   
            }
        }


        // clear moving  if the mouse is up or released
        
        if(left_mouse_button.releasedOrUp()){
            balls_moving.clear();
            paddles_moving.clear();
            radial_group_selected.clear();
        }

        // add selected balls to moving balls is met
        for(Ball * ball : balls_selected){
            Circle ball_circle = ball.getCircle();
            if(left_mouse_button.pressed() && 
                containsPoint(ball_circle, glm::vec2(mouse.position.x, mouse.position.y))){
                balls_moving.push_back(ball);
            }
        // Move move the selected balls if the mouse is down      
        }

        // add selected paddles to moving paddles
        for(Paddle * paddle_ptr : paddles_selected){
            Paddle& paddle = *paddle_ptr;
            Rect paddle_rect = paddle.getRect();
            if(left_mouse_button.pressed() &&
                containsPoint(paddle_rect, glm::vec2(mouse.position.x, mouse.position.y))){
                paddles_moving.push_back(paddle);
            }
        }

        // add selected radial to moving radial group
        // for(RadialBrickGroup * radial_group : radial_group_selected){
        //     if(left_mouse_button.state == ButtonState_Pressed &&
        //         contains(radial_group->bounding_rect, glm::vec2(game_mouse.position_x, game_mouse.position_y))){
        //         radial_group_moving.push_back(radial_group);
        //     }
        // }

        // player_paddle.velocity.x = (left_button.releasedOrUp() && right_button.releasedOrUp()) ? 0.0f : player_paddle.velocity.x;
        // player_paddle.velocity.x = left_button.pressedOrDown() ? 400.0f : player_paddle.velocity.x;
        // player_paddle.velocity.x = right_button.pressedOrDown() ? -400.0f : player_paddle.velocity.x;
  
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
                    for (Ball * ball : balls){
                        move(*ball, dt);
                    }
                    for(Paddle * paddle : paddles){
                        move(*paddle, dt);                           
                    }    

                    dt = 0.0f;
                    glm::vec2 normal = glm::vec2(0.0f, 0.0f);

                    for (Ball * ball_ptr : balls){
                        Ball& ball = *ball_ptr;
                        for(Paddle * paddle_ptr : paddles){
                            Paddle& paddle = *paddle_ptr;
                            if(Intersector::circleIntersectsRect(ball.refCircle(), paddle.refRect())){
                                if(resolve(dt, normal, ball.refCircle(), paddle.refRect(), ball.velocity - paddle.velocity)){
                                    ball_bounce_paddle.set(&ball, &paddle);
                                    on_hit = &ball_bounce_paddle;
                                }
                            }
                        }

                        if((getTopCircular(ball) < top_wall) && (ball.velocity.y < 0.0f)){
                            if(resolve(dt, normal, ball.getTop(), top_wall, ball.velocity.y, glm::vec2(0.0f, 1.0f))){
                                ball_bounce_wall.set(&ball);
                                on_hit = &ball_bounce_wall;

                            }
                        }
                        
                        if((getBottomCircular(ball) > bottom_wall) && (ball.velocity.y > 0.0f)){
                            if(resolve(dt, normal, getBottomCircular(ball), bottom_wall, ball.velocity.y, glm::vec2(0.0f, -1.0f))){
                                ball_bounce_wall.set(&ball);
                                on_hit = &ball_bounce_wall;

                            }
                        }

                        if((getLeftCircular(ball) < left_wall) && (ball.velocity.x < 0.0f)){
                            if(resolve(dt, normal, getLeftCircular(ball), left_wall, ball.velocity.x, glm::vec2(1.0f, 0.0f))){
                                ball_bounce_wall.set(&ball);
                                on_hit = &ball_bounce_wall;

                            }
                        }

                        if((getRightCircular(ball) > right_wall) && (ball.velocity.x > 0.0f)){
                            if(resolve(dt, normal, getRightCircular(ball), right_wall, ball.velocity.x, glm::vec2(-1.0f, 0.0f))){
                                ball_bounce_wall.set(&ball);
                                on_hit = &ball_bounce_wall; 
                            }
                        }
                    }     

                    for(Paddle * paddle_ptr : paddles){
                        Paddle& paddle = *paddle_ptr;
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

                    for (Ball * ball : balls){
                        move(*ball, -dt);
                    }
                    for (Paddle * paddle : paddles){
                        move(*paddle, -dt);
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
        glClearColor(game.bg_color.r, game.bg_color.g, game.bg_color.b, game.bg_color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        circle_renderer.begin();
        for(Ball * ball : balls){
            glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
            Rect rct;
            getBoundingRect(rct, (*ball).refCircle());
            addCircle(circle_renderer.vertex_batch, circle_renderer.index_batch, getLeftBoxed(rct), getRightBoxed(rct), getWidth(rct), getHeight(rct), color.r, color.g, color.b, circle_renderer.index_offset);            
        }
        // render with the polygon renderer
        polygon_renderer.begin();
        {
            Rect rect = player_paddle.refRect();
            glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
            addRectangle(polygon_renderer.vertex_batch, polygon_renderer.index_batch, rect, color, polygon_renderer.index_offset);                
        }
        // left wall render
        {
            Rect rect = Rect(glm::vec2(left_wall - 4, 0), glm::vec2(4, 480));
            glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
            addRectangle(polygon_renderer.vertex_batch, polygon_renderer.index_batch, rect, color, polygon_renderer.index_offset);                
        }
        // right wall render
        {            
            Rect rect = Rect(glm::vec2(right_wall, 0),glm::vec2(4, 480));
            glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
            addRectangle(polygon_renderer.vertex_batch, polygon_renderer.index_batch, rect, color, polygon_renderer.index_offset);                
        }
        //get rects that can be selected
        std::vector<Rect> selection_rects;
        // add selection box for selected balls render
        for(Ball * ball : balls_selected){
           Rect rect = getBoundingRect(rect, ball->refCircle());
           selection_rects.push_back(rect); 
           
        }

        // add selection box for paddles
        for (Paddle * paddle : paddles_selected){
            selection_rects.push_back(paddle->refRect()); 
        }

        // add selection box for radial group
        // for (RadialBrickGroup * radial_group : radial_group_selected){
        //     selection_rects.push_back(radial_group->bounding_rect); 
        // }
        
        // render for rectangles to represent the outline of the selection box of the ball
        for(Rect selection_rect : selection_rects){
            addLines(polygon_renderer, selection_rect, 2.0f);
        }

        // Render brick_array if it is active
        if(brick_array_editor.active){

            Rect rect = Rect(
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
            addRadialBrickGroup(polygon_renderer, bricks);
        }

        // render editor radial bricks
    
        if(radial_brick_editor.active){
            addRadialBrickGroup(polygon_renderer, editor_radial_bricks);
            // render it's bounding box
            // renderLines(polygon_renderer, editor_radial_bricks.bounding_rect, 2.0f );
        }

        if(!scene.paused){
            // Brick grid render
        }

        // Get ready to draw polygon
        render(polygon_renderer, matrix);
        render(circle_renderer, matrix);

        
        // Default Render off screen frame as a texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, 640, 480);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
        update(time_controller, SDL_GetTicks64());    
        // Reset all buttons at the End of frame

        for(Button * button: buttons){
            button->state = (button->state == ButtonState_Pressed) ? ButtonState_Down : button->state;
            button->state = (button->state == ButtonState_Released) ? ButtonState_Up : button->state;
        }   
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
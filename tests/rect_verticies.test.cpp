#include <cstdint>
#include <string>
#include <rect_verticies.hpp>
#include <SDL2/SDL.h>

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include <catch_amalgamated.hpp>



TEST_CASE("Rect To Verticies Anticlockwise", "[Rect Verticies]"){
    RectVerticies rect_verticies;
    AARect aa_rect = AARect();
    aa_rect.create(glm::vec2(10.0f, 10.0f), glm::vec2(20.0f, 10.0f));
    rect_verticies.create(aa_rect);
    REQUIRE(rect_verticies.bottom_left == glm::vec3(10.0f, 20.0f, 0.0f));
    REQUIRE(rect_verticies.bottom_right == glm::vec3(30.0f, 20.0f, 0.0f));
    REQUIRE(rect_verticies.top_right == glm::vec3(30.0f, 10.0f, 0.0f));
    REQUIRE(rect_verticies.top_left == glm::vec3(10.0f, 10.0f, 0.0f));

};
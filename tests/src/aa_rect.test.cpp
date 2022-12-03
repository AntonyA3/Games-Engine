#include <catch_amalgamated.hpp>
#include <cstdint>
#include <string>
#include <shapes/aa_rect.hpp>
#include <glm/glm.hpp>
TEST_CASE("Combine combines rectangles as expected", "[aa_rect]" ) {
    AARect rect_0 = AARect().create(glm::vec2(10.0f, 10.0f), glm::vec2(17.0f, 17.0f));
    AARect rect_1 = AARect().create(glm::vec2(15.0f, 15.0f), glm::vec2(5.0f, 5.0f));
    rect_0.combine(rect_1);

    REQUIRE(rect_0.getTopLeft().x == glm::vec2(10.0f, 10.0f).x);
    REQUIRE(rect_0.getTopRight().x == glm::vec2(20.0f, 10.0f).x);
    REQUIRE(rect_0.getBottomLeft().x == glm::vec2(10.0f, 20.0f).x);
    REQUIRE(rect_0.getBottomRight().x == glm::vec2(20.0f, 20.0f).x);

    REQUIRE(rect_0.getTopLeft().y == glm::vec2(10.0f, 10.0f).y);
    REQUIRE(rect_0.getTopRight().y == glm::vec2(20.0f, 10.0f).y);
    REQUIRE(rect_0.getBottomLeft().y == glm::vec2(10.0f, 20.0f).y);
    REQUIRE(rect_0.getBottomRight().y == glm::vec2(20.0f, 20.0f).y);
}

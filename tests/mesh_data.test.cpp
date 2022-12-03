#define CATCH_CONFIG_MAIN
#include <catch_amalgamated.hpp>
#include <mesh_data.hpp>
#include <shapes/aa_rect.hpp>
TEST_CASE("Push 2 rects with a color", "[MeshData]"){
    MeshData mesh_data;
    AARect rect0;
    rect0.create(glm::vec2(10.0f, 10.0f), glm::vec2(10.0f, 10.0f));
    AARect rect1;
    rect1.create(glm::vec2(20.0f, 10.0f), glm::vec2(20.0f, 10.0f));
    mesh_data.pushRectOfColor(rect0, glm::vec3(1.0f, 0.0f, 0.0f));
    mesh_data.pushRectOfColor(rect1, glm::vec3(1.0f, 1.0f, 1.0f));
    // Anti clockwise starting from Bottom left of rectangle
    REQUIRE(mesh_data.getVertexData().size() == 48);
    REQUIRE(mesh_data.getIndexData().size() == 12);

    //First Rect First Position
    REQUIRE(mesh_data.getVertexData().at(0) == 10.0f);
    REQUIRE(mesh_data.getVertexData().at(1) == 20.0f);
    REQUIRE(mesh_data.getVertexData().at(2) == 0.0f);

    //First Rect First Color
    REQUIRE(mesh_data.getVertexData().at(3) == 1.0f);
    REQUIRE(mesh_data.getVertexData().at(4) == 0.0f);
    REQUIRE(mesh_data.getVertexData().at(5) == 0.0f);

    //First Rect Second Position
    REQUIRE(mesh_data.getVertexData().at(6) == 20.0f);
    REQUIRE(mesh_data.getVertexData().at(7) == 20.0f);
    REQUIRE(mesh_data.getVertexData().at(8) == 0.0f);

    //First Rect Third Position
    REQUIRE(mesh_data.getVertexData().at(12) == 20.0f);
    REQUIRE(mesh_data.getVertexData().at(13) == 10.0f);
    REQUIRE(mesh_data.getVertexData().at(14) == 0.0f);

    //First Rect Fourth Position
    REQUIRE(mesh_data.getVertexData().at(18) == 10.0f);
    REQUIRE(mesh_data.getVertexData().at(19) == 10.0f);
    REQUIRE(mesh_data.getVertexData().at(20) == 0.0f);

    //Second Rect First Position
    REQUIRE(mesh_data.getVertexData().at(24) == 20.0f);
    REQUIRE(mesh_data.getVertexData().at(25) == 20.0f);
    REQUIRE(mesh_data.getVertexData().at(26) == 0.0f);

    //Second Rect Color
    REQUIRE(mesh_data.getVertexData().at(27) == 1.0f);
    REQUIRE(mesh_data.getVertexData().at(28) == 1.0f);
    REQUIRE(mesh_data.getVertexData().at(29) == 1.0f);


}

TEST_CASE("Push 2 rects with a color and unit position", "[MeshData]"){
    MeshData mesh_data;
    AARect rect0;
    rect0.create(glm::vec2(10.0f, 10.0f), glm::vec2(10.0f, 10.0f));
    AARect rect1;
    rect1.create(glm::vec2(20.0f, 20.0f), glm::vec2(20.0f, 20.0f));
    mesh_data.pushRectOfColorAndAreaUnit(rect0, glm::vec3(1.0f, 0.0f, 0.0f));
    mesh_data.pushRectOfColorAndAreaUnit(rect1, glm::vec3(1.0f, 1.0f, 1.0f));

    REQUIRE(mesh_data.getVertexData().size() == 64);
    REQUIRE(mesh_data.getIndexData().size() == 12);

    // Rect 1 First Position
    REQUIRE(mesh_data.getVertexData().at(0) == 10.0f);
    REQUIRE(mesh_data.getVertexData().at(1) == 20.0f);
    REQUIRE(mesh_data.getVertexData().at(2) == 0.0f);

    // Rect 1 First Color
    REQUIRE(mesh_data.getVertexData().at(3) == 1.0f);
    REQUIRE(mesh_data.getVertexData().at(4) == 0.0f);
    REQUIRE(mesh_data.getVertexData().at(5) == 0.0f);

    // Rect 1 First Unit
    REQUIRE(mesh_data.getVertexData().at(6) == -1.0f);
    REQUIRE(mesh_data.getVertexData().at(7) == 1.0f);

    // Rect 1 Second Position
    REQUIRE(mesh_data.getVertexData().at(8) == 20.0f);
    REQUIRE(mesh_data.getVertexData().at(9) == 20.0f);
    REQUIRE(mesh_data.getVertexData().at(10) == 0.0f);

    // Second Unit
    REQUIRE(mesh_data.getVertexData().at(14) == 1.0f);
    REQUIRE(mesh_data.getVertexData().at(15) == 1.0f);

    //Third Position
    REQUIRE(mesh_data.getVertexData().at(16) == 20.0f);
    REQUIRE(mesh_data.getVertexData().at(17) == 10.0f);
    REQUIRE(mesh_data.getVertexData().at(18) == 0.0f);

    // Third Unit
    REQUIRE(mesh_data.getVertexData().at(22) == 1.0f);
    REQUIRE(mesh_data.getVertexData().at(23) == -1.0f);

    //Fourth Position
    REQUIRE(mesh_data.getVertexData().at(24) == 10.0f);
    REQUIRE(mesh_data.getVertexData().at(25) == 10.0f);
    REQUIRE(mesh_data.getVertexData().at(26) == 0.0f);

    // Fourth Unit
    REQUIRE(mesh_data.getVertexData().at(30) == -1.0f);
    REQUIRE(mesh_data.getVertexData().at(31) == -1.0f);

    // Second Rect First Position
    REQUIRE(mesh_data.getVertexData().at(32) == 20.0f);
    REQUIRE(mesh_data.getVertexData().at(33) == 40.0f);
    REQUIRE(mesh_data.getVertexData().at(34) == 0.0f);

    // Second Rect First Color
    REQUIRE(mesh_data.getVertexData().at(35) == 1.0f);
    REQUIRE(mesh_data.getVertexData().at(36) == 1.0f);
    REQUIRE(mesh_data.getVertexData().at(37) == 1.0f);

    // Second Rect First Unit
    REQUIRE(mesh_data.getVertexData().at(38) == -1.0f);
    REQUIRE(mesh_data.getVertexData().at(39) == 1.0f);



}
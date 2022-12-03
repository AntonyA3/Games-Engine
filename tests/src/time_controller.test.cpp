#include <catch_amalgamated.hpp>
#include <cstdint>
#include <string>
#include <glm/glm.hpp>
#include <timing/time_controller.hpp>
#include <iostream>

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE

TEST_CASE("Time Controller With No time Overflow", "[TimeController]" ) {
    TimeController time_controller;
    time_controller.create(0);
    REQUIRE(time_controller.getDeltaTime() == Catch::Approx(1.0f / 60.0f));
    time_controller.update(20);
    REQUIRE(time_controller.getDeltaTime() == Catch::Approx(0.02f));   
}

TEST_CASE("Time Controller Should Produce Correct Delta Time at integer Overflow", "[TimeController]" ) {
    TimeController time_controller;
    time_controller.create();
    time_controller.update(std::numeric_limits<Uint64>::max() - 10);
    // Integer overflow at 10/30ms;
    time_controller.update(20);
    REQUIRE(time_controller.getDeltaTime() == Catch::Approx(0.03f));
}
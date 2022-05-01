#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <simulator.h>

using minimetro::MiniMetroApp;

TEST_CASE("Test Setup") {
    minimetro::Brain brain;
    REQUIRE(750 == 750);
}
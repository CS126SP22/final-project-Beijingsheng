#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <simulator.h>

using minimetro::MiniMetroApp;

// No.1
TEST_CASE("Test Brain - Constructor") {
    minimetro::Brain brain;
    REQUIRE(brain.top_ == 100);
}

// No.2
TEST_CASE("Test Brain - Constructor with Value") {
    std::vector<std::vector<float>> locations {{100, 100}, {200, 200}};
    std::vector<std::vector<int>> connections {{0,1}, {1,0}};
    std::vector<minimetro::Metro> metros;
    std::vector<minimetro::Item> items;
    std::vector<int> destinations;
    minimetro::Brain Brain(locations, connections, metros, 10, items, destinations, 500);
    REQUIRE(Brain.kWindowSize == 500);
}

// No.3
TEST_CASE("Test Brain - InitValues") {
    std::vector<std::vector<float>> locations {{100, 100}, {200, 200}};
    std::vector<std::vector<int>> connections {{0,1}, {1,0}};
    std::vector<minimetro::Metro> metros;
    std::vector<minimetro::Item> items;
    std::vector<int> destinations;
    minimetro::Brain brain(locations, connections, metros, 10, items, destinations, 500);
    REQUIRE(brain.cur_heights_.size() == 0);
}

// No.4
TEST_CASE("Test Metro - Constructor") {
    minimetro::Metro metro(std::vector<int> {0,1,2,1,0}, ci::Color("black"));
    REQUIRE(metro.GetCurStop() == 0);
}

// No.5
TEST_CASE("Test Metro - Get Next Stop") {
    minimetro::Metro metro(std::vector<int> {0,1,2,1,0}, ci::Color("black"));
    REQUIRE(metro.GetNextStop() == 1);
}

// No.6
TEST_CASE("Test Metro - OnArrive") {
    minimetro::Metro metro(std::vector<int> {0,1,2,1,0}, ci::Color("black"));
    metro.OnArrive();
    REQUIRE(metro.GetNextStop() == 2);
}

// No.7
TEST_CASE("Test Item - Constructor") {
    minimetro::Item item(5, ci::Color("white"));
    REQUIRE(item.GetCurStop() == 5);
}

// No.8
TEST_CASE("Test Item - on_metro_ value") {
    minimetro::Item item(5, ci::Color("white"));
    REQUIRE(item.on_metro_ == -1);
}

// No.9
TEST_CASE("Test Dijkstra - Constructor") {

}
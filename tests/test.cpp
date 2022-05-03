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
    minimetro::Dijkstra dijkstra(std::vector<std::vector<int>> {{1,0},{0,1}});
    REQUIRE(dijkstra.num_of_vertices_ == 2);
}

// No.10
TEST_CASE("Test Dijkstra - Get Path") {
    minimetro::Dijkstra dijkstra(std::vector<std::vector<int>> {{1,0},{0,1}});
    REQUIRE(dijkstra.GetPath(0)[0] == 0);
}

// No.11
TEST_CASE("Test Dijkstra - Get Path 2") {
    minimetro::Dijkstra dijkstra(std::vector<std::vector<int>> {{0,1,0},{1,0,1},{0,1,0}});
    REQUIRE(dijkstra.GetPath(0).size() == 3);
}

// No.12
TEST_CASE("Test Brain - Init Dijkstra") {
    std::vector<std::vector<float>> locations {{100, 100}, {200, 200}};
    std::vector<std::vector<int>> connections {{0,1}, {1,0}};
    std::vector<minimetro::Metro> metros;
    std::vector<minimetro::Item> items;
    std::vector<int> destinations;
    minimetro::Brain Brain(locations, connections, metros, 10, items, destinations, 500);
    REQUIRE(Brain.InitDijkstra().num_of_vertices_ == 2);
}

// No.13
TEST_CASE("Test Brain - Init Metro") {
    std::vector<std::vector<float>> locations {{100, 100}, {200, 200}};
    std::vector<std::vector<int>> connections {{0,1}, {1,0}};
    std::vector<minimetro::Metro> metros;
    std::vector<minimetro::Item> items;
    std::vector<int> destinations;
    minimetro::Brain Brain(locations, connections, metros, 10, items, destinations, 500);
    Brain.InitMetro();
    REQUIRE(Brain.metros_.size() == 0);
}

// No.14
TEST_CASE("Test Brain - Handle Horizontal Scroll") {
    minimetro::Brain brain;
    brain.HandleBrush(vec2(490, 200));
    REQUIRE(brain.y_scroll_ == 200);
}

// No.15
TEST_CASE("Test Brain - Handle Vertical Scroll") {
    minimetro::Brain brain;
    brain.HandleBrush(vec2(200, 490));
    REQUIRE(brain.x_scroll_ == 200);
}

// No.16
TEST_CASE("Test Brain - Handle Speed Control") {
    minimetro::Brain brain;
    brain.HandleBrush(vec2(700, 80));
    REQUIRE(brain.speed_ == 3.1f);
}

// No.17
TEST_CASE("Test Brain - Handle Click Station") {
    std::vector<std::vector<float>> locations {{100, 100}, {200, 200}};
    std::vector<std::vector<int>> connections {{0,1}, {1,0}};
    std::vector<minimetro::Metro> metros;
    std::vector<minimetro::Item> items;
    std::vector<int> destinations;
    minimetro::Brain brain(locations, connections, metros, 10, items, destinations, 500);
    brain.HandleBrush(vec2(200, 200));
    REQUIRE(brain.message_ == "Station 0 has been visited 0 times.");
}

// No.18
TEST_CASE("Test Brain - Handle Click Pause Button") {
    minimetro::Brain brain;
    brain.HandleBrush(vec2(600, 113));
    REQUIRE(brain.on_pause_ == false);
}

// No.19
TEST_CASE("Test Brain - Handle Click Metro") {
    std::vector<std::vector<float>> locations {{100, 100}, {200, 200}};
    std::vector<std::vector<int>> connections {{0,1}, {1,0}};
    minimetro::Metro m(std::vector<int> {0,1,0}, ci::Color("white"));
    std::vector<minimetro::Metro> metros;
    metros.push_back(m);
    std::vector<minimetro::Item> items;
    std::vector<int> destinations;
    minimetro::Brain brain(locations, connections, metros, 10, items, destinations, 500);
    brain.AdvanceOneFrame();
    brain.HandleBrush(vec2(200, 200));
    REQUIRE(brain.message_ == "Station 0 has been visited 0 times.");
}
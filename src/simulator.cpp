//
// Created by clark on 2022/4/12.
//
#include "../include/simulator.h"

namespace minimetro {

MiniMetroApp::MiniMetroApp() {
    ci::app::setWindowSize(kWindowSize, kWindowSize);

    std::vector<std::vector<float>> locations;
    std::vector<float> l1 {100, 100};
    std::vector<float> l2 {200, 100};
    std::vector<float> l3 {300, 100};
    std::vector<float> l4 {400, 100};
    std::vector<float> l5 {400, 200};
    std::vector<float> l6 {400, 300};
    std::vector<float> l7 {400, 400};
    std::vector<float> l8 {300, 400};
    std::vector<float> l9 {200, 400};
    std::vector<float> l10 {100, 400};
    std::vector<float> l11 {100, 300};
    std::vector<float> l12 {100, 200};
    locations.push_back(l1);
    locations.push_back(l2);
    locations.push_back(l3);
    locations.push_back(l4);
    locations.push_back(l5);
    locations.push_back(l6);
    locations.push_back(l7);
    locations.push_back(l8);
    locations.push_back(l9);
    locations.push_back(l10);
    locations.push_back(l11);
    locations.push_back(l12);

    std::vector<std::vector<int>> connections;
    std::vector<int> c1 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    std::vector<int> c2 {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0};
    std::vector<int> c3 {0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0};
    std::vector<int> c4 {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> c5 {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1};
    std::vector<int> c6 {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0};
    std::vector<int> c7 {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0};
    std::vector<int> c8 {0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0};
    std::vector<int> c9 {0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0};
    std::vector<int> c10 {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0};
    std::vector<int> c11 {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1};
    std::vector<int> c12 {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};


    connections.push_back(c1);
    connections.push_back(c2);
    connections.push_back(c3);
    connections.push_back(c4);
    connections.push_back(c5);
    connections.push_back(c6);
    connections.push_back(c7);
    connections.push_back(c8);
    connections.push_back(c9);
    connections.push_back(c10);
    connections.push_back(c11);
    connections.push_back(c12);

    std::vector<Metro> metros;
    std::vector<int> r1;
    std::vector<int> r2 {0};
    for (int i = 0; i < 12; i++) {
        r1.push_back(i);
        r2.push_back(11 - i);
    }
    r1.push_back(0);
    Metro m1 = Metro( r1, ci::Color("black"));
    Metro m2 = Metro(r2, ci::Color("brown"));
    Metro m3 = Metro(std::vector<int> {1, 8, 1}, ci::Color("red"));
    Metro m4 = Metro(std::vector<int> {7, 2, 7}, ci::Color("yellow"));
    Metro m5 = Metro(std::vector<int> {4, 11, 4}, ci::Color("pink"));
    Metro m6 = Metro(std::vector<int> {10, 5, 10}, ci::Color("orange"));
//    metros.push_back(m1);
    metros.push_back(m2);
    metros.push_back(m3);
    metros.push_back(m4);
    metros.push_back(m5);
    metros.push_back(m6);

    std::vector<Passenger> passengers;
    for (int i = 0; i < 10; i++) {
        passengers.push_back(Passenger(i, ci::Color("blue")));
    }

    brain_ = Brain(locations, connections, metros, 12, passengers, 6);
}

void MiniMetroApp::draw() {
    ci::Color background_color("white");
    ci::gl::clear(background_color);
    brain_.Display();
}

void MiniMetroApp::update() {
    brain_.AdvanceOneFrame();
}

}

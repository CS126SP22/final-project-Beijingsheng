//
// Created by clark on 2022/4/12.
//
#include "../include/simulator.h"

namespace minimetro {

MiniMetroApp::MiniMetroApp() {
    ci::app::setWindowSize(kWindowSize, kWindowSize);

    std::vector<std::vector<float>> locations;
    std::vector<float> l1;
    l1.push_back(100);
    l1.push_back(100);
    std::vector<float> l2;
    l2.push_back(100);
    l2.push_back(500);
    std::vector<float> l3;
    l3.push_back(500);
    l3.push_back(500);
    locations.push_back(l1);
    locations.push_back(l2);
    locations.push_back(l3);

    std::vector<std::vector<int>> connections;
    std::vector<int> c1;
    std::vector<int> c2;
    std::vector<int> c3;
    c1.push_back(0);
    c1.push_back(1);
    c1.push_back(0);
    c2.push_back(1);
    c2.push_back(0);
    c2.push_back(1);
    c3.push_back(0);
    c3.push_back(1);
    c3.push_back(0);
    connections.push_back(c1);
    connections.push_back(c2);
    connections.push_back(c3);
    brain_ = Brain(locations, connections, 12);
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

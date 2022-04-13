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
    l2.push_back(250);
    l2.push_back(370);
    std::vector<float> l3;
    l3.push_back(500);
    l3.push_back(500);
    std::vector<float> l4;
    l4.push_back(300);
    l4.push_back(600);
    locations.push_back(l1);
    locations.push_back(l2);
    locations.push_back(l3);
    locations.push_back(l4);

    std::vector<std::vector<int>> connections;
    std::vector<int> c1;
    std::vector<int> c2;
    std::vector<int> c3;
    std::vector<int> c4;

    c1.push_back(0);
    c1.push_back(1);
    c1.push_back(0);
    c1.push_back(0);

    c2.push_back(1);
    c2.push_back(0);
    c2.push_back(1);
    c2.push_back(1);

    c3.push_back(0);
    c3.push_back(1);
    c3.push_back(0);
    c3.push_back(1);

    c4.push_back(0);
    c4.push_back(1);
    c4.push_back(1);
    c4.push_back(0);

    connections.push_back(c1);
    connections.push_back(c2);
    connections.push_back(c3);
    connections.push_back(c4);

    std::vector<std::vector<int>> routes;
    std::vector<int> r1;
    r1.push_back(0);
    r1.push_back(1);
    r1.push_back(3);
    routes.push_back(r1);
    std::vector<int> r2;
    r2.push_back(1);
    r2.push_back(3);
    r2.push_back(2);
    r2.push_back(1);
    routes.push_back(r2);

    std::vector<std::vector<int>> destinations;
    std::vector<int> d1;
    d1.push_back(0);
    d1.push_back(1);
    d1.push_back(3);
    d1.push_back(2);
    destinations.push_back(d1);
    std::vector<int> d2;
    d2.push_back(2);
    d2.push_back(1);
    d2.push_back(0);
    destinations.push_back(d2);

    std::vector<ci::Color> colors;
    colors.push_back(ci::Color("orange"));
    colors.push_back(ci::Color("red"));

    brain_ = Brain(locations, connections, routes, 12, destinations, colors);
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

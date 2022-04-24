//
// Created by clark on 2022/4/12.
//
#include "../include/simulator.h"

namespace minimetro {

MiniMetroApp::MiniMetroApp() {
    ci::app::setWindowSize(kWindowSize, kWindowSize);

    std::vector<std::vector<float>> locations;
    std::vector<std::vector<int>> connections;
    std::vector<Metro> metros;
    std::vector<Passenger> passengers;
    std::vector<int> destination;

    // PRINT DESTINATIONS
//    for (int i = 0; i < destination.size(); i++) {
//        std::cout << destination[i] << " ";
//    }
//    std::cout << std::endl;

    brain_ = Brain(locations, connections, metros, 12, passengers, destination);
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

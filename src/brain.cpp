//
// Created by clark on 2022/4/12.
//
#include "brain.h"

namespace minimetro {

using glm::vec2;

Brain::Brain() {}

Brain::Brain(std::vector<std::vector<float>> locations, std::vector<std::vector<int>> connections, int station_radius) {
    this->locations = locations;
    this->connections = connections;
    this->station_radius_ = station_radius;
}

void Brain::Display() {
    for (unsigned int i = 0; i < connections.size(); i++) {
        for (unsigned int j = i + 1; j < connections.size(); j++) {
            if (connections[i][j] == 1) {
                ci::gl::color(ci::Color("blue"));
                ci::gl::drawLine(glm::vec2(locations[i][0], locations[i][1]), glm::vec2(locations[j][0], locations[j][1]));
            }
        }
    }
    for (unsigned int i = 0; i < locations.size(); i++) {
        ci::gl::color(ci::Color("black"));
        ci::gl::drawSolidCircle(glm::vec2(locations[i][0], locations[i][1]), station_radius_);
    }
}

void Brain::AdvanceOneFrame() {

}

}
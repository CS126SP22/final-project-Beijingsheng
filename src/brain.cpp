//
// Created by clark on 2022/4/12.
//
#include "brain.h"

namespace minimetro {

using glm::vec2;

Brain::Brain() {}

Brain::Brain(std::vector<std::vector<float>> locations, std::vector<std::vector<int>> connections,
             std::vector<std::vector<int>> routes, int station_radius,
             std::vector<std::vector<int>> destinations, std::vector<ci::Color> colors) {
    this->locations = locations;
    this->connections = connections;
    this->station_radius_ = station_radius;
    this->routes = routes;
    this->destinations = destinations;
    this->colors = colors;
    for (unsigned int i = 0; i < routes.size(); i++) {
        std::vector<float> curLoc;
        curLoc.push_back(locations[routes[i][0]][0]);
        curLoc.push_back(locations[routes[i][0]][1]);
        this->metro_locs.push_back(curLoc);
        this->passengers.push_back(0);
        next_stop.push_back(1);
        if (routes[i][0] == routes[i][routes[i].size() - 1]) {
            std::cout << i << std::endl;
            this->directions.push_back(-1);
        } else {
            this->directions.push_back(0);
        }
    }
    for (unsigned int i = 0; i < colors.size(); i++) {
        this->tourists_locs.push_back(0);
        this->on_metro.push_back(false);
    }
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
    for (unsigned int i = 0; i < metro_locs.size(); i++) {
        ci::gl::color(ci::Color("yellow"));
        ci::gl::drawSolidCircle(glm::vec2(metro_locs[i][0], metro_locs[i][1]), station_radius_ * 0.7);
    }
    for (unsigned int i = 0; i < tourists_locs.size(); i++) {
        if (on_metro[i] == false) {
            ci::gl::color(ci::Color(colors[i]));
            ci::gl::drawSolidCircle(glm::vec2(locations[destinations[i][tourists_locs[i]]][0], locations[destinations[i][tourists_locs[i]]][1]), station_radius_ * 0.5);
        }
    }
}

void Brain::AdvanceOneFrame() {
    for (unsigned int i = 0; i < metro_locs.size(); i++) {
        if (glm::length(glm::vec2(metro_locs[i][0], metro_locs[i][1]) - glm::vec2(locations[routes[i][next_stop[i]]][0], locations[routes[i][next_stop[i]]][1])) < station_radius_) {
            metro_locs[i][0] = locations[routes[i][next_stop[i]]][0];
            metro_locs[i][1] = locations[routes[i][next_stop[i]]][1];

            if (directions[i] == 0 || directions[i] == -1) next_stop[i] = (next_stop[i] + 1) % routes[i].size();
            else if (directions[i] == 1) next_stop[i] = (next_stop[i] - 1) % routes[i].size();

            if (next_stop[i] == 0 || next_stop[i] == routes[i].size() - 1) {
                if (directions[i] == 0) directions[i] = 1;
                else if (directions[i] == 1) directions[i] = 0;
            }

            if (passengers[i] == 0) {

            } else {

            }

        } else {
            float x1 = locations[routes[i][next_stop[i]]][1] - metro_locs[i][1];
            float x2 = locations[routes[i][next_stop[i]]][0] - metro_locs[i][0];
            float x3 = sqrt(x1 * x1 + x2 * x2);
            metro_locs[i][0] += 2 * x2 / x3;
            metro_locs[i][1] += 2 * x1 / x3;
        }
    }
}

}
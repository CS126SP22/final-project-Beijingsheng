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
    InitPlatform(locations, routes);
    InitMetroLocs(routes);
    InitPassengers(routes);
    InitNextStops(routes);
    InitDirections(routes);
    InitColors(colors);
}

void Brain::InitPassengers(std::vector<std::vector<int>> routes) {
    for (unsigned int i = 0; i < routes.size(); i++) {
        this->passengers.push_back(0);
    }
}

void Brain::InitNextStops(std::vector<std::vector<int>> routes) {
    for (unsigned int i = 0; i < routes.size(); i++) {
        next_stop.push_back(1);
    }
}

void Brain::InitMetroLocs(std::vector<std::vector<int>> routes) {
    for (unsigned int i = 0; i < routes.size(); i++) {
        std::vector<float> curLoc;
        curLoc.push_back(locations[routes[i][0]][0]);
        curLoc.push_back(locations[routes[i][0]][1]);
        this->metro_locs.push_back(curLoc);
    }
}

void Brain::InitDirections(std::vector<std::vector<int>> routes) {
    for (unsigned int i = 0; i < routes.size(); i++) {
        if (routes[i][0] == routes[i][routes[i].size() - 1]) {
            this->directions.push_back(-1);
        } else {
            this->directions.push_back(0);
        }
    }
}

void Brain::InitPlatform(std::vector<std::vector<float>> locations, std::vector<std::vector<int>> routes) {
    for (unsigned int i = 0; i < locations.size(); i++) {
        std::vector<int> toPush;
        platform.push_back(toPush);
    }
    for (unsigned int i = 0; i < destinations.size(); i++) {
        platform[destinations[i][0]].push_back(i);
    }
}

void Brain::InitColors(std::vector<ci::Color> colors) {
    for (unsigned int i = 0; i < colors.size(); i++) {
        this->tourists_locs.push_back(0);
        this->on_metro.push_back(false);
    }
}

void Brain::DisplayConnections() {
    for (unsigned int i = 0; i < connections.size(); i++) {
        for (unsigned int j = i + 1; j < connections.size(); j++) {
            if (connections[i][j] == 1) {
                ci::gl::color(ci::Color("blue"));
                ci::gl::drawLine(glm::vec2(locations[i][0], locations[i][1]), glm::vec2(locations[j][0], locations[j][1]));
            }
        }
    }
}

void Brain::DisplayStations() {
    for (unsigned int i = 0; i < locations.size(); i++) {
        ci::gl::color(ci::Color("black"));
        ci::gl::drawSolidCircle(glm::vec2(locations[i][0], locations[i][1]), station_radius_);
    }
}

void Brain::DisplayMetros() {
    for (unsigned int i = 0; i < metro_locs.size(); i++) {
        ci::gl::color(ci::Color("yellow"));
        ci::gl::drawSolidCircle(glm::vec2(metro_locs[i][0], metro_locs[i][1]), station_radius_ * 0.7);
    }
}

void Brain::DisplayTourists() {
    for (unsigned int i = 0; i < tourists_locs.size(); i++) {
        if (on_metro[i] == false) {
            ci::gl::color(ci::Color(colors[i]));
            ci::gl::drawSolidCircle(glm::vec2(locations[destinations[i][tourists_locs[i]]][0], locations[destinations[i][tourists_locs[i]]][1]), station_radius_ * 0.5);
        }
    }
}

void Brain::Display() {
    DisplayConnections();
    DisplayStations();
    DisplayMetros();
    DisplayTourists();
}

void Brain::UpdateDirection(int i) {
    if (next_stop[i] == 0 || next_stop[i] == routes[i].size() - 1) {
        if (directions[i] == 0) directions[i] = 1;
        else if (directions[i] == 1) directions[i] = 0;
    }
}

int Brain::GetMetroNextStop(int i) {
    int temp = next_stop[i];
    int temp2 = directions[i];
    if (temp2 == 0 || temp2 == -1)
        temp = (temp + 1) % routes[i].size();
    else if (temp2 == 1)
        temp = (temp - 1) % routes[i].size();
    return routes[i][temp];
}

void Brain::UpdateNextStop(int i) {
    if (directions[i] == 0 || directions[i] == -1) next_stop[i] = (next_stop[i] + 1) % routes[i].size();
    else if (directions[i] == 1) next_stop[i] = (next_stop[i] - 1) % routes[i].size();
}

int Brain::HasPassengerToBoard(int i) {
    int station = routes[i][next_stop[i]];
    if (platform[station].size() > 0) {
        for (unsigned int k = 0; k < platform[station].size(); k++) {
            int curPassengerId = platform[station][k];
            int passengerNextLoc = destinations[curPassengerId].size() - 1;
            if (tourists_locs[curPassengerId] + 1 < passengerNextLoc) passengerNextLoc = tourists_locs[curPassengerId] + 1;
            if (GetMetroNextStop(i) == destinations[curPassengerId][passengerNextLoc]) {

            }
        }
    }
    return -1;
}

int Brain::HasPassengerToLeave(int i) {

}

void Brain::UpdateArriving(int i) {
    metro_locs[i][0] = locations[routes[i][next_stop[i]]][0];
    metro_locs[i][1] = locations[routes[i][next_stop[i]]][1];

    if (passengers[i] == 0) {
        if (HasPassengerToBoard(i) != -1) {

        }
    } else {
        if (HasPassengerToLeave(i) != -1) {

        }
    }
    UpdateNextStop(i);
    UpdateDirection(i);
}

void Brain::UpdateDriving(int i) {
    float x1 = locations[routes[i][next_stop[i]]][1] - metro_locs[i][1];
    float x2 = locations[routes[i][next_stop[i]]][0] - metro_locs[i][0];
    float x3 = sqrt(x1 * x1 + x2 * x2);
    metro_locs[i][0] += 2 * x2 / x3;
    metro_locs[i][1] += 2 * x1 / x3;
}

void Brain::AdvanceOneFrame() {
    for (unsigned int i = 0; i < metro_locs.size(); i++) {
        if (glm::length(glm::vec2(metro_locs[i][0], metro_locs[i][1])
                            - glm::vec2(locations[routes[i][next_stop[i]]][0], locations[routes[i][next_stop[i]]][1]))
                            < station_radius_) {
            UpdateArriving(i);
        } else {
            UpdateDriving(i);
        }
    }
}

}
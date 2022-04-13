//
// Created by clark on 2022/4/12.
//
#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace minimetro {
class Brain {
public:
    Brain();
    Brain(std::vector<std::vector<float>> locations, std::vector<std::vector<int>> connections,
          std::vector<std::vector<int>> routes, int station_radius,
          std::vector<std::vector<int>> destinations, std::vector<ci::Color> colors);
    void Display();
    void AdvanceOneFrame();

private:
    std::vector<std::vector<float>> locations;
    std::vector<std::vector<int>> connections;
    std::vector<std::vector<float>> metro_locs;
    std::vector<int> next_stop;
    int station_radius_;
    std::vector<int> directions;
    std::vector<std::vector<int>> destinations;
    std::vector<int> tourists_locs;
    std::vector<bool> on_metro;
    std::vector<ci::Color> colors;
    std::vector<int> passengers;
    std::vector<std::vector<int>> routes;
};
}

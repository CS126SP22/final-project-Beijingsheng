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
    Brain(std::vector<std::vector<float>> locations, std::vector<std::vector<int>> connections, int station_radius);
    void Display();
    void AdvanceOneFrame();

private:
    std::vector<std::vector<float>> locations;
    std::vector<std::vector<int>> connections;
    int station_radius_;
};
}

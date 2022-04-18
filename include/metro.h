//
// Created by clark on 2022/4/13.
//
#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace minimetro {

class Metro {
public:
    Metro();
    Metro(std::vector<int> route, ci::Color color);

    std::vector<float> location;
    int stop_idx;
    int next_stop_idx;
    int passenger;
    ci::Color color;
    std::vector<int> route;

    int GetCurStop();
    int GetNextStop();
    void OnArrive();
private:

};

}

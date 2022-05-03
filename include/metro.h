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
    int GetCurStop();
    int GetNextStop();
    void OnArrive();
    std::vector<float> location_;
    int cur_stop_idx_;
    int next_stop_idx_;
    int passenger_;
    ci::Color color_;
    std::vector<int> route_;
};

}

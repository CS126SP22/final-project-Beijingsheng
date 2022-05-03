//
// Created by clark on 2022/4/13.
//
#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace minimetro {

class Item {
public:
    Item(int start_station, ci::Color color);
    int GetCurStop();
    int stop_visited_;
    ci::Color color_;
    int on_metro_;
    std::vector<int> visit_hist_;
    int cur_stop_;
};

}